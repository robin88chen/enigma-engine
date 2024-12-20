/*****************************************************************
 * \file   tabbar_item_skin_renderer.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef TABBAR_ITEM_SKIN_RENDERER_HPP
#define TABBAR_ITEM_SKIN_RENDERER_HPP
#include <nana/gui/widgets/tabbar.hpp>

 // ReSharper disable once CppInconsistentNaming
// NOLINTNEXTLINE(readability-identifier-naming)
class tabbar_item_skin_renderer final : public nana::drawerbase::tabbar::item_renderer
{
public:
    void background(graph_reference, const nana::rectangle& r, const ::nana::color& bgcolor) override;
    void item(graph_reference, const item_t&, bool active, state_t) override;
    void close_fly(graph_reference, const nana::rectangle&, bool active, state_t) override {}

    void add(graph_reference, const nana::rectangle&, state_t) override {}
    void close(graph_reference, const nana::rectangle&, state_t) override;
    void back(graph_reference, const nana::rectangle&, state_t) override {}
    void next(graph_reference, const nana::rectangle&, state_t) override {}
    void list(graph_reference, const nana::rectangle&, state_t) override {}
};

#endif // TABBAR_ITEM_SKIN_RENDERER_HPP
