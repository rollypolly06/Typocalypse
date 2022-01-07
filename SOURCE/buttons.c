/*!
file:	buttons.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	Function definitions for button

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "buttons.h"

struct Button
{
	float x, y;				// pos x and y
	float width, height;	// width and height of the button
	int alpha;				// alpha (transparency) of the image
	int id;					// button id
	int img_index;			// choose which image to draw
	Boolean clickable;		// is this button clickable
	RenderOrder order;
	CP_Image img[2];		// image of the button
};

int totalButtons = 0;
// pointer array to store all button pointers, then free the memory at the end
Button** btnPtr;
// id of button
int btnID = 0;
// index of button used for scaling
int btnIndex = 0;
// dynamic array for storing original size of btn when scaling
float* btnOriginalSize;

/*!
@brief	Store button pointers here to be 
@param	btn:	button to be stored in my pointer array
*//*____________________________________________*/
void StoreButtonPointers(Button* btn)
{
	// Pointer array initialised
	if (btnPtr)
	{
		Button** tmp = btnPtr;
		btnPtr = (Button**)malloc(((size_t)totalButtons + 1) * sizeof(Button*));
		memcpy_s(btnPtr, ((size_t)totalButtons + 1) * sizeof(Button*), tmp, totalButtons * sizeof(Button*));
		free(tmp);
		if (!btnPtr)
			return;
		btnPtr[totalButtons] = btn;

		float* tmp2 = btnOriginalSize;
		btnOriginalSize = (float*)malloc(((size_t)totalButtons + 1) * 2 * sizeof(float));
		memcpy_s(btnOriginalSize, ((size_t)totalButtons + 1) * 2 * sizeof(float), tmp2, (((size_t)totalButtons + 1) * 2 - 2) * sizeof(float));
		free(tmp2);
		if (!btnOriginalSize)
		{
			free(btnPtr);
			return;
		}
		btnOriginalSize[btnIndex++] = btn->width;
		btnOriginalSize[btnIndex++] = btn->height;
	}
	// Pointer array not initialised
	else
	{
		btnPtr = (Button**)malloc(sizeof(Button*));
		if (!btnPtr)
			return;
		btnPtr[totalButtons] = btn;

		// first index for width, second index for height
		btnOriginalSize = (float*)malloc(2 * sizeof(float));
		if (!btnOriginalSize)
		{
			free(btnPtr);
			return;
		}
		btnOriginalSize[btnIndex++] = btn->width;
		btnOriginalSize[btnIndex++] = btn->height;
	}	
	++totalButtons;
}

/*!
@brief	Set default values for btn
@param	btn:	button to have it's value defaulted
*//*____________________________________________*/
void DefaultButton(Button* btn, const float x, const float y, const float width, const float height)
{
	btn->x = x;
	btn->y = y;
	btn->width = width;
	btn->height = height;
	btn->alpha = ALPHA;
	btn->id = btnID;
	btn->img_index = 0;
	btn->clickable = True;
	btn->order = UI_LAYER;

	// increase the id by two
	btnID += 2;
}

void DebugButtons(void)
{
	for (int i = 0; i < totalButtons; i += 2)
		printf("width: %f height: %f\n", btnOriginalSize[i], btnOriginalSize[i + 1]);
}

/*!
@brief	Creates a button

@param	filePath:	file path to the image

@return	Reference to the button array
*//*____________________________________________*/
Button* LoadButton(const char* filePath, const float x, const float y, const float width, const float height)
{
	Button* btn = (Button*)malloc(sizeof(Button));
	if (!btn)
		return NULL;
	btn->img[0] = CP_Image_Load(filePath);
	btn->img[1] = NULL;

	if (!btn->img[0])
	{
		printf("Error loading image: %s", filePath);
		free(btn);
		return NULL;
	}

	DefaultButton(btn, x, y, width, height);
	StoreButtonPointers(btn);

	return btn;
}

/*!
@brief	Add an additional image for button
@param	filePath:	file path to the image
		btn:		reference to the button
*//*____________________________________________*/
void AdditionalButtonImage(Button* btn, const char* filePath)
{
	if (!btn)
		return;
	btn->img[1] = CP_Image_Load(filePath);
	if (!btn->img[1])
	{
		printf("Error loading image: %s", filePath);		
	}
}

/*!
@brief	Set the alpha of the button
@param	btn:	button to have it's alpha changed
		a:		alpha value of the button
*//*____________________________________________*/
void SetButtonAlpha(Button* btn, const int a)
{
	if (!btn)
		return;
	btn->alpha = a;
}

/*!
@brief	Set the image index of the button
@param	btn:	button to have it's image changed
		index:	index of the button
*//*____________________________________________*/
void SetButtonImageIndex(Button* btn, const int index)
{
	if (!btn)
		return;
	if (0 > index || 2 <= index)
		return;
	btn->img_index = index;
}

/*!
@brief	Set the position of the button
@param	btn:	button to have it's position changed
		p:		new position
*//*____________________________________________*/
void SetButtonPosition(Button* btn, Point p)
{
	if (!btn)
		return;
	btn->x = p.x;
	btn->y = p.y;
}

/*!
@brief	Set the clickable status of the button
@param	btn:	button to have it's state changed
		state:	clickable state of button
*//*____________________________________________*/
void SetButtonClickableState(Button* btn, Boolean state)
{
	if (!btn)
		return;
	btn->clickable = state;
}

