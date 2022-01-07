/*!
file:	level_editor.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	function declarations for level editor

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "level_editor.h"
#include "typing.h"

#define MAX_FILE_NAME_SIZE		55

Boolean buildMode = False, drawGrid = False, saveMode = False, saveFile = False, writeFile = False;
int imageIndex = EMPTY_PATH;
signed char grid_size_x = 1, grid_size_y = 1;

Grid levelEditorGrid[GRID_SYSTEM_ROWS][GRID_SYSTEM_COLS];

int* levelEditorWaypoints;
int currLevelEditorWaypointIndex, levelEditorWaypointSize;

char fileName[MAX_FILE_NAME_SIZE];
int fileNameLength;

void InitLevelEditor(void)
{
	InitTyping();
	InitGrid("");

	for (int i = 0; i < GRID_SYSTEM_ROWS; ++i)
	{
		for (int j = 0; j < GRID_SYSTEM_COLS; ++j)
		{
			levelEditorGrid[i][j].type = EMPTY_PATH;
			levelEditorGrid[i][j].size_x = 1;
			levelEditorGrid[i][j].size_y = 1;
		}
	}

	currLevelEditorWaypointIndex = 0;
	levelEditorWaypointSize = 10;
	levelEditorWaypoints = (int*)malloc(sizeof(int) * levelEditorWaypointSize);
	for (int i = 0; i < levelEditorWaypointSize; ++i)
	{
		if(levelEditorWaypoints + i)
			*(levelEditorWaypoints + i) = -1;
	}
				
	buildMode = False;
	drawGrid = False;
	saveMode = False;
	saveFile = False;
	writeFile = False;
}

void DrawLevelEditor(void)
{
	if (!saveMode && CP_Input_KeyTriggered(KEY_3))
		drawGrid = !drawGrid;

	if (drawGrid)
	{
		// Drawing verticle lines
		for (unsigned i = 0; i < GRID_SYSTEM_COLS; ++i)
		{
			// Verticle
			AddLine(0.0f, (float)(GRID_SYSTEM_HEIGHT * (i + 1)), (float)CP_System_GetWindowWidth(), (float)(GRID_SYSTEM_HEIGHT * (i + 1)), 1.0f, COLOR_BLACK, UI_LAYER);
		}
		// Drawing horizontal lines
		for (unsigned i = 0; i < GRID_SYSTEM_ROWS; ++i)
		{
			// Horizontal
			AddLine((float)(GRID_SYSTEM_WIDTH * (i + 1)), 0.0f, (float)(GRID_SYSTEM_WIDTH * (i + 1)), (float)CP_System_GetWindowHeight(), 1.0f, COLOR_BLACK, UI_LAYER);
		}
	}

	for (unsigned i = 0; i < GRID_SYSTEM_ROWS; ++i)
	{
		for (unsigned j = 0; j < GRID_SYSTEM_COLS; ++j)
		{
			if (levelEditorGrid[i][j].type == GRID_OCCUPIED)
				continue;
			else if (levelEditorGrid[i][j].type != GRID_NOT_OCCUPIED)
				CP_Image_Draw(GetPathImage(levelEditorGrid[i][j].type), (i * GRID_SYSTEM_WIDTH) + (GRID_SYSTEM_WIDTH * levelEditorGrid[i][j].size_x * 0.5f), (j * GRID_SYSTEM_HEIGHT) + (GRID_SYSTEM_HEIGHT * levelEditorGrid[i][j].size_y * 0.5f), GRID_SYSTEM_WIDTH * levelEditorGrid[i][j].size_x + 0.1f, GRID_SYSTEM_HEIGHT * levelEditorGrid[i][j].size_y + 0.1f, 255);
		}
	}

	for (int i = 0; i < levelEditorWaypointSize; ++i)
	{
		if (*(levelEditorWaypoints + i) < 0)
			break;
		AddRect(*(levelEditorWaypoints + i++) * GRID_SYSTEM_WIDTH, *(levelEditorWaypoints + i) * GRID_SYSTEM_HEIGHT, GRID_SYSTEM_WIDTH, GRID_SYSTEM_HEIGHT, 0.1f, TRANSLUCENT_WHITE, TOP_LAYER);
	}
}

void BuildOntoLevelEditorGrid(Point pos, Grid grid, GridType gridType)
{
#if LEVEL_EDITOR_MODE
	if (WAY_POINTS == gridType)
		return;
#endif	
	int x = (int)(pos.x / GRID_SYSTEM_WIDTH);
	int y = (int)(pos.y / GRID_SYSTEM_HEIGHT);

	for (int row = 0; row < (int)grid.size_x; ++row)
	{
		for (int col = 0; col < (int)grid.size_y; ++col)
		{
			levelEditorGrid[x + row][y + col].type = GRID_OCCUPIED;
		}
	}

	levelEditorGrid[x][y].type = gridType;
	levelEditorGrid[x][y].size_x = grid.size_x;
	levelEditorGrid[x][y].size_y = grid.size_y;
}

void BuildWayPoints(Point pos)
{
	int x = (int)(pos.x / GRID_SYSTEM_WIDTH);
	int y = (int)(pos.y / GRID_SYSTEM_HEIGHT);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
	{
		if (currLevelEditorWaypointIndex + 2 >= levelEditorWaypointSize)
		{
			levelEditorWaypointSize *= 2;
			int* tmp = levelEditorWaypoints;
			levelEditorWaypoints = (int*)malloc(sizeof(int) * levelEditorWaypointSize);
			memcpy_s(levelEditorWaypoints, sizeof(int) * levelEditorWaypointSize, tmp, sizeof(int) * levelEditorWaypointSize >> 1);
			free(tmp);
		}

		*(levelEditorWaypoints + currLevelEditorWaypointIndex++) = x;
		*(levelEditorWaypoints + currLevelEditorWaypointIndex++) = y;
		printf("size: %d\n", levelEditorWaypointSize);
	}
}

/*!
@brief	during building of maps, can use these codes to make the map
*//*_____________________________________________________________________________*/
void DesignLevel(void)
{
	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		if (!saveMode)
		{
			buildMode = !buildMode;
			saveMode = False;
		}
	}
	else if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		buildMode = False;
		saveMode = False;
	}

	if (!buildMode)
		return;

	char printed_text[20] = "";
	Grid grid = { 0, 0, GRID_NOT_OCCUPIED };

	if (CP_Input_KeyTriggered(KEY_E))
	{
		if (TOTAL_TILES <= ++imageIndex)
			imageIndex = EMPTY_PATH;
	}
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		if (GRID_NOT_OCCUPIED >= --imageIndex)
			imageIndex = TOTAL_TILES - 1;
	}

	switch (imageIndex)
	{
		case EMPTY_PATH:
		{
			strcpy_s(printed_text, 20, "empty path");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = EMPTY_PATH;
			break;
		}
		case HORIZONTAL_PATH:
		{
			strcpy_s(printed_text, 20, "horizontal path");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = HORIZONTAL_PATH;
			break;
		}
		case VERTICLE_PATH:
		{
			strcpy_s(printed_text, 20, "verticle path");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = VERTICLE_PATH;
			break;
		}
		case L_JUNCTION_1:
		{
			strcpy_s(printed_text, 20, "l juntion 1");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = L_JUNCTION_1;
			break;
		}
		case L_JUNCTION_2:
		{
			strcpy_s(printed_text, 20, "l juntion 2");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = L_JUNCTION_2;
			break;
		}
		case L_JUNCTION_3:
		{
			strcpy_s(printed_text, 20, "l juntion 3");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = L_JUNCTION_3;
			break;
		}
		case L_JUNCTION_4:
		{
			strcpy_s(printed_text, 20, "l juntion 4");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = L_JUNCTION_4;
			break;
		}
		case T_JUNCTION_1:
		{
			strcpy_s(printed_text, 20, "t junction 1");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = T_JUNCTION_1;
			break;
		}
		case T_JUNCTION_2:
		{
			strcpy_s(printed_text, 20, "t junction 2");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = T_JUNCTION_2;
			break;
		}
		case T_JUNCTION_3:
		{
			strcpy_s(printed_text, 20, "t junction 3");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = T_JUNCTION_3;
			break;
		}
		case T_JUNCTION_4:
		{
			strcpy_s(printed_text, 20, "t junction 4");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = T_JUNCTION_4;
			break;
		}
		case X_JUNCTION:
		{
			strcpy_s(printed_text, 20, "x junction");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = X_JUNCTION;
			break;
		}
		case EDGE_1:
		{
			strcpy_s(printed_text, 20, "edge 1");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = EDGE_1;
			break;
		}
		case EDGE_2:
		{
			strcpy_s(printed_text, 20, "edge 2");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = EDGE_2;
			break;
		}
		case EDGE_3:
		{
			strcpy_s(printed_text, 20, "edge 3");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = EDGE_3;
			break;
		}
		case EDGE_4:
		{
			strcpy_s(printed_text, 20, "edge 4");
			grid.size_x = grid_size_x;
			grid.size_y = grid_size_y;
			grid.type = EDGE_4;
			break;
		}
		case TREE_1:
		{
			strcpy_s(printed_text, 20, "tree 1");
			grid.size_x = 2;
			grid.size_y = 2;
			grid.type = TREE_1;
			break;
		}
		case TREE_2:
		{
			strcpy_s(printed_text, 20, "tree 2");
			grid.size_x = 2;
			grid.size_y = 2;
			grid.type = TREE_2;
			break;
		}
		case TREE_3:
		{
			strcpy_s(printed_text, 20, "tree 3");
			grid.size_x = 2;
			grid.size_y = 2;
			grid.type = TREE_3;
			break;
		}
		case TREE_4:
		{
			strcpy_s(printed_text, 20, "tree 4");
			grid.size_x = 2;
			grid.size_y = 2;
			grid.type = TREE_4;
			break;
		}
		case TREE_5:
		{
			strcpy_s(printed_text, 20, "tree 5");
			grid.size_x = 2;
			grid.size_y = 2;
			grid.type = TREE_5;
			break;
		}
		case CASTLE:
		{
			strcpy_s(printed_text, 20, "castle");
			grid.size_x = 5;
			grid.size_y = 5;
			grid.type = CASTLE;
			break;
		}
#if LEVEL_EDITOR_MODE
		case WAY_POINTS:
		{
			strcpy_s(printed_text, 20, "way points");
			Point p = { CP_Input_GetMouseX(), CP_Input_GetMouseY() };
			BuildWayPoints(p);
			grid.type = WAY_POINTS;
			break;
		}
#endif
		//default:
		//{
		//	strcpy_s(printed_text, 20, "delete path");
		//	grid.size_x = grid_size_x;
		//	grid.size_y = grid_size_y;
		//	grid.type = GRID_NOT_OCCUPIED;
		//	break;
		//}
	}

	Point p = { CP_Input_GetMouseX(), CP_Input_GetMouseY() };
	int x = (int)(p.x / GRID_SYSTEM_WIDTH);
	int y = (int)(p.y / GRID_SYSTEM_HEIGHT);

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		printf("mouse x: %d, mouse y: %d\n", x, y);

		BuildOntoLevelEditorGrid(p, grid, grid.type);
	}

	Point q = { (float)((int)(p.x / GRID_SYSTEM_WIDTH)), (float)((int)(p.y / GRID_SYSTEM_HEIGHT)) };
	p = GetPositionOnGrid(q, grid.size_x, grid.size_y);
	CP_Image_Draw(GetPathImage(imageIndex), p.x, p.y, GRID_SYSTEM_WIDTH * grid.size_x, GRID_SYSTEM_HEIGHT * grid.size_y, 255);
