/*****************************************************************
 * \file   AssetHeaderDataMap.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef ASSET_HEADER_DATA_MAP_HPP
#define ASSET_HEADER_DATA_MAP_HPP

#include <string>
#include <unordered_map>
#include <optional>
#include <system_error>
#include <vector>

namespace AssetPackage
{
    using error = std::error_code;
    class AssetHeaderDataMap
    {
    public:
        struct AssetHeaderData
        {
            std::string m_name;
            unsigned int m_version;
            unsigned int m_size;
            unsigned int m_orgSize;
            unsigned int m_offset;
            unsigned int m_crc;
            AssetHeaderData() : m_name{ "" }, m_version{ 0 }, m_size{ 0 }, m_orgSize{ 0 }, m_offset{ 0 }, m_crc{ 0 } {};
        };
    public:
        AssetHeaderDataMap();
        AssetHeaderDataMap(const AssetHeaderDataMap&) = delete;
        AssetHeaderDataMap(AssetHeaderDataMap&&) = delete;
        ~AssetHeaderDataMap();

        AssetHeaderDataMap& operator=(const AssetHeaderDataMap&) = delete;
        AssetHeaderDataMap& operator=(AssetHeaderDataMap&&) = delete;

        error insertHeaderData(const AssetHeaderData& header);
        error removeHeaderData(const std::string& name);

        [[nodiscard]] bool hasAssetKey(const std::string& name) const;

        void repackContentOffsets(unsigned content_size, unsigned base_offset);

        std::optional<AssetHeaderData> tryGetHeaderData(const std::string& name);

        [[nodiscard]] size_t calcHeaderDataMapBytes() const;

        [[nodiscard]] size_t getTotalDataCount() const { return m_headerDataMap.size(); };

        [[nodiscard]] std::vector<char> exportToByteBuffer() const;
        [[nodiscard]] std::error_code importFromByteBuffer(const std::vector<char>& buff);

    private:
        std::unordered_map<std::string, AssetHeaderData> m_headerDataMap;
    };
};


#endif // ASSET_HEADER_DATA_MAP_HPP
