#include "tabbar_item_skin_renderer.hpp"
#include "SchemeColorDef.hpp"
#include <nana/gui/element.hpp>

void tabbar_item_skin_renderer::background(graph_reference graph, const nana::rectangle& r, const nana::color& bgcolor)
{
    graph.rectangle(true, AssetPackageTool::UISchemeColors::m_menuBarBackground);
}

void tabbar_item_skin_renderer::item(graph_reference graph, const item_t& m, bool active, state_t sta)
{
    const nana::rectangle& r = m.r;
    if ((active) || (sta == item_renderer::highlight))

    {
        graph.rectangle(r, true, AssetPackageTool::UISchemeColors::m_tabBarItemBackgroundHighlight);
    }
    else
    {
        graph.rectangle(r, true, AssetPackageTool::UISchemeColors::m_tabBarItemBackground);
    }
}

void tabbar_item_skin_renderer::close(graph_reference graph, const nana::rectangle& r, state_t sta)
{
    nana::facade<nana::element::x_icon> x_icon;
    x_icon.draw(graph, {}, AssetPackageTool::UISchemeColors::m_menuBarForeground, { r.x + static_cast<int>(r.width - 16) / 2, r.y + static_cast<int>(r.height - 16) / 2, 16, 16 }, nana::element_state::normal);
}
