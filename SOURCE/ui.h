/*!
file:	ui.h
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	Includes all declaration of functions defined in ui.c

	Copyright © 2020 DigiPen, All rights reserved.

*//*____________________________________________________________*/

#ifndef UI_H
#define UI_H

#include "tower.h"
#include "buttons.h"
#include "grid_system.h"
#include "common_headers.h"
#include "player.h"
#include "gold.h"

// initializes the buttons and renders them on the screen
// Should be placed in state_init() portion
void InitButtons(void);

// initializes the buttons and renders them on the screen
// called in InitUI()
void HotkeyInit(void);

// Renders the hotkey images onto the screen with AddSprite()
// Called in UIUpdate()
void RenderHotkeys(void);

// Loads the image of typing box
void InitTypingBox(void);


// Renders a textbox to display the words to be typed
// Called in ButtonsUpdate
void TypingBox(void);

// Loads the images of the tower information
void InfoInit(void);

// Call function to initialize all required UI assets
void InitUI(void);

// changes details when buttons are pressed
// TowerButton pressed, toggles editing mode to place down towers
// AbilityButton pressed, toggle ability mode to render the ability radius
// Must be called only after TowerUpdate() is called
void ButtonsUpdate(void);

// Renders TowerWithRadius() when isEditing is True
// creates tower in tPtr array with CreateTower()
// Sets isEditing to False after click
// Also call SlowTower() hence should be called only after InTowerRange() is called
void TowerUpdate(void);

// Renders either the AOE or Freeze ability radius
// calls FreezeArray when clicked
// Unfreezes enemies when freezeTime > FREEZE_TIME
// Must be called only after TowerUpdate()
void AbilityUpdate(void);

// Calls ButtonsUpdate, TowerUpdate and AbilityUpdate
void UIUpdate(void);

Boolean GetIsEditing(void);
void SetIsEditing(Boolean status);

#endif