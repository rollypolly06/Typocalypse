/*!
file:	typing.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	typing mechanic for the game

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	TYPING_H
#define TYPING_H

#define DEBUG_TYPING		0
#define DEBUG_TYPING_STORE	0

void InitTyping(void);
void UpdateTyping(char* capInput, int len);
void EraseCapturedString(char* strInput, int* strLength);
void CleanInputString(char* strInput, int strLength, int maxLength);

#endif