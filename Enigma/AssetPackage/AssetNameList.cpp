#include "AssetNameList.hpp"
#include "AssetPackageErrors.hpp"
#include <cassert>
#include <cstring>

using namespace AssetPackage;

AssetNameList::AssetNameList()
{
    m_assetNames.clear();
}

AssetNameList::~AssetNameList() noexcept
{
    m_assetNames.clear();
}

bool AssetNameList::hasAssetName(const std::string& name)
{
    if (name.empty()) return false;
    return m_assetNames.find(name) != m_assetNames.end();
}

error AssetNameList::appendAssetName(const std::string& name)
{
    if (name.empty()) return ErrorCode::emptyKey;
    if (hasAssetName(name)) return ErrorCode::duplicatedKey;
    m_assetNames.emplace(name);
    return ErrorCode::ok;
}

error AssetNameList::removeAssetName(const std::string& name)
{
    if (name.empty()) return ErrorCode::emptyKey;
    if (!hasAssetName(name)) return ErrorCode::notExistedKey;
    m_assetNames.erase(name);
    return ErrorCode::ok;
}

size_t AssetNameList::calcNameListDataBytes() const
{
    size_t sum = 0;
    for (const std::string& name : m_assetNames)
    {
        sum += (name.length() + 1);
    }
    return sum;
}

std::vector<char> AssetNameList::exportToByteBuffer() const
{
    const size_t size = calcNameListDataBytes();
    if (size == 0) return {};

    std::vector<char> buff;
    buff.resize(size, 0);

    size_t index = 0;
    for (const std::string& name : m_assetNames)
    {
        assert(index + name.length() + 1 <= size);
        std::memcpy(&buff[index], name.c_str(), name.length());
        index += (name.length() + 1);
    }
    return buff;
}

error AssetNameList::importFromByteBuffer(const std::vector<char>& buff)
{
    if (buff.empty()) return ErrorCode::emptyBuffer;
    m_assetNames.clear();
    size_t index = 0;
    error er;
    while ((index < buff.size()) && (!er))
    {
        const std::string name{ &buff[index] };
        index += (name.length() + 1);
        er = appendAssetName(name);
    }
    return er;
}

