/*!
file:   render_manager.c
author: Wong Man Cong

email:  w.mancong@digipen.edu

brief:  Function defintions for render manager  

    Copyright © 2020 DigiPen, All rights reserved.      
*//*________________________________________________________*/
#include "render_manager.h"

typedef enum RenderType
{
    DRAW_NOTHING = -1,
    DRAW_IMAGE,
    DRAW_TEXT,
    DRAW_POINT,
    DRAW_LINE,
    DRAW_RECT,
    DRAW_CIRCLE,
    DRAW_ELLIPSE,
    DRAW_TRIANGLE,
    DRAW_QUAD,

}RenderType;

typedef struct RenderOrderData
{
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float size_x;
    float size_y;
    float stroke_weight;
    char* str;
    int alpha;
    CP_Image img;
    CP_Color color;
    CP_TEXT_ALIGN_HORIZONTAL h; 
    CP_TEXT_ALIGN_VERTICAL v;
    RenderOrder order;
    RenderType renderType;
} RenderOrderData;

//typedef RenderOrderDataStruct* RenderOrderData;

RenderOrderData* orderData = NULL;
const unsigned initSize = 10;
unsigned rmCurrIndex = 0, rmCurrSize = 0;
CP_Color background;
CP_Font font;

void TowersRender(void);
void DrawGrid(void);

#if LEVEL_EDITOR_MODE
void TypingBox(void);
#endif

void DefaultRenderManager(void)
{
    rmCurrIndex = 0;
    rmCurrSize = initSize;
    background = BACKGROUND_COLOR;
    font = DEFAULT_FONT;
}

void ResetRenderManagerVariables(unsigned max)
{
    rmCurrIndex = 0;
    for (unsigned i = 0; i < max; ++i)
    {
        orderData[i].x1 = CP_System_GetWindowWidth() * 10.0f;        // set it somewhere outside of the screen
        orderData[i].y1 = CP_System_GetWindowHeight() * 10.0f;       // set it somewhere outside of the screen
        orderData[i].x2 = CP_System_GetWindowWidth() * 10.0f;        // set it somewhere outside of the screen
        orderData[i].y2 = CP_System_GetWindowHeight() * 10.0f;       // set it somewhere outside of the screen
        orderData[i].size_x = 0.0f;
        orderData[i].size_y = 0.0f;
        orderData[i].stroke_weight = 1.0f;
        orderData[i].str = "";
        orderData[i].alpha = 0;
        orderData[i].img = NULL;;
        orderData[i].color = COLOR_WHITE;
        orderData[i].h = CP_TEXT_ALIGN_H_LEFT;
        orderData[i].v = CP_TEXT_ALIGN_V_BASELINE;
        orderData[i].order = NO_ORDER;
        orderData[i].renderType = DRAW_NOTHING;
    }
}

void InitRenderManager(void)
{
    if (!orderData)
    {
        orderData = (RenderOrderData*)malloc(sizeof(RenderOrderData) * initSize);
        ResetRenderManagerVariables(initSize);
    }
    ResetRenderManagerVariables(rmCurrSize);
}

void ReallocateOrderData(void)
{
    rmCurrSize *= 2;
    RenderOrderData* tmp = orderData;
    orderData = (RenderOrderData*)malloc(sizeof(RenderOrderData) * rmCurrSize);
    memcpy_s(orderData, sizeof(RenderOrderData) * rmCurrSize, tmp, sizeof(RenderOrderData) * (rmCurrSize >> 1));
    free(tmp);
}

