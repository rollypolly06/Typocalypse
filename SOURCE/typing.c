/*!
file:	typing.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	definition for typing mechanics

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "typing.h"
#include "common_headers.h"

CP_KEY acceptedKeys[] =
{
	KEY_SPACE,
	KEY_APOSTROPHE,			// '''
	KEY_COMMA,				// ','
	KEY_MINUS,				// '-'
	KEY_PERIOD,				// '.'
	KEY_SLASH,				// '/'
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_SEMICOLON,			// ';'
	KEY_EQUAL,				// '='
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_LEFT_BRACKET,		// '['
	KEY_BACKSLASH,			// '\'
	KEY_RIGHT_BRACKET,		// ']'
	KEY_GRAVE_ACCENT,		// '`'
	KEY_KP_0,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_KP_DECIMAL,
	KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY,
	KEY_KP_SUBTRACT,
	KEY_KP_ADD,
};

Boolean keysTriggered[ARRAY_SIZE(acceptedKeys)];						// arrays of keys triggered
Boolean shiftDown;														// is player holding down shift?
Boolean capsStatus;														// is caps toggle on?
Boolean ctrlDown;						// is control button down?
Boolean backSpaceDown;					// is player pressing backspace?
Boolean haveErasedWords;				// was any character other than space part of the block to be erased?
float backSpaceDelayDeltaTime;			// delta time to calculate the delay before erasing data
const float delayTime = 0.4f;			// delay time

Boolean GetTypingMode(void);
/*!
@brief	Printing c for debugging purposes
@param	c: char to be printed
*//*___________________________________________________________*/
void PrintCharacters(char* c)
{
#if DEBUG_TYPING
	if (!strcmp("\0", c)) // if c contains '\0'
		return;
	printf("%c\n", *c);
#endif
}

/*!
@brief	Function to store character
@param	c: char to be stored
		capInput: storage container
		len: length of current storage container
*//*___________________________________________________________*/
void StoreCharacter(char c, char* capInput, int len)
{
	if (c == '\0')	// if c contains '\0'
		return;

	capInput[len] = c;

#if DEBUG_TYPING_STORE
	printf("%s\n", capInput);
#endif
}

/*!
@brief	To capture and store special characters that require
		user to hold shift such as '!' '@' '#' '$' '%'
@param	index: to check which keys are pressed
*//*___________________________________________________________*/
void SpecialCharactersShift(int index, char* capInput, int len)
{
	// keys not pressed
	if (!keysTriggered[index] || !shiftDown)
		return;
	
	char c = '\0';

	switch (acceptedKeys[index])
	{
		case KEY_APOSTROPHE:			// '"'
		{
			c = '\"';
			break;
		}
		case KEY_COMMA:					// '<'
		{
			c = '<';
			break;
		}
		case KEY_MINUS:					// '_'
		{
			c = '_';
			break;
		}
		case KEY_PERIOD:				// '>'
		{
			c = '>';
			break;
		}
		case KEY_SLASH:					// '?'
		{
			c = '?';
			break;						
		}								
		case KEY_0:						// ')'
		{								
			c = ')';
			break;						
		}								
		case KEY_1:						// '!'
		{								
			c = '!';
			break;						
		}								
		case KEY_2:						// '@'
		{								
			c = '@';
			break;						
		}								
		case KEY_3:						// '#'
		{								
			c = '#';
			break;						
		}								
		case KEY_4:						// '$'
		{								
			c = '$';
			break;						
		}								
		case KEY_5:						// '%'
		{
			c = '%';
			break;
		}
		case KEY_6:						// '^'
		{
			c = '^';
			break;
		}
		case KEY_7:						// '&'
		{
			c = '&';
			break;
		}
		case KEY_8:						// '*'
		{
			c = '*';
			break;
		}
		case KEY_9:						// '('
		{
			c = '(';
			break;
		}
		case KEY_SEMICOLON:				// ':'
		{
			c = ':';
			break;
		}
		case KEY_EQUAL:					// '+'
		{
			c = '+';
			break;
		}
		case KEY_LEFT_BRACKET:			// '{'
		{
			c = '{';
			break;
		}
		case KEY_BACKSLASH:				// '|'
		{
			c = '|';
			break;
		}
		case KEY_RIGHT_BRACKET:			// '}'
		{
			c = '}';
			break;
		}
		case KEY_GRAVE_ACCENT:			// '~'
		{
			c = '~';
			break;
		}
	}

	StoreCharacter(c, capInput, len);
	PrintCharacters(&c);
}