#if LEVEL_EDITOR_MODE
	if (WAY_POINTS == grid.type)
		AddRect(p.x, p.y, GRID_SYSTEM_WIDTH, GRID_SYSTEM_HEIGHT, 0.1f, TRANSLUCENT_WHITE, TOP_LAYER);
	printf("x: %f, y: %f\n\n", p.x, p.y);
#endif	

	CP_Settings_Fill(COLOR_RED);
#if FULL_SCREEN
	CP_Settings_TextSize((float)CP_System_GetWindowWidth() * 0.025f);
#else
	CP_Settings_TextSize(15.0f);
#endif
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	CP_Font_DrawText(printed_text, 10.0f, 10.0f);
}

void SaveFile(void)
{
	if (!saveFile)
		return;

	CP_Settings_Fill(COLOR_WHITE);

	float size_x = (float)CP_System_GetWindowWidth() * 0.75f;
	float size_y = (float)CP_System_GetWindowHeight() * 0.5f;
	float pos_x = (float)CP_System_GetWindowWidth() * 0.5f - size_x * 0.5f;
	float pos_y = (float)CP_System_GetWindowHeight() * 0.5f - size_y * 0.5f;
	CP_Graphics_DrawRect(pos_x, pos_y, size_x, size_y);

	CP_Settings_TextSize((float)CP_System_GetWindowWidth() * 0.05f);
	CP_Settings_Fill(COLOR_BLACK);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	pos_x = (float)CP_System_GetWindowWidth() * 0.5f;
	pos_y = (float)CP_System_GetWindowHeight() * 0.5f - size_y * 0.45f;
	CP_Font_DrawText("CONFIRM?", pos_x, pos_y);

	CP_Settings_TextSize((float)CP_System_GetWindowWidth() * 0.05f);
	CP_Settings_Fill(COLOR_GREEN);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	pos_x = (float)CP_System_GetWindowWidth() * 0.5f - size_x * 0.4f;
	pos_y = (float)CP_System_GetWindowHeight() * 0.5f + size_y * 0.2f;
	CP_Font_DrawText("(Y)ES", pos_x, pos_y);

	CP_Settings_Fill(COLOR_RED);
	pos_x = (float)CP_System_GetWindowWidth() * 0.5f + size_x * 0.15f;
	pos_y = (float)CP_System_GetWindowHeight() * 0.5f + size_y * 0.2f;
	CP_Font_DrawText("(N)O", pos_x, pos_y);

	if (CP_Input_KeyTriggered(KEY_Y))
	{
		writeFile = True;
		saveMode = False;
		buildMode = False;
		saveFile = False;
	}
	else if (CP_Input_KeyTriggered(KEY_N))
	{
		saveMode = False;
		buildMode = False;
		saveFile = False;
		strcpy_s(fileName, sizeof(fileName), "");
	}
}

