/*!
file:   render_manager.h
author: Wong Man Cong

email:  w.mancong@digipen.edu

brief:  Render manager to handle what to render onto screen first
        Smallest to biggest -> order = 1 will be rendered first compared to
                    order = 10 will be rendered last (on top of everything else)

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________________________________*/
#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "common_headers.h"

typedef enum RenderOrder
{
    NO_ORDER = -1,
    BOTTOM_LAYER,
    BACKGROUND_LAYER,
    TOWER_LAYER,            // drawing of towers when playing
    PATH_LAYER,             // drawing of enemies when playing
    RADIUS_LAYER,
    SELECTED_ENEMY_LAYER,   // using this when toggling the enemy
    ENEMY_LAYER,
    EDITING_LAYER,
    LOGO_LAYER,             // logo inside main menu
    OVERLAY_LAYER,          
    LEVEL_PREVIEW_LAYER,    // inside main menu, when want to preview the levels
    GRID_LINE_LAYER,        // grid lines when placing towers
    ABLE_TO_BUILD_LAYER,    // layer to check if it's able to build onto grid
    DRAW_TOWER_LAYER,       // when trying to place the tower
    UI_LAYER,
    HOTKEY_LAYER,           // Hotkeys images
    INFO_LAYER,             // layer to render infomation above hotkeys
    QUAD_TREE_LAYER,        // drawing of quad tree lines for debugging
    COOLDOWN_LAYER,
    TEXT_LAYER,
    CORRECT_TEXT_LAYER,
    // can add new variables here...
    PAUSE_LAYER,
    PAUSE_BUTTON_LAYER,
    TOP_LAYER,
}RenderOrder;

void DefaultRenderManager(void);
void InitRenderManager(void);
void AddSprite(CP_Image img, float x, float y, float w, float h, int alpha, RenderOrder order);
void AddText(const char* str, float x, float y, float size, CP_Color color, CP_TEXT_ALIGN_HORIZONTAL h, CP_TEXT_ALIGN_VERTICAL v, RenderOrder order);
void AddPoint(float x, float y, float stroke_weight, CP_Color color, RenderOrder order);
void AddLine(float x1, float y1, float x2, float y2, float stroke_weight, CP_Color color, RenderOrder order);
void AddRect(float x, float y, float w, float h, float stroke_weight, CP_Color color, RenderOrder order);
void AddCircle(float x, float y, float radius, float stroke_weight, CP_Color color, RenderOrder order);
void AddEllipse(float x, float y, float w, float h, float stroke_weight, CP_Color color, RenderOrder order);
void AddTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float stroke_weight, CP_Color color, RenderOrder order);
void AddQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float stroke_weight, CP_Color color, RenderOrder order);
void SetBackgroundColor(CP_Color bg);
void SetFont(CP_Font f);
void RenderAll(void);
void ResetRenderManagerVariables(unsigned max);

#endif