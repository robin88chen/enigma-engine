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

namespace AssetPackageTool
{
    class MainForm : public nana::form
    {
    public:
        MainForm();
        virtual ~MainForm();

        void initialize();
    private:
        //void initMenu();

        //void OnCloseCommand(nana::menu::item_proxy& menu_item);
        //void OnCreatePackage(nana::menu::item_proxy& menu_item);
        //void OnOpenPackage(nana::menu::item_proxy& menu_item);
    private:
        std::shared_ptr<nana::place> m_place;
        //nana::menubar* m_menubar;
        //nana::tabbar<int>* m_tabbar;
        //std::vector<AssetPackagePanel*> m_assetPanels;
    };
}


#endif // MAIN_FORM_HPP
