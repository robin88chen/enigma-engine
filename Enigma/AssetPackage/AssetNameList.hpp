/*****************************************************************
 * \file   AssetNameList.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef ASSET_NAME_LIST_HPP
#define ASSET_NAME_LIST_HPP

#include <string>
#include <unordered_set>
#include <system_error>
#include <vector>

namespace AssetPackage
{
    using error = std::error_code;
    class AssetNameList
    {
    public:
        AssetNameList();
        AssetNameList(const AssetNameList&) = delete;
        AssetNameList(AssetNameList&&) = delete;
        ~AssetNameList() noexcept;

        AssetNameList& operator=(const AssetNameList&) = delete;
        AssetNameList& operator=(AssetNameList&&) = delete;

        bool hasAssetName(const std::string& name);
        error appendAssetName(const std::string& name);
        error removeAssetName(const std::string& name);

        [[nodiscard]] size_t getNameCount() const { return m_assetNames.size(); };

        [[nodiscard]] size_t calcNameListDataBytes() const;

        [[nodiscard]] std::unordered_set<std::string> getAssetNames() const { return m_assetNames; }

        [[nodiscard]] std::vector<char> exportToByteBuffer() const;
        error importFromByteBuffer(const std::vector<char>& buff);

    private:
        std::unordered_set<std::string> m_assetNames;
    };
}

#endif // ASSET_NAME_LIST_HPP