/*!
@brief	To capture and store special characters such as 
		'1' '2' '3' '4' '5' ',' '.' '/'
@param	index: to check which keys are pressed
*//*___________________________________________________________*/
void SpecialCharacters(int index, char* capInput, int len)
{
	// keys not pressed
	if (!keysTriggered[index] || shiftDown)
		return;

	char c = '\0';

	switch (acceptedKeys[index])
	{
		case KEY_APOSTROPHE:			// '''
		{
			c = '\'';
			break;
		}
		case KEY_COMMA:					// ','
		{
			c = ',';
			break;
		}
		case KEY_MINUS:					// '-'
		{
			c = '-';
			break;
		}
		case KEY_PERIOD:				// '.'
		{
			c = '.';
			break;
		}
		case KEY_SLASH:					// '/'
		{
			c = '/';
			break;
		}
		case KEY_0:
		{
			c = '0';
			break;
		}
		case KEY_1:
		{
			c = '1';
			break;
		}
		case KEY_2:
		{
			c = '2';
			break;
		}
		case KEY_3:
		{
			c = '3';
			break;
		}
		case KEY_4:
		{
			c = '4';
			break;
		}
		case KEY_5:
		{
			c = '5';
			break;
		}
		case KEY_6:
		{
			c = '6';
			break;
		}
		case KEY_7:
		{
			c = '7';
			break;
		}
		case KEY_8:
		{
			c = '8';
			break;
		}
		case KEY_9:
		{
			c = '9';
			break;
		}
		case KEY_SEMICOLON:				// ';'
		{
			c = ';';
			break;
		}
		case KEY_EQUAL:					// '='
		{
			c = '=';
			break;
		}
		case KEY_LEFT_BRACKET:			// '['
		{
			c = '[';
			break;
		}
		case KEY_BACKSLASH:				// '\'
		{
			c = '\\';
			break;
		}
		case KEY_RIGHT_BRACKET:			// ']'
		{
			c = ']';
			break;
		}
		case KEY_GRAVE_ACCENT:			// '`'
		{
			c = '`';
			break;
		}
		case KEY_KP_0:
		{
			c = '0';
			break;
		}
		case KEY_KP_1:
		{
			c = '1';
			break;
		}
		case KEY_KP_2:
		{
			c = '2';
			break;
		}
		case KEY_KP_3:
		{
			c = '3';
			break;
		}
		case KEY_KP_4:
		{
			c = '4';
			break;
		}
		case KEY_KP_5:
		{
			c = '5';
			break;
		}
		case KEY_KP_6:
		{
			c = '6';
			break;
		}
		case KEY_KP_7:
		{
			c = '7';
			break;
		}
		case KEY_KP_8:
		{
			c = '8';
			break;
		}
		case KEY_KP_9:
		{
			c = '9';
			break;
		}
		case KEY_KP_DECIMAL:			// '.'
		{
			c = '.';
			break;
		}
		case KEY_KP_DIVIDE:				// '/'
		{
			c = '/';
			break;
		}
		case KEY_KP_MULTIPLY:			// '*'
		{
			c = '*';
			break;
		}
		case KEY_KP_SUBTRACT:			// '-'
		{
			c = '-';
			break;
		}
		case KEY_KP_ADD:				// '+'
		{
			c = '+';
			break;
		}
	}

	StoreCharacter(c, capInput, len);
	PrintCharacters(&c);
}

