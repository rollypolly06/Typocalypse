/*!
file:	text_render.h
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	Includes all function declaration related rendering of 
		texts defined in text_render.c

	Copyright © 2020 DigiPen, All rights reserved.
		
*//*____________________________________________________________*/
#ifndef TEXT_RENDER_H
#define TEXT_RENDER_H
#include "common_headers.h"

#define MAX_LENGTH	30;

void EnemyText(char line[], int row);

void CorrectText(char line[], int row);

void TextDraw(void);

void SetFonts(void);
void SetCorrectRenderText(char* text);
void SetEnemyRenderText(char* text);

#endif