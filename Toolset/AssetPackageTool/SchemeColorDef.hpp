﻿/*********************************************************************
 * \file   SchemeColorDef.h
 * \brief  color define for UI scheme
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2020
 *********************************************************************/
#ifndef _VIEWER_COLOR_DEF_H
#define _VIEWER_COLOR_DEF_H

#include "nana/basic_types.hpp"
#include "nana/gui/detail/widget_geometrics.hpp"
namespace AssetPackageTool
{
    class UISchemeColors
    {
    public:
        static void applySchemaColors(nana::widget_geometrics& scheme);
        static nana::color BACKGROUND;
        static nana::color FOREGROUND;
        static nana::color SELECT_BG;
        static nana::color HIGHLIGHT_BG;
        static nana::color m_menuBarBackground;
        static nana::color m_menuBarForeground;
        static nana::color m_menuBarSelectBackground;
        static nana::color m_menuBarBorder;
    };
}
#endif // !_VIEWER_COLOR_DEF_H
