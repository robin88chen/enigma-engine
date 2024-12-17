#include "AssetHeaderDataMap.hpp"
#include "AssetPackageErrors.hpp"
#include <cassert>
#include <cstring>

using namespace AssetPackage;

constexpr unsigned int HEADER_ATTRIBUTE_SIZE = sizeof(unsigned int) * 5;

AssetHeaderDataMap::AssetHeaderDataMap()
{
    m_headerDataMap.clear();
}

AssetHeaderDataMap::~AssetHeaderDataMap()
{
    m_headerDataMap.clear();
}

error AssetHeaderDataMap::insertHeaderData(const AssetHeaderData& header)
{
    if (hasAssetKey(header.m_name)) return ErrorCode::duplicatedKey;
    bool is_ok = false;
    std::tie(std::ignore, is_ok) = m_headerDataMap.emplace(header.m_name, header);
    assert(is_ok);
    return ErrorCode::ok;
}

error AssetHeaderDataMap::removeHeaderData(const std::string& name)
{
    if (!hasAssetKey(name)) return ErrorCode::notExistedKey;
    m_headerDataMap.erase(name);
    return ErrorCode::ok;
}

bool AssetHeaderDataMap::hasAssetKey(const std::string& name) const
{
    const auto find_iter = m_headerDataMap.find(name);
    return (find_iter != m_headerDataMap.end());
}

void AssetHeaderDataMap::repackContentOffsets(const unsigned content_size, const unsigned base_offset)
{
    for (auto& [name, header] : m_headerDataMap)
    {
        if (header.m_offset >= base_offset)
        {
            header.m_offset -= content_size;
        }
    }
}

std::optional<AssetHeaderDataMap::AssetHeaderData> AssetHeaderDataMap::tryGetHeaderData(const std::string& name)
{
    if (const auto find_iter = m_headerDataMap.find(name); find_iter != m_headerDataMap.end()) return find_iter->second;
    return std::nullopt;
}

size_t AssetHeaderDataMap::calcHeaderDataMapBytes() const
{
    size_t sum = 0;
    for (const auto& [name, header] : m_headerDataMap)
    {
        sum += (name.length() + 1); // name 的長度加起來
    }
    sum += (getTotalDataCount() * HEADER_ATTRIBUTE_SIZE);  // 5個uint * 總數量
    return sum;
}

std::vector<char> AssetHeaderDataMap::exportToByteBuffer() const
{
    const size_t size = calcHeaderDataMapBytes();
    if (size == 0) return {};

    std::vector<char> buff;
    buff.resize(size, 0);

    size_t index = 0;
    for (const auto& [name, header] : m_headerDataMap)
    {
        assert(index + header.m_name.length() + 1 + HEADER_ATTRIBUTE_SIZE <= size);
        std::memcpy(&buff[index], header.m_name.c_str(), header.m_name.length());
        index += (header.m_name.length() + 1);
        std::memcpy(&buff[index], &(header.m_version), sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&buff[index], &(header.m_size), sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&buff[index], &(header.m_orgSize), sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&buff[index], &(header.m_offset), sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&buff[index], &(header.m_crc), sizeof(unsigned int));
        index += sizeof(unsigned int);
    }
    return buff;
}

std::error_code AssetHeaderDataMap::importFromByteBuffer(const std::vector<char>& buff)
{
    if (buff.empty()) return ErrorCode::emptyBuffer;
    m_headerDataMap.clear();
    const size_t size = buff.size();
    size_t index = 0;
    while (index < size)
    {
        AssetHeaderData header{};
        header.m_name = std::string{ &buff[index] };
        index += (header.m_name.length() + 1);
        std::memcpy(&header.m_version, &buff[index], sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&header.m_size, &buff[index], sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&header.m_orgSize, &buff[index], sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&header.m_offset, &buff[index], sizeof(unsigned int));
        index += sizeof(unsigned int);
        std::memcpy(&header.m_crc, &buff[index], sizeof(unsigned int));
        index += sizeof(unsigned int);

        if (const error er = insertHeaderData(header)) return er;
    }
    return ErrorCode::ok;
}

