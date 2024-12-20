/*****************************************************************
 * \file   AssetPackagePanel.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef ASSET_PACKAGE_PANEL_HPP
#define ASSET_PACKAGE_PANEL_HPP

#include <nana/gui/widgets/panel.hpp>

namespace AssetPackage
{
    class AssetPackageFile;
}

namespace AssetPackageTool
{
    class AssetPackagePanel : public nana::panel<false>
    {
    public:
        AssetPackagePanel(nana::window wd, const std::shared_ptr<AssetPackage::AssetPackageFile>& package);
        virtual ~AssetPackagePanel() override;
        AssetPackagePanel(const AssetPackagePanel&) = delete;
        AssetPackagePanel& operator=(const AssetPackagePanel&) = delete;
        AssetPackagePanel(AssetPackagePanel&&) = delete;
        AssetPackagePanel& operator=(AssetPackagePanel&&) = delete;

        void initialize();

    private:
        /*void OnBrowseRootButton(const nana::arg_click& ev);
        void OnAddFilesButton(const nana::arg_click& ev);
        void OnAddDirectoryButton(const nana::arg_click& ev);
        void OnExtractSelectedAsset(nana::menu::item_proxy& menu_item);
        void OnDeleteSelectedAsset(nana::menu::item_proxy& menu_item);

        void AddPackageFile(const std::string& filepath);
        std::string SplitAssetKeyName(const std::string& filepath);
        void RefreshAssetsList();

        void PopupErrorMessage(const std::error_code& er);*/
    private:
        /*nana::place* m_place;
        nana::label* m_rootDirLabel;
        nana::button* m_browseButton;
        nana::listbox* m_assetListbox;
        nana::button* m_addFilesButton;
        nana::button* m_addDirButton;
        nana::label* m_rootDirPrompt;

        nana::menu* m_assetSelectedMenu;*/

        std::shared_ptr<AssetPackage::AssetPackageFile> m_packageFile;
    };

}

#endif // ASSET_PACKAGE_PANEL_HPP
