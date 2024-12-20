/*****************************************************************
 * \file   menu_skin_renderer.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef MENU_SKIN_RENDERER_HPP
#define MENU_SKIN_RENDERER_HPP

#include <nana/gui/widgets/menu.hpp>
#include <nana/gui/element.hpp>

 // ReSharper disable once CppInconsistentNaming
class menu_skin_renderer final : public nana::drawerbase::menu::renderer_interface
{
public:
    menu_skin_renderer();
    virtual void background(graph_reference, nana::window) override;
    virtual void item(graph_reference, const nana::rectangle&, const attr&) override;
    virtual void item_image(graph_reference, const nana::point&, unsigned image_px, const nana::paint::image&) override;
    virtual void item_text(graph_reference, const nana::point&, const std::string&, unsigned text_pixels, const attr&) override;
    virtual void sub_arrow(graph_reference, const nana::point&, unsigned item_pixels, const attr&) override;
private:
    nana::facade<nana::element::crook> m_crook;
};
#endif // MENU_SKIN_RENDERER_HPP