/*!
@brief	Set the render order of the button
@param	btn:	button to have it's render order changed
		order:	order of the button
*//*____________________________________________*/
void SetButtonRenderOrder(Button* btn, RenderOrder order)
{
	if (!btn)
		return;
	btn->order = order;
}

/*!
@brief	Returns true if the mouse is hovering
		over the button
@param	btn:	the button that the mouse will
		check if it's hovering over
*//*____________________________________________*/
Boolean MouseHoveringButton(Button* btn)
{
	if (!btn)
		return False;
	return CP_Input_GetMouseX() >= btn->x - (btn->width * 0.5f) && CP_Input_GetMouseX() <= btn->x + (btn->width * 0.5f) && CP_Input_GetMouseY() >= btn->y - (btn->height * 0.5f) && CP_Input_GetMouseY() <= btn->y + (btn->height * 0.5f);
}

/*!
@brief	Returns true if the user is clicking on
		the button
@param	btn:	the button to be clicked
		mouseBtn: Which mouse button
*//*____________________________________________*/
Boolean IsButtonClick(Button* btn, CP_MOUSE mouseBtn)
{
	if (!btn || !btn->clickable)
		return False;
	return CP_Input_MouseTriggered(mouseBtn) && MouseHoveringButton(btn);
}

/*!
@brief	Returns true if the mouse is still within
		the original size of the button
@param	btn:	the button that the mouse will
		check if it's still within the original
		size of the button
*//*____________________________________________*/
Boolean WithinOriginalSize(Button* btn)
{
	return CP_Input_GetMouseX() >= btn->x - (btnOriginalSize[btn->id] * 0.5f) && CP_Input_GetMouseX() <= btn->x + (btnOriginalSize[btn->id] * 0.5f) && CP_Input_GetMouseY() >= btn->y - (btnOriginalSize[btn->id + 1] * 0.5f) && CP_Input_GetMouseY() <= btn->y + (btnOriginalSize[btn->id + 1] * 0.5f);
}

/*!
@brief	Enlarges when mouse hover over it
@param	btn:	button to be scaled up
		sW:		increase width by sW from the 
				original width
		sH:		increase height by sH from the
				original height
		speed:	determines how fast to enlarge
				the button
*//*____________________________________________*/
void ButtonScaleUp(Button* btn, float sW, float sH, float speed)
{
	if (!btn)
		return;
	// if not hovering, go back to original size
	if (!MouseHoveringButton(btn))
	{
		btn->width -= speed;
		btn->height -= speed;

		if (btn->width <= btnOriginalSize[btn->id])
			btn->width = btnOriginalSize[btn->id];

		if (btn->height <= btnOriginalSize[btn->id + 1])
			btn->height = btnOriginalSize[btn->id + 1];
	}
	// else enlarge the button
	else
	{
		btn->width += speed;
		btn->height += speed;

		if (btn->width > btnOriginalSize[btn->id] + sW)
			btn->width = btnOriginalSize[btn->id] + sW;

		if (btn->height > btnOriginalSize[btn->id + 1] + sH)
			btn->height = btnOriginalSize[btn->id + 1] + sH;
	}
}

/*!
@brief	Shrinks when mouse hover over it
@param	btn:	button to be scaled down
		sW:		decrease width by sW from the
		original width
		sH:		decrease height by sH from the
		original height
		speed:	determines how fast to shrink
		the button
*//*____________________________________________*/
void ButtonScaleDown(Button* btn, float sW, float sH, float speed)
{
	if (!btn)
		return;
	// if not hovering, go back to original size
	if (!MouseHoveringButton(btn))
	{
		if (!WithinOriginalSize(btn))
		{
			btn->width += speed;
			btn->height += speed;
		}

		if (btn->width >= btnOriginalSize[btn->id])
			btn->width = btnOriginalSize[btn->id];

		if (btn->height >= btnOriginalSize[btn->id + 1])
			btn->height = btnOriginalSize[btn->id + 1];
	}
	// else shrink the button
	if(WithinOriginalSize(btn))
	{
		btn->width -= speed;
		btn->height -= speed;

		if (btn->width < btnOriginalSize[btn->id] - sW)
			btn->width = btnOriginalSize[btn->id] - sW;

		if (btn->height < btnOriginalSize[btn->id + 1] - sH)
			btn->height = btnOriginalSize[btn->id + 1] - sH;
	}
}

/*!
@brief	Draws the button onto the screen
@param	btn:	button to be drawn on screen
*//*____________________________________________*/
void DrawButtons(void)
{
	for (int i = 0; i < totalButtons; ++i)
		AddSprite(btnPtr[i]->img[btnPtr[i]->img_index], btnPtr[i]->x, btnPtr[i]->y, btnPtr[i]->width, btnPtr[i]->height, btnPtr[i]->alpha, btnPtr[i]->order);
}

/*!
@brief	Deallocates all the memory of button 
		pointers
*//*____________________________________________*/
void FreeButtonPointers(void)
{
	for (int i = 0; i < totalButtons; ++i)
	{
		CP_Image_Free(&btnPtr[i]->img[0]);
		CP_Image_Free(&btnPtr[i]->img[1]);

		free(btnPtr[i]);
		btnPtr[i] = NULL;
	}

	if (btnPtr)
	{
		free(btnPtr);
		btnPtr = NULL;
	}

	if (btnOriginalSize)
	{
		free(btnOriginalSize);
		btnOriginalSize = NULL;
	}

	totalButtons = 0;
	btnIndex = 0;
	btnID = 0;
}

/*!
@brief	deallocate and or resets button
*//*____________________________________________*/
void ButtonExit(void)
{
	FreeButtonPointers();
}