void SaveLevel(void)
{
	if (CP_Input_KeyDown(KEY_LEFT_CONTROL) && CP_Input_KeyReleased(KEY_S))
	{
		if (!saveMode)
		{
			saveMode = True;
			buildMode = False;
			saveFile = False;
			strcpy_s(fileName, sizeof(fileName), "");
		}
	}
	else if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		saveMode = False;
		buildMode = False;
		saveFile = False;
		strcpy_s(fileName, sizeof(fileName), "");
	}

	if (!saveMode)
		return;

	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		int textSize = (int)strlen(fileName);
		if(0 < textSize)
			saveFile = True;
	}

	if (!saveFile)
	{
		fileNameLength = (int)strlen(fileName);
		EraseCapturedString(fileName, &fileNameLength);
		if (MAX_FILE_NAME_SIZE - 1 > fileNameLength)
		{
			CleanInputString(fileName, fileNameLength, MAX_FILE_NAME_SIZE);
			UpdateTyping(&*fileName, fileNameLength);
		}
	}

	CP_Settings_TextSize((float)CP_System_GetWindowWidth() * 0.05f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_Fill(COLOR_RED);
	if (0 == fileNameLength)
		CP_Font_DrawText("ENTER FILE NAME:", (float)CP_System_GetWindowWidth() * 0.5f, (float)CP_System_GetWindowHeight() * 0.5f);
	else
	{
		char saveName[65];
		strcpy_s(saveName, sizeof(fileName), fileName);
		strncat_s(saveName, sizeof(saveName), ".txt", 4);
		CP_Font_DrawText(saveName, (float)CP_System_GetWindowWidth() * 0.5f, (float)CP_System_GetWindowHeight() * 0.5f);
	}
}

