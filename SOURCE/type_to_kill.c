/*!
file:	typing.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	Storage to set next word and get current word

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "type_to_kill.h"
#include "word_generator.h"

char* currWordToType;

void SetNextWord(void)
{
	currWordToType = GetNextWord();
}

char* GetCurrentWord(void)
{
	return currWordToType;
}