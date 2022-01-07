/*!
file:	win_screen.h
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

brief:	includes all declarations to functions defined in
		win_screen.h

*//*____________________________________________________________*/

#ifndef WINSCREEN_H
#define WINSCREEN_H

typedef enum Level Level;

// To be called in the init function
void InitWinScreen(Level nextLvl);

// Sets the alpha and clickability of the buttons.
// Called in WinScreenUpdate()
//void RenderWinScreenButtons(void);

// Sets Boolean of winState to True
// Called in Update loop if condition to win is fulfilled
//void SetWinTrue(void);

// Renders onto screen the win screen and awaits user to click on buttons
// Called in Update loop. 
void WinScreenUpdate(void);

#endif