/*!
file:	word_generator.h
author:	Wong Man Cong
		Lee Fu Sheng Roy
		Phua Tze Cheng Jennifer
		Thea Sea
		Nicole Wong

email:	w.mancong@digipen.edu
		f.lee@digipen.edu
		p.tzechengjennifer@digipen.edu
		thea.sea@digipen.edu
		n.wong@digipen.edu

brief: header file for word generator

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#ifndef	WORD_GENERATOR_H
#define WORD_GENERATOR_H

#include "io_files.h"

typedef enum WordTheme
{
	ANIMALS, FOOD, CITIES, SPORTS, COLOURS
} WordTheme;

int RandomWord(void);
void InitTheme(WordTheme theme, unsigned totalWords);
char* GetRandomWord(void);
char* GetNextWord(void);
unsigned GetWordGenCurrentIndex(void);

#endif
