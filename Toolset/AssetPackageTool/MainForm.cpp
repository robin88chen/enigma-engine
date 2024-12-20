#include "MainForm.hpp"
#include "SchemeColorDef.hpp"
#include "AssetPackagePanel.hpp"
#include "menu_skin_renderer.hpp"
#include "tabbar_item_skin_renderer.hpp"
#include "AssetPackage/AssetPackage.hpp"
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/filebox.hpp>

using namespace AssetPackageTool;

MainForm::MainForm()
{
    m_place = nullptr;
}

MainForm::~MainForm()
{
    m_place = nullptr;
    m_menuBar = nullptr;
    m_tabBar = nullptr;
    m_assetPanels.clear();
}

void MainForm::initialize()
{
    m_place = std::make_shared<nana::place>(*this);
    m_place->div("vert<menubar weight=28><tabbar weight=28><tabframe>");
    initMenu();
    m_tabBar = std::make_shared<nana::tabbar<int>>(*this);
    m_tabBar->scheme().background = UISchemeColors::m_menuBarBackground;
    m_tabBar->scheme().foreground = UISchemeColors::m_menuBarForeground;
    m_tabBar->renderer(tabbar_item_skin_renderer());
    m_place->field("tabbar") << *m_tabBar;
    m_place->collocate();
}

void MainForm::initMenu()
{
    m_menuBar = std::make_shared<nana::menubar>(*this);
    m_menuBar->scheme().background = UISchemeColors::m_menuBarBackground;
    m_menuBar->scheme().body_selected = UISchemeColors::m_menuBarSelectBackground;
    m_menuBar->scheme().body_highlight = UISchemeColors::m_menuBarSelectBackground;
    m_menuBar->scheme().text_fgcolor = UISchemeColors::m_menuBarForeground;
    m_menuBar->scheme().border_highlight = UISchemeColors::m_menuBarBorder;
    m_menuBar->scheme().border_selected = UISchemeColors::m_menuBarBorder;
    m_menuBar->scheme().activated = UISchemeColors::m_menuBarSelectBackground;
    m_menuBar->scheme().foreground = UISchemeColors::m_menuBarForeground;
    nana::menu& menu = m_menuBar->push_back("&FILE");
    menu.renderer(menu_skin_renderer());
    m_menuBar->at(0).append("Create Package", [this](auto item) { onCreatePackage(item); });
    m_menuBar->at(0).append("Open Package", [this](auto item) { onOpenPackage(item); });
    m_menuBar->at(0).append_splitter();
    m_menuBar->at(0).append("Exit", [this](auto item) { onCloseCommand(item); });
    m_place->field("menubar") << *m_menuBar;
}

void MainForm::onCloseCommand(nana::menu::item_proxy& menu_item)
{
    close();
}

void MainForm::onCreatePackage(nana::menu::item_proxy& menu_item)
{
    nana::filebox file_dlg{ *this, false };
    const auto paths = file_dlg.title("Create New Package").add_filter("package file", "*.eph").show();
    if (paths.empty()) return;

    std::string base_filename = paths[0].generic_string();
    const size_t pos = base_filename.find_last_of('.');
    base_filename = base_filename.substr(0, pos);
    auto package = AssetPackage::AssetPackageFile::createNewPackage(base_filename);
    const auto p = std::make_shared<AssetPackagePanel>(*this, package);
    p->initialize();
    m_place->field("tabframe").fasten(*p);
    m_tabBar->append(paths[0].filename().stem(), *p);
    m_tabBar->toolbox(nana::drawerbase::tabbar::trigger::kits::close, true);
    //tab.renderer(tabbar_item_skin_renderer());
    m_place->collocate();

    m_assetPanels.emplace_back(p);
}

void MainForm::onOpenPackage(nana::menu::item_proxy& menu_item)
{
    /*nana::filebox file_dlg{ *this, true };
    auto paths = file_dlg.title("Open Package").add_filter("package file", "*.eph").show();
    if (paths.empty()) return;

    std::string baseFilename = paths[0].generic_string();
    size_t pos = baseFilename.find_last_of('.');
    baseFilename = baseFilename.substr(0, pos);

    AssetPackageFile* package = AssetPackageFile::OpenPackage(baseFilename);
    AssetPackagePanel* p = new AssetPackagePanel{ *this, package };
    p->Initialize();
    m_place->field("tabframe").fasten(*p);
    m_tabbar->append(paths[0].filename().stem(), *p);
    m_place->collocate();

    m_assetPanels.emplace_back(p);*/
}