/*!
@brief	save data from level editor into a .txt file
*//*_____________________________________________________________________________*/
void WriteIntoFile(void)
{
	if (!writeFile)
		return;

	char saveFileName[1024];
	memcpy_s(saveFileName, sizeof(saveFileName), "Assets/Levels/", sizeof("Assets/Levels/"));
	strncat_s(saveFileName, sizeof(saveFileName), fileName, MAX_FILE_NAME_SIZE);
	strncat_s(saveFileName, sizeof(saveFileName), ".txt", strlen(".txt"));

	// delete existing file
	remove(saveFileName);

	// then create a new file
	for (int i = 0; i < GRID_SYSTEM_ROWS; ++i)
	{
		for (int j = 0; j < GRID_SYSTEM_COLS; ++j)
		{
			WriteInt(saveFileName, "a", 1, levelEditorGrid[i][j].type);
			levelEditorGrid[i][j].type = EMPTY_PATH;
			levelEditorGrid[i][j].size_x = 1;
			levelEditorGrid[i][j].size_y = 1;
		}
	}

	char wpFileName[1024];
	memcpy_s(wpFileName, sizeof(wpFileName), "Assets/Levels/Waypoints/", sizeof("Assets/Levels/Waypoints/"));
	strncat_s(wpFileName, sizeof(wpFileName), fileName, MAX_FILE_NAME_SIZE);
	strncat_s(wpFileName, sizeof(wpFileName), "_waypoints.txt", strlen("_waypoints.txt"));

	// delete existing waypoint files
	remove(wpFileName);

	// save into .txt file
	for (int i = 0; i < levelEditorWaypointSize; ++i)
	{
		if (*(levelEditorWaypoints + i) < 0)
			break;
		WriteInt(wpFileName, "a", 1, *(levelEditorWaypoints + i));
		*(levelEditorWaypoints + i) = -1;
	}

	writeFile = False;
	strcpy_s(fileName, sizeof(fileName), "");
}

void UpdateLevelEditor(void)
{
	// changing background to be the same as my sprite bg
	DrawLevelEditor();
	DesignLevel();
	SaveLevel();
	SaveFile();
	WriteIntoFile();
}

void ExitLevelEditor(void)
{
	if (levelEditorWaypoints)
	{
		free(levelEditorWaypoints);
	}
	levelEditorWaypoints = NULL;
}