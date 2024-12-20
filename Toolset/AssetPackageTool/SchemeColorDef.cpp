#include "SchemeColorDef.hpp"

nana::color s_bgBlack(45, 45, 48);
nana::color s_fgWhite(241, 241, 241);
nana::color s_bgSelect(32, 32, 32);
nana::color s_bgHighlight(62, 62, 64);
nana::color s_bgMenuBar(46, 52, 64);
nana::color s_fgMenuBar(236, 239, 244);
nana::color s_bgMenuBarSelect(59, 66, 82);
nana::color s_borderMenuBar(76, 86, 106);
nana::color s_bgTabBarItem(59, 66, 82);
nana::color s_bgTabBarItemHighlight(67, 76, 94);
nana::color AssetPackageTool::UISchemeColors::BACKGROUND(s_bgBlack);
nana::color AssetPackageTool::UISchemeColors::FOREGROUND(s_fgWhite);
nana::color AssetPackageTool::UISchemeColors::SELECT_BG(s_bgSelect);
nana::color AssetPackageTool::UISchemeColors::HIGHLIGHT_BG(s_bgHighlight);
nana::color AssetPackageTool::UISchemeColors::m_menuBarBackground(s_bgMenuBar);
nana::color AssetPackageTool::UISchemeColors::m_menuBarForeground(s_fgMenuBar);
nana::color AssetPackageTool::UISchemeColors::m_menuBarSelectBackground(s_bgMenuBarSelect);
nana::color AssetPackageTool::UISchemeColors::m_menuBarBorder(s_borderMenuBar);
nana::color AssetPackageTool::UISchemeColors::m_tabBarItemBackground(s_bgTabBarItem);
nana::color AssetPackageTool::UISchemeColors::m_tabBarItemBackgroundHighlight(s_bgTabBarItemHighlight);

void AssetPackageTool::UISchemeColors::applySchemaColors(nana::widget_geometrics& scheme)
{
    scheme.background = UISchemeColors::BACKGROUND;
    scheme.foreground = UISchemeColors::FOREGROUND;
}
