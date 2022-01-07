/*!
file:   level_5.h
author: Wong Man Cong
        Lee Fu Sheng Roy
        Phua Tze Cheng Jennifer
        Thea Sea
        Nicole Wong

email:  w.mancong@digipen.edu
        f.lee@digipen.edu
        p.tzechengjennifer@digipen.edu
        thea.sea@digipen.edu
        n.wong@digipen.edu

brief:  level scene to make makes

    Copyright © 2020 DigiPen, All rights reserved.
//_____________________________________________________*/
#include "level_maker.h"
#include "level_editor.h"
#include "ui.h"

void level_maker_init(void)
{
	DefaultRenderManager();
	InitLevelEditor();
	InitUI();
}

void level_maker_update(void)
{
	UpdateLevelEditor();
	RenderAll();
}

void level_maker_exit(void)
{
	ExitLevelEditor();
}