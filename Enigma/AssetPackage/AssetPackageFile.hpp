/*****************************************************************
 * \file   AssetPackageFile.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef ASSET_PACKAGE_FILE_HPP
#define ASSET_PACKAGE_FILE_HPP

#include "AssetHeaderDataMap.hpp"
#include <system_error>
#include <string>
#include <fstream>
#include <mutex>
#include <optional>
#include <vector>
#include <memory>
#include <tuple>

namespace AssetPackage
{
    class AssetNameList;

    using error = std::error_code;
    class AssetPackageFile
    {
    public:
        constexpr static unsigned int VERSION_USE_FILE_TIME = 0;
    public:
        AssetPackageFile(const AssetPackageFile&) = delete;
        AssetPackageFile(AssetPackageFile&&) = delete;
        ~AssetPackageFile() noexcept;
        AssetPackageFile& operator=(const AssetPackageFile&) = delete;
        AssetPackageFile& operator=(AssetPackageFile&&) = delete;

        const std::string& getBaseFilename() { return m_baseFilename; };
        static std::shared_ptr<AssetPackageFile> createNewPackage(const std::string& base_filename);
        static std::shared_ptr<AssetPackageFile> openPackage(const std::string& base_filename);

        error addAssetFile(const std::string& file_path, const std::string& asset_key, unsigned version);
        error addAssetMemory(const std::vector<char>& buff, const std::string& asset_key, unsigned version);
        error tryRetrieveAssetToFile(const std::string& file_path, const std::string& asset_key);
        std::optional<std::vector<char>> tryRetrieveAssetToMemory(const std::string& asset_key);
        [[nodiscard]] unsigned getAssetOriginalSize(const std::string& asset_key) const;
        [[nodiscard]] time_t getAssetTimeStamp(const std::string& asset_key) const;

        error removeAsset(const std::string& asset_key);

        const std::unique_ptr<AssetNameList>& getAssetNameList() { return m_nameList; };
        [[nodiscard]] std::optional<AssetHeaderDataMap::AssetHeaderData> tryGetAssetHeaderData(const std::string& asset_key) const;
    private:
        AssetPackageFile();
        error createNewPackageImp(const std::string& base_filename);
        error openPackageImp(const std::string& base_filename);
        void resetPackage();

        void saveHeaderFile();
        void readHeaderFile();

        std::tuple<std::vector<char>, unsigned int> readBundleContent(unsigned int offset, unsigned int content_size);
        error repackBundleContent(unsigned int content_size, unsigned int base_offset);

    private:
        unsigned int m_formatTag;
        unsigned int m_fileVersion;
        unsigned int m_assetCount;
        std::unique_ptr<AssetNameList> m_nameList;
        std::unique_ptr<AssetHeaderDataMap> m_headerDataMap;

        std::string m_baseFilename;
        std::fstream m_headerFile;
        std::fstream m_bundleFile;

        std::mutex m_headerFileLocker;
        std::mutex m_bundleFileLocker;
    };

}

#endif // ASSET_PACKAGE_FILE_HPP