void MergeRenderOrder(int left, int mid, int right)
{
    int sub1 = mid - left + 1;
    int sub2 = right - mid;

    RenderOrderData* left_temp =  (RenderOrderData*)malloc(sizeof(RenderOrderData) * sub1);
    RenderOrderData* right_temp = (RenderOrderData*)malloc(sizeof(RenderOrderData) * sub2);

    for (int i = 0; i < sub1; ++i)
    {
        if(left_temp + i)
            *(left_temp + i) = *(orderData + i + left);
    }
    for (int i = 0; i < sub2; ++i)
    {
        if(right_temp + i)
            *(right_temp + i) = *(orderData + mid + i + 1);
    }

    int first_index = 0, second_index = 0;
    int merge_index = left;
    while (first_index < sub1 && second_index < sub2)
    {
        if (!(left_temp + first_index) || !(right_temp + second_index))
            continue;
        if ((left_temp + first_index)->order <= (right_temp + second_index)->order)
            *(orderData + merge_index++) = *(left_temp + first_index++);
        else
            *(orderData + merge_index++) = *(right_temp + second_index++);
    }

    while (first_index < sub1)
    {
        if(left_temp + first_index)
            *(orderData + merge_index++) = *(left_temp + first_index++);
    }
    while (second_index < sub2)
    {
        if(right_temp + second_index)
            *(orderData + merge_index++) = *(right_temp + second_index++);
    }

    free(left_temp);
    free(right_temp);
}

void MergeSortRenderOrder(int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (int)((right - left) * 0.5f);
    MergeSortRenderOrder(left, mid);
    MergeSortRenderOrder(mid + 1, right);

    MergeRenderOrder(left, mid, right);
}

void AddSprite(CP_Image img, float x, float y, float w, float h, int alpha, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x;
    orderData[rmCurrIndex].y1 = y;
    orderData[rmCurrIndex].size_x = w;
    orderData[rmCurrIndex].size_y = h;
    orderData[rmCurrIndex].alpha = alpha;
    orderData[rmCurrIndex].img = img;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex++].renderType = DRAW_IMAGE;
}

void AddText(const char* str, float x, float y, float size, CP_Color color, CP_TEXT_ALIGN_HORIZONTAL h, CP_TEXT_ALIGN_VERTICAL v, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x;
    orderData[rmCurrIndex].y1 = y;
    orderData[rmCurrIndex].size_x = size;
    orderData[rmCurrIndex].str = str;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex].h = h;
    orderData[rmCurrIndex].v = v;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex++].renderType = DRAW_TEXT;
}

void AddPoint(float x, float y, float stroke_weight, CP_Color color, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x;
    orderData[rmCurrIndex].y1 = y;
    orderData[rmCurrIndex].stroke_weight = stroke_weight;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex++].renderType = DRAW_POINT;
}

void AddLine(float x1, float y1, float x2, float y2, float stroke_weight, CP_Color color, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x1;
    orderData[rmCurrIndex].y1 = y1;
    orderData[rmCurrIndex].x2 = x2;
    orderData[rmCurrIndex].y2 = y2;
    orderData[rmCurrIndex].stroke_weight = stroke_weight;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex++].renderType = DRAW_LINE;
}

void AddRect(float x, float y, float w, float h, float stroke_weight, CP_Color color, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x;
    orderData[rmCurrIndex].y1 = y;
    orderData[rmCurrIndex].size_x = w;
    orderData[rmCurrIndex].size_y = h;
    orderData[rmCurrIndex].stroke_weight = stroke_weight;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex++].renderType = DRAW_RECT;
}

void AddCircle(float x, float y, float radius, float stroke_weight, CP_Color color, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x;
    orderData[rmCurrIndex].y1 = y;
    orderData[rmCurrIndex].size_x = radius;
    orderData[rmCurrIndex].stroke_weight = stroke_weight;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex++].renderType = DRAW_CIRCLE;
}

void AddEllipse(float x, float y, float w, float h, float stroke_weight, CP_Color color, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x;
    orderData[rmCurrIndex].y1 = y;
    orderData[rmCurrIndex].size_x = w;
    orderData[rmCurrIndex].size_y = h;
    orderData[rmCurrIndex].stroke_weight = stroke_weight;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex++].renderType = DRAW_ELLIPSE;
}

void AddTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float stroke_weight, CP_Color color, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x1;
    orderData[rmCurrIndex].y1 = y1;
    orderData[rmCurrIndex].x2 = x2;
    orderData[rmCurrIndex].y2 = y2;
    orderData[rmCurrIndex].x3 = x3;
    orderData[rmCurrIndex].y3 = y3;
    orderData[rmCurrIndex].stroke_weight = stroke_weight;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex++].renderType = DRAW_TRIANGLE;
}

void AddQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float stroke_weight, CP_Color color, RenderOrder order)
{
    if (rmCurrIndex + 1 >= rmCurrSize)
        ReallocateOrderData();

    orderData[rmCurrIndex].x1 = x1;
    orderData[rmCurrIndex].y1 = y1;
    orderData[rmCurrIndex].x2 = x2;
    orderData[rmCurrIndex].y2 = y2;
    orderData[rmCurrIndex].x3 = x3; 
    orderData[rmCurrIndex].y3 = y3;
    orderData[rmCurrIndex].size_x = x4;
    orderData[rmCurrIndex].size_y = y4;
    orderData[rmCurrIndex].stroke_weight = stroke_weight;
    orderData[rmCurrIndex].order = order;
    orderData[rmCurrIndex].color = color;
    orderData[rmCurrIndex++].renderType = DRAW_QUAD;
}

void SetBackgroundColor(CP_Color bg)
{
    background = bg;
}

void SetFont(CP_Font f)
{
    font = f;
}

void RenderObjectType(RenderType type, unsigned index)
{
    switch (type)
    {
        case DRAW_IMAGE:
        { 
            CP_Image_Draw(orderData[index].img, orderData[index].x1, orderData[index].y1, orderData[index].size_x, orderData[index].size_y, orderData[index].alpha);
            break;
        }
        case DRAW_TEXT:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Font_Set(font);
            CP_Settings_TextSize(orderData[index].size_x);
            CP_Settings_TextAlignment(orderData[index].h, orderData[index].v);
            CP_Font_DrawText(orderData[index].str, orderData[index].x1, orderData[index].y1);
            break;
        }
        case DRAW_POINT:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Graphics_DrawPoint(orderData[index].x1, orderData[index].y1);
            break;
        }
        case DRAW_LINE:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Settings_StrokeWeight(orderData[index].stroke_weight);
            CP_Graphics_DrawLine(orderData[index].x1, orderData[index].y1, orderData[index].x2, orderData[index].y2);
            break;
        }
        case DRAW_RECT:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Settings_StrokeWeight(orderData[index].stroke_weight);
            CP_Graphics_DrawRect(orderData[index].x1, orderData[index].y1, orderData[index].size_x, orderData[index].size_y);
            break;
        }
        case DRAW_CIRCLE:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Settings_StrokeWeight(orderData[index].stroke_weight);
            CP_Graphics_DrawCircle(orderData[index].x1, orderData[index].y1, orderData[index].size_x * 2.0f);
            break;
        }
        case DRAW_ELLIPSE:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Settings_StrokeWeight(orderData[index].stroke_weight);
            CP_Graphics_DrawEllipse(orderData[index].x1, orderData[index].y1, orderData[index].size_x, orderData[index].size_y);
            break;
        }
        case DRAW_TRIANGLE:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Settings_StrokeWeight(orderData[index].stroke_weight);
            CP_Graphics_DrawTriangle(orderData[index].x1, orderData[index].y1, orderData[index].x2, orderData[index].y2, orderData[index].x3, orderData[index].y3);
            break;
        }
        case DRAW_QUAD:
        {
            CP_Settings_Fill(orderData[index].color);
            CP_Settings_StrokeWeight(orderData[index].stroke_weight);
            CP_Graphics_DrawQuad(orderData[index].x1, orderData[index].y1, orderData[index].x2, orderData[index].y2, orderData[index].x3, orderData[index].y3, orderData[index].size_x, orderData[index].size_y);
            break;
        }
    }
}

void RenderAll(void)
{
    CP_Graphics_ClearBackground(background);
    TowersRender();
    DrawButtons();
    DrawGrid();
    // At this point of the code, everything that needs to be rendered is added into render manager

#if LEVEL_EDITOR_MODE
    TypingBox();
#endif
    
    MergeSortRenderOrder(0, rmCurrIndex - 1);

    // then render everything
    for (unsigned i = 0; i < rmCurrIndex; ++i)
        RenderObjectType(orderData[i].renderType, i);

    // reset the color to white
    CP_Settings_Fill(COLOR_WHITE);
    ResetRenderManagerVariables(rmCurrIndex);
}

void FreeRenderManager(void)
{
    if (orderData)
    {
        free(orderData);
        orderData = NULL;
    }
}