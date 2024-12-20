/*****************************************************************
 * \file   MainForm.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef MAIN_FORM_HPP
#define MAIN_FORM_HPP

#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>

namespace AssetPackageTool
{
    class MainForm final : public nana::form
    {
    public:
        MainForm();
        MainForm(const MainForm&) = delete;
        MainForm& operator=(const MainForm&) = delete;
        virtual ~MainForm() override;
        MainForm(MainForm&&) = delete;
        MainForm& operator=(MainForm&&) = delete;

        void initialize();
    private:
        void initMenu();

        void onCloseCommand(nana::menu::item_proxy& menu_item);
        void onCreatePackage(nana::menu::item_proxy& menu_item);
        void onOpenPackage(nana::menu::item_proxy& menu_item);
    private:
        std::shared_ptr<nana::place> m_place;
        std::shared_ptr<nana::menubar> m_menuBar;
        //nana::tabbar<int>* m_tabbar;
        //std::vector<AssetPackagePanel*> m_assetPanels;
    };
}


#endif // MAIN_FORM_HPP
