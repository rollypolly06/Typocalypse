/*!
file:	buttons.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	Struct that contains data for a button with function
		declarations

		Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#ifndef	BUTTONS_H
#define BUTTONS_H

#include "common_headers.h"

typedef struct Button Button;
typedef enum RenderOrder RenderOrder;

// Init
Button* LoadButton(const char* filePath, const float x, const float y, const float width, const float height);
void AdditionalButtonImage(Button* btn, const char* filePath);

// Setter
void SetButtonAlpha(Button* btn, const int a);
void SetButtonImageIndex(Button* btn, const int index);
void SetButtonPosition(Button* btn, Point p);
void SetButtonClickableState(Button* btn, Boolean state);
void SetButtonRenderOrder(Button* btn, RenderOrder order);

// Update
Boolean IsButtonClick(Button* btn, CP_MOUSE mouseBtn);
Boolean MouseHoveringButton(Button* btn);
void ButtonScaleUp(Button* btn, float sW, float sH, float speed);
void ButtonScaleDown(Button* btn, float sW, float sH, float speed);

Boolean MouseHoveringButton(Button* btn);

// Render
void DrawButtons(void);

// Exit
void ButtonExit(void);

void DebugButtons(void);

#endif