/*!
@brief	To capture and store upper case letters
@param	index: to check which keys are pressed
*//*___________________________________________________________*/
void UpperCase(int index, char* capInput, int len)
{
	// keys not pressed
	if (!keysTriggered[index] || !shiftDown && !capsStatus)
		return;

	char c = '\0';

	switch (acceptedKeys[index])
	{
		case KEY_SPACE:
		{
			c = ' ';
			break;
		}
		case KEY_A:
		{
			c = 'A';
			break;
		}
		case KEY_B:
		{
			c = 'B';
			break;
		}
		case KEY_C:
		{
			c = 'C';
			break;
		}
		case KEY_D:
		{
			c = 'D';
			break;
		}
		case KEY_E:
		{
			c = 'E';
			break;
		}
		case KEY_F:
		{
			c = 'F';
			break;
		}
		case KEY_G:
		{
			c = 'G';
			break;
		}
		case KEY_H:
		{
			c = 'H';
			break;
		}
		case KEY_I:
		{
			c = 'I';
			break;
		}
		case KEY_J:
		{
			c = 'J';
			break;
		}
		case KEY_K:
		{
			c = 'K';
			break;
		}
		case KEY_L:
		{
			c = 'L';
			break;
		}
		case KEY_M:
		{
			c = 'M';
			break;
		}
		case KEY_N:
		{
			c = 'N';
			break;
		}
		case KEY_O:
		{
			c = 'O';
			break;
		}
		case KEY_P:
		{
			c = 'P';
			break;
		}
		case KEY_Q:
		{
			c = 'Q';
			break;
		}
		case KEY_R:
		{
			c = 'R';
			break;
		}
		case KEY_S:
		{
			c = 'S';
			break;
		}
		case KEY_T:
		{
			c = 'T';
			break;
		}
		case KEY_U:
		{
			c = 'U';
			break;
		}
		case KEY_V:
		{
			c = 'V';
			break;
		}
		case KEY_W:
		{
			c = 'W';
			break;
		}
		case KEY_X:
		{
			c = 'X';
			break;
		}
		case KEY_Y:
		{
			c = 'Y';
			break;
		}
		case KEY_Z:
		{
			c = 'Z';
			break;
		}
	}

	StoreCharacter(c, capInput, len);
	PrintCharacters(&c);
}

/*!
@brief	To capture and store lower case letters
@param	index: to check which keys are pressed
*//*___________________________________________________________*/
void LowerCase(int index, char* capInput, int len)
{
	// keys not pressed
	if (!keysTriggered[index] || shiftDown || capsStatus)
		return;

	char c = '\0';

	switch (acceptedKeys[index])
	{
		case KEY_SPACE:
		{
			c = ' ';
			break;
		}
		case KEY_A:
		{
			c = 'a';
			break;
		}
		case KEY_B:
		{
			c = 'b';
			break;
		}
		case KEY_C:
		{
			c = 'c';
			break;
		}
		case KEY_D:
		{
			c = 'd';
			break;
		}
		case KEY_E:
		{
			c = 'e';
			break;
		}
		case KEY_F:
		{
			c = 'f';
			break;
		}
		case KEY_G:
		{
			c = 'g';
			break;
		}
		case KEY_H:
		{
			c = 'h';
			break;
		}
		case KEY_I:
		{
			c = 'i';
			break;
		}
		case KEY_J:
		{
			c = 'j';
			break;
		}
		case KEY_K:
		{
			c = 'k';
			break;
		}
		case KEY_L:
		{
			c = 'l';
			break;
		}
		case KEY_M:
		{
			c = 'm';
			break;
		}
		case KEY_N:
		{
			c = 'n';
			break;
		}
		case KEY_O:
		{
			c = 'o';
			break;
		}
		case KEY_P:
		{
			c = 'p';
			break;
		}
		case KEY_Q:
		{
			c = 'q';
			break;
		}
		case KEY_R:
		{
			c = 'r';
			break;
		}
		case KEY_S:
		{
			c = 's';
			break;
		}
		case KEY_T:
		{
			c = 't';
			break;
		}
		case KEY_U:
		{
			c = 'u';
			break;
		}
		case KEY_V:
		{
			c = 'v';
			break;
		}
		case KEY_W:
		{
			c = 'w';
			break;
		}
		case KEY_X:
		{
			c = 'x';
			break;
		}
		case KEY_Y:
		{
			c = 'y';
			break;
		}
		case KEY_Z:
		{
			c = 'z';
			break;
		}
	}

	StoreCharacter(c, capInput, len);
	PrintCharacters(&c);
}

