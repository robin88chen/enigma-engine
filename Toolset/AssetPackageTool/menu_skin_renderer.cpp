#include "menu_skin_renderer.hpp"
#include "SchemeColorDef.hpp"
#include <nana/paint/text_renderer.hpp>

menu_skin_renderer::menu_skin_renderer() : m_crook("menu_crook")
{
    m_crook.check(nana::facade<nana::element::crook>::state::checked);
}
void menu_skin_renderer::background(graph_reference graph, nana::window wd)
{
    nana::size sz = graph.size();
    unsigned int left_width = 30u; // nana::platform::dpi_scale(wd, 30u);
    unsigned int unit = 1u; // platform_abstraction::dpi_scale(wd, 1u);
    sz.width -= left_width;
    sz.height -= 2;
    graph.rectangle(false, AssetPackageTool::UISchemeColors::m_menuBarBorder); // nana::colors::gray_border);
    graph.rectangle({ 1, 1, left_width - unit, sz.height }, true, AssetPackageTool::UISchemeColors::m_menuBarSelectBackground); // static_cast<nana::color_rgb>(0xf6f6f6));
    graph.rectangle({ static_cast<int>(left_width - unit), 1, sz.width, sz.height }, true, AssetPackageTool::UISchemeColors::m_menuBarSelectBackground); // nana::colors::white);
}

void menu_skin_renderer::item(graph_reference graph, const nana::rectangle& r, const attr& at)
{
    if (!at.enabled)
        return;

    if (at.item_state == state::active)
    {
        graph.rectangle(r, false, AssetPackageTool::UISchemeColors::m_menuBarBorder); // static_cast<nana::color_rgb>(0xa8d8eb));

        graph.palette(false, AssetPackageTool::UISchemeColors::m_menuBarBorder); // static_cast<nana::color_rgb>(0xc0ddfc));
        nana::paint::draw(graph).corner(r, 1);

        if (at.enabled)
            graph.gradual_rectangle(nana::rectangle(r).pare_off(1), AssetPackageTool::UISchemeColors::m_menuBarBackground, AssetPackageTool::UISchemeColors::m_menuBarBackground, true); // static_cast<nana::color_rgb>(0xE8F0F4), static_cast<nana::color_rgb>(0xDBECF4), true);
    }

    if (at.checked && (nana::menu::checks::none != at.check_style))
    {
        // 用到的時候再改
        graph.rectangle(r, false, static_cast<nana::color_rgb>(0xCDD3E6));

        ::nana::color clr(0xE6, 0xEF, 0xF4);
        graph.rectangle(nana::rectangle(r).pare_off(1), true, clr);

        nana::rectangle crook_r = r;
        crook_r.width = 16;
        m_crook.radio(at.check_style == nana::menu::checks::option);
        m_crook.draw(graph, clr, nana::colors::black, crook_r, nana::element_state::normal);
    }
}

void menu_skin_renderer::item_image(graph_reference graph, const nana::point& pos, unsigned image_px, const nana::paint::image& img)
{
    // 用到的時候再改
}

void menu_skin_renderer::item_text(graph_reference graph, const nana::point& pos, const std::string& text, unsigned text_pixels, const attr& at)
{
    graph.palette(true, at.enabled ? AssetPackageTool::UISchemeColors::m_menuBarForeground : AssetPackageTool::UISchemeColors::m_menuBarBorder);
    nana::paint::text_renderer tr(graph);

    auto wstr = nana::to_wstring(text);
    tr.render(pos, { wstr.c_str(), wstr.length() }, text_pixels, nana::paint::text_renderer::mode::truncate_with_ellipsis);
}

void menu_skin_renderer::sub_arrow(graph_reference graph, const nana::point& pos, unsigned item_pixels, const attr& at)
{
    // 用到的時候再改
}
