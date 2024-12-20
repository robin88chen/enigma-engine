// NOLINTBEGIN(clang-analyzer-optin.core.EnumCastOutOfRange)
#include "AssetPackageFile.hpp"
#include "AssetPackageErrors.hpp"
#include "AssetNameList.hpp"
#include "AssetHeaderDataMap.hpp"
#include "Platforms/Debug.hpp"
#include "zlib.h"
#include <ctime>
#include <cstring>
#include <cassert>
#include <filesystem>

using namespace AssetPackage;

constexpr unsigned int PACKAGE_FORMAT_TAG = 0x01;
const std::string PACKAGE_HEADER_FILE_EXT = ".eph";
const std::string PACKAGE_BUNDLE_FILE_EXT = ".epb";

using AssetHeaderData = AssetHeaderDataMap::AssetHeaderData;

static unsigned int getFileVersionWithModifyTime(const std::string& file_path)
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    if (file_path.empty()) return 0;
    const std::filesystem::file_time_type file_time = std::filesystem::last_write_time(file_path);
    const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(file_time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    const std::time_t modify_time = std::chrono::system_clock::to_time_t(sctp);
    //struct stat attrib;
    //if (int err = stat(file_path.c_str(), &attrib); err != 0) return 0;
    //const std::time_t modify_time = (time_t)attrib.st_mtime;
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    const std::tm* clock = std::localtime(&modify_time); // (attrib.st_mtime));
    if (clock == nullptr) return 0;
    const unsigned int min_step = clock->tm_min / 4;
    // min_step 4 bits, hour 5 bits, mday 5 bits, month 4 bits, year since 2010
    const unsigned int ver = static_cast<unsigned int>(min_step) + (static_cast<unsigned int>(clock->tm_hour) << 4)
        + (static_cast<unsigned int>(clock->tm_mday) << 9) + (static_cast<unsigned int>(clock->tm_mon) << 14)
        + ((static_cast<unsigned int>(clock->tm_year) - 110) << 18);
    return ver;
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

static time_t getTimeStampFromFileVersion(unsigned int ver)
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    std::tm clock{};
    std::memset(&clock, 0, sizeof(struct tm));
    clock.tm_min = static_cast<int>(ver & 0xf) * 4;
    ver = ver >> 4;
    clock.tm_hour = static_cast<int>(ver & 0x1f);
    ver = ver >> 5;
    clock.tm_mday = static_cast<int>(ver & 0x1f);
    ver = ver >> 5;
    clock.tm_mon = static_cast<int>(ver & 0xf);
    ver = ver >> 4;
    clock.tm_year = static_cast<int>(ver + 110);
    return std::mktime(&clock);
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

AssetPackageFile::AssetPackageFile() : m_formatTag(PACKAGE_FORMAT_TAG), m_fileVersion(0), m_assetCount(0), m_nameList(nullptr), m_headerDataMap(nullptr)
{
}

AssetPackageFile::~AssetPackageFile() noexcept
{
    try
    {
        resetPackage();
    }
    catch (...)
    {
        Platforms::Debug::printf("AssetPackageFile::~AssetPackageFile() exception");
    }
}

std::shared_ptr<AssetPackageFile> AssetPackageFile::createNewPackage(const std::string& base_filename)
{
    const std::shared_ptr<AssetPackageFile> package = std::shared_ptr<AssetPackageFile>(new AssetPackageFile());
    [[maybe_unused]] const error er = package->createNewPackageImp(base_filename);
    assert(!er);
    return package;
}

error AssetPackageFile::createNewPackageImp(const std::string& base_filename)
{
    if (base_filename.empty()) return ErrorCode::emptyFileName;

    resetPackage();

    m_nameList = std::make_unique<AssetNameList>();
    m_headerDataMap = std::make_unique<AssetHeaderDataMap>();
    m_baseFilename = base_filename;

    const std::string header_filename = m_baseFilename + PACKAGE_HEADER_FILE_EXT;
    const std::string bundle_filename = m_baseFilename + PACKAGE_BUNDLE_FILE_EXT;

    m_headerFile.open(header_filename.c_str(), std::fstream::in | std::fstream::out
        | std::fstream::binary | std::fstream::trunc);
    m_bundleFile.open(bundle_filename.c_str(), std::fstream::in | std::fstream::out
        | std::fstream::binary | std::fstream::trunc);
    if ((!m_headerFile) || (!m_bundleFile))
    {
        return ErrorCode::fileOpenFail;
    }

    saveHeaderFile();

    return ErrorCode::ok;
}

std::shared_ptr<AssetPackageFile> AssetPackageFile::openPackage(const std::string& base_filename)
{
    const std::shared_ptr<AssetPackageFile> package = std::shared_ptr<AssetPackageFile>(new AssetPackageFile());
    [[maybe_unused]] const error er = package->openPackageImp(base_filename);
    assert(!er);
    return package;
}

error AssetPackageFile::openPackageImp(const std::string& base_filename)
{
    if (base_filename.empty()) return ErrorCode::emptyFileName;

    resetPackage();

    m_baseFilename = base_filename;

    const std::string header_filename = m_baseFilename + PACKAGE_HEADER_FILE_EXT;
    const std::string bundle_filename = m_baseFilename + PACKAGE_BUNDLE_FILE_EXT;

    m_headerFile.open(header_filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
    m_bundleFile.open(bundle_filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
    if ((!m_headerFile) || (!m_bundleFile))
    {
        return ErrorCode::fileOpenFail;
    }

    readHeaderFile();

    return ErrorCode::ok;
}

error AssetPackageFile::addAssetFile(const std::string& file_path, const std::string& asset_key, unsigned version)
{
    assert(m_headerFile.is_open());
    assert(m_bundleFile.is_open());
    if ((file_path.empty()) || (asset_key.empty()))
    {
        return ErrorCode::emptyFileName;
    }
    unsigned int asset_ver = version;
    if (version == VERSION_USE_FILE_TIME)
    {
        asset_ver = getFileVersionWithModifyTime(file_path);
    }
    std::ifstream asset_file{ file_path, std::fstream::in | std::fstream::binary };
    if (asset_file.fail()) return ErrorCode::fileOpenFail;
    asset_file.seekg(0, std::fstream::end);
    const unsigned file_length = static_cast<unsigned>(asset_file.tellg());
    asset_file.seekg(0);
    std::vector<char> buff;
    buff.resize(file_length, 0);
    asset_file.read(buff.data(), file_length);
    if (!asset_file)
    {
        asset_file.close();
        return ErrorCode::fileReadFail;
    }
    const error add_result = addAssetMemory(buff, asset_key, asset_ver);

    asset_file.close();
    return add_result;
}

error AssetPackageFile::addAssetMemory(const std::vector<char>& buff, const std::string& asset_key, unsigned version)
{
    assert(m_headerFile.is_open());
    assert(m_bundleFile.is_open());
    if (buff.empty())
    {
        return ErrorCode::emptyBuffer;
    }
    if (asset_key.empty())
    {
        return ErrorCode::emptyKey;
    }
    unsigned long comp_length = compressBound(static_cast<uLong>(buff.size()));
    std::vector<unsigned char> comp_buff;
    comp_buff.resize(comp_length, 0);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    const int comp_result = compress(comp_buff.data(), &comp_length, reinterpret_cast<const unsigned char*>(buff.data()), static_cast<uLong>(buff.size()));
    if (comp_result != Z_OK)
    {
        return ErrorCode::compressFail;
    }

    const std::lock_guard<std::mutex> locker{ m_bundleFileLocker };

    m_bundleFile.seekp(0, std::fstream::end);
    const unsigned int bundle_offset = static_cast<unsigned int>(m_bundleFile.tellp());
    AssetHeaderData header_data;
    header_data.m_name = asset_key;
    header_data.m_offset = bundle_offset;
    header_data.m_orgSize = static_cast<unsigned int>(buff.size());
    header_data.m_size = comp_length;
    header_data.m_version = version;
    header_data.m_crc = 0;

    error er = m_nameList->appendAssetName(asset_key);
    if (er) return er;
    er = m_headerDataMap->insertHeaderData(header_data);
    if (er)
    {
        // header add 失敗, 要再把 name list 改回
        [[maybe_unused]] const error er_remove = m_nameList->removeAssetName(asset_key);
        return er;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    m_bundleFile.write(reinterpret_cast<const char*>(comp_buff.data()), comp_length);
    m_bundleFile.flush();

    m_assetCount++;

    saveHeaderFile();

    return ErrorCode::ok;
}

error AssetPackageFile::tryRetrieveAssetToFile(const std::string& file_path, const std::string& asset_key)
{
    if (file_path.empty())
    {
        return ErrorCode::emptyFileName;
    }
    if (asset_key.empty())
    {
        return ErrorCode::emptyKey;
    }
    const unsigned int asset_orig_size = getAssetOriginalSize(asset_key);
    if (asset_orig_size == 0) return ErrorCode::zeroSizeAsset;
    const auto buff = tryRetrieveAssetToMemory(asset_key);
    if (!buff)
    {
        return ErrorCode::emptyBuffer;
    }

    std::ofstream output_file{ file_path, std::fstream::out | std::fstream::binary | std::fstream::trunc };
    if (!output_file) return ErrorCode::fileOpenFail;

    output_file.write(buff.value().data(), asset_orig_size);
    if (!output_file) return ErrorCode::fileWriteFail;
    const auto write_bytes = output_file.tellp();

    output_file.close();

    if (write_bytes != asset_orig_size) return ErrorCode::writeSizeCheck;

    return ErrorCode::ok;
}

std::optional<std::vector<char>> AssetPackageFile::tryRetrieveAssetToMemory(const std::string& asset_key)
{
    assert(m_bundleFile);

    if (asset_key.empty()) return std::nullopt;
    const unsigned int asset_orig_size = getAssetOriginalSize(asset_key);
    if (asset_orig_size == 0) return std::nullopt;

    const auto header_data = tryGetAssetHeaderData(asset_key);
    if (!header_data) return std::nullopt;

    auto [comp_buff, read_bytes] = readBundleContent(header_data->m_offset, header_data->m_size);

    if (read_bytes != header_data->m_size) return std::nullopt;

    auto buff_out_length = static_cast<unsigned long>(asset_orig_size);
    std::vector<char> buff;
    buff.resize(buff_out_length, 0);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    const int z_result = uncompress(reinterpret_cast<unsigned char*>(buff.data()), &buff_out_length, reinterpret_cast<const unsigned char*>(comp_buff.data()), header_data->m_size);
    if (z_result != Z_OK) return std::nullopt;

    return buff;
}

unsigned int AssetPackageFile::getAssetOriginalSize(const std::string& asset_key) const
{
    assert(m_headerDataMap);

    if (asset_key.empty()) return 0;
    const auto header_data = tryGetAssetHeaderData(asset_key);
    if (!header_data) return 0;
    return header_data->m_orgSize;
}

time_t AssetPackageFile::getAssetTimeStamp(const std::string& asset_key) const
{
    assert(m_headerDataMap);

    if (asset_key.empty()) return 0;

    const auto header_data = tryGetAssetHeaderData(asset_key);
    if (!header_data) return 0;

    const unsigned int ver = header_data->m_version;
    return getTimeStampFromFileVersion(ver);
}

error AssetPackageFile::removeAsset(const std::string& asset_key)
{
    if (asset_key.empty()) return ErrorCode::emptyKey;
    if (!m_headerDataMap) return ErrorCode::invalidHeaderData;
    if (!m_nameList) return ErrorCode::invalidNameList;
    const auto header_data = tryGetAssetHeaderData(asset_key);
    if (!header_data) return ErrorCode::invalidHeaderData;
    const unsigned int content_size = header_data->m_size;
    const unsigned int content_offset = header_data->m_offset;

    error er = repackBundleContent(content_size, content_offset);
    if (er) return er;

    // 前面都檢查過可以移除，所以這後面的 error 都做 assert
    er = m_nameList->removeAssetName(asset_key);
    assert(!er);
    m_headerDataMap->repackContentOffsets(content_size, content_offset);
    er = m_headerDataMap->removeHeaderData(asset_key);
    assert(!er);
    saveHeaderFile();

    return ErrorCode::ok;
}

std::optional<AssetHeaderDataMap::AssetHeaderData> AssetPackageFile::tryGetAssetHeaderData(
    const std::string& asset_key) const
{
    assert(m_headerDataMap);
    return m_headerDataMap->tryGetHeaderData(asset_key);
}

void AssetPackageFile::resetPackage()
{
    if (m_headerFile.is_open())
    {
        m_headerFile.close();
    }
    if (m_bundleFile.is_open())
    {
        m_bundleFile.close();
    }
    m_formatTag = PACKAGE_FORMAT_TAG;
    m_fileVersion = 0;
    m_assetCount = 0;
    m_nameList = nullptr;
    m_headerDataMap = nullptr;
}

void AssetPackageFile::saveHeaderFile()
{
    // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
    assert(m_headerFile.is_open());
    const std::lock_guard<std::mutex> locker{ m_headerFileLocker };
    m_headerFile.seekp(0);

    //m_headerFile << m_formatTag << m_fileVersion << m_assetCount;
    m_headerFile.write(reinterpret_cast<const char*>(&m_formatTag), sizeof(m_formatTag));
    m_headerFile.write(reinterpret_cast<const char*>(&m_fileVersion), sizeof(m_fileVersion));
    m_headerFile.write(reinterpret_cast<const char*>(&m_assetCount), sizeof(m_assetCount));

    assert(m_nameList);
    const std::vector<char> name_buff = m_nameList->exportToByteBuffer();
    const auto name_list_byte_size = static_cast<unsigned int>(name_buff.size());
    m_headerFile.write(reinterpret_cast<const char*>(&name_list_byte_size), sizeof(name_list_byte_size));
    if (name_list_byte_size > 0)
    {
        m_headerFile.write(name_buff.data(), name_list_byte_size);
    }

    assert(m_headerDataMap);
    const std::vector<char> header_buff = m_headerDataMap->exportToByteBuffer();
    const auto header_byte_size = static_cast<unsigned int>(header_buff.size());
    m_headerFile.write(reinterpret_cast<const char*>(&header_byte_size), sizeof(header_byte_size));
    if (header_byte_size > 0)
    {
        m_headerFile.write(header_buff.data(), header_byte_size);
    }

    m_headerFile.flush();
    // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
}

void AssetPackageFile::readHeaderFile()
{
    // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
    assert(m_headerFile.is_open());
    const std::lock_guard<std::mutex> locker{ m_headerFileLocker };
    m_headerFile.seekg(0);

    //m_headerFile >> m_formatTag >> m_fileVersion >> m_assetCount;
    m_headerFile.read(reinterpret_cast<char*>(&m_formatTag), sizeof(m_formatTag));
    m_headerFile.read(reinterpret_cast<char*>(&m_fileVersion), sizeof(m_fileVersion));
    m_headerFile.read(reinterpret_cast<char*>(&m_assetCount), sizeof(m_assetCount));

    unsigned int name_list_byte_size = 0;
    m_headerFile.read(reinterpret_cast<char*>(&name_list_byte_size), sizeof(name_list_byte_size));
    std::vector<char> name_buff;
    if (name_list_byte_size > 0)
    {
        name_buff.resize(name_list_byte_size, 0);
        m_headerFile.read(name_buff.data(), name_list_byte_size);
    }
    m_nameList = std::make_unique<AssetNameList>();
    error er = m_nameList->importFromByteBuffer(name_buff);
    assert(!er);

    unsigned int header_byte_size = 0;
    m_headerFile.read(reinterpret_cast<char*>(&header_byte_size), sizeof(header_byte_size));
    std::vector<char> header_buff;
    if (header_byte_size > 0)
    {
        header_buff.resize(header_byte_size, 0);
        m_headerFile.read(header_buff.data(), header_byte_size);
    }
    m_headerDataMap = std::make_unique<AssetHeaderDataMap>();
    er = m_headerDataMap->importFromByteBuffer(header_buff);
    assert(!er);
    // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
}

std::tuple<std::vector<char>, unsigned int> AssetPackageFile::readBundleContent(unsigned int offset,
    unsigned int content_size)
{
    assert(m_bundleFile.is_open());
    const std::lock_guard<std::mutex> locker{ m_bundleFileLocker };
    m_bundleFile.seekg(offset);
    std::vector<char> out_buff;
    out_buff.resize(content_size, 0);
    m_bundleFile.read(out_buff.data(), content_size);
    if (!m_bundleFile) return { out_buff, 0 };
    return { out_buff, static_cast<unsigned int>(m_bundleFile.tellg()) - offset };
}

error AssetPackageFile::repackBundleContent(unsigned int content_size, unsigned int base_offset)
{
    assert(m_bundleFile.is_open());

    const std::lock_guard<std::mutex> locker{ m_bundleFileLocker };

    m_bundleFile.seekp(0, std::fstream::end);
    const auto bundle_org_size = m_bundleFile.tellp();
    if (bundle_org_size == 0) return ErrorCode::fileSizeError;
    std::vector<char> file_buff;
    file_buff.resize(bundle_org_size, 0);
    m_bundleFile.seekg(0);
    m_bundleFile.read(file_buff.data(), bundle_org_size);
    const auto read_bytes = m_bundleFile.tellg();
    if (read_bytes != bundle_org_size) return ErrorCode::readSizeCheck;

    file_buff.erase(file_buff.begin() + base_offset, file_buff.begin() + base_offset + content_size);
    m_bundleFile.seekp(0);
    m_bundleFile.write(file_buff.data(), static_cast<std::streamsize>(file_buff.size()));
    m_bundleFile.flush();
    return ErrorCode::ok;
}

// NOLINTEND(clang-analyzer-optin.core.EnumCastOutOfRange)