/*!
@brief	Capture all acceptable keys to handle the
		typing inputs
*//*___________________________________________________________*/
void CaptureInput(void)
{
	for (int i = 0; i < ARRAY_SIZE(acceptedKeys); ++i)
	{
		if (CP_Input_KeyTriggered(acceptedKeys[i]))
			keysTriggered[i] = True;
		else
			keysTriggered[i] = False;
	}

	if (CP_Input_KeyDown(KEY_LEFT_SHIFT) || CP_Input_KeyDown(KEY_RIGHT_SHIFT))
		shiftDown = True;
	else
		shiftDown = False;

	if (CP_Input_KeyDown(KEY_LEFT_CONTROL) || CP_Input_KeyDown(KEY_RIGHT_CONTROL))
		ctrlDown = True;
	else
		ctrlDown = False;

	// updates state of caps lock
	capsStatus = GetKeyState(VK_CAPITAL);
}

/*!
@brief	Calls each function where each keys have different
		booleans condition to print different keys depending
		on user's input
*//*___________________________________________________________*/
void UpdateInput(char* capInput, int len)
{
	for (int i = 0; i < ARRAY_SIZE(keysTriggered); ++i)
	{
		SpecialCharacters(i, capInput, len);
		SpecialCharactersShift(i, capInput, len);
		UpperCase(i, capInput, len);
		LowerCase(i, capInput, len);
	}
}

void InitTyping(void)
{
	backSpaceDown = False;
	backSpaceDelayDeltaTime = 0.0f;
	haveErasedWords = False;
}

/*!
@brief	Main update function to use to capture and update
		user's keyboard input
*//*___________________________________________________________*/
void UpdateTyping(char* capInput, int len)
{
	CaptureInput();
	UpdateInput(capInput, len);
}

/*!
@brief	Erasing block of characters from the string storage
*//*__________________________________________________________________________*/
void EraseBlockCharacters(char* strInput, int* strLength)
{
	if (!ctrlDown)
		return;

	if (CP_Input_KeyTriggered(KEY_BACKSPACE))
	{
		for (--(*strLength); *strLength >= 0; --(*strLength))
		{
			if (strInput[*strLength] == ' ' && haveErasedWords)
			{
				strInput[*strLength] = ' ';
				break;
			}

			if (strInput[*strLength] != ' ')
				haveErasedWords = True;
			strInput[*strLength] = '\0';
		}

		if (0 > *strLength)
			*strLength = 0;

#if DEBUG_TYPING_STORE
		printf("%s\n", strInput);
#endif
	}

	haveErasedWords = False;
}

/*!
@brief	Erasing single character string from the storage
*//*__________________________________________________________________________*/
void EraseSingleCharacter(char* strInput, int* strLength)
{
	if (ctrlDown)
		return;

	// Erase character one by one
	if (CP_Input_KeyDown(KEY_BACKSPACE) && !backSpaceDown)
	{
		if (0 > --(*strLength))
			return;

		strInput[*strLength] = '\0';
		backSpaceDown = True;
#if DEBUG_TYPING_STORE
		printf("%s\n", strInput);
#endif
	}
	// Erase character one by one while holding backspace
	else if (CP_Input_KeyDown(KEY_BACKSPACE) && backSpaceDown)
	{
		backSpaceDelayDeltaTime += CP_System_GetDt();

		// let it have a bit of delay before deleting
		if (delayTime <= backSpaceDelayDeltaTime)
		{
			if (0 > --(*strLength))
				return;

			strInput[*strLength] = '\0';
			backSpaceDelayDeltaTime = backSpaceDelayDeltaTime - 0.025f;
#if DEBUG_TYPING_STORE
			printf("%s\n", strInput);
#endif
		}
	}
	// reset values back to default when released backspace btn
	else if (CP_Input_KeyReleased(KEY_BACKSPACE) && backSpaceDown)
	{
		backSpaceDown = False;
		backSpaceDelayDeltaTime = 0.0f;
	}
}

/*!
@brief	Main function call to handle erasing of captured string
*//*__________________________________________________________________________*/
void EraseCapturedString(char* strInput, int* strLength)
{
	if (GetTypingMode())
		return;
	EraseSingleCharacter(strInput, strLength);
	EraseBlockCharacters(strInput, strLength);
}

/*!
@brief	Always make the back of the string be null terminator
*//*__________________________________________________________________________*/
void CleanInputString(char* strInput, int strLength, int maxLength)
{
		for (int i = strLength; i < maxLength; ++i)
			strInput[i] = '\0';
}