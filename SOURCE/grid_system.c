/*!
file:	grid_system.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	function definition for handling grid system

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "grid_system.h"

Grid buildGrid[GRID_SYSTEM_ROWS][GRID_SYSTEM_COLS];

CP_Image path[TOTAL_TILES];

void InitCastle(float x, float y, float width, float height);

Boolean gridGameState = False;

const int GRID_CASTLE_WIDTH = 5, GRID_CASTLE_HEIGHT = 5;


/*!
@brief	Based on the Grid Type, returns relevant Grid data

@param	type: type of the grid

@return	Relevant grid data of the specific type
*//*____________________________________________________________*/
Grid InitGridType(GridType type)
{
	Grid grid = { 0, 0, type };
	unsigned path_size = 1;
	unsigned tree_size = 2;
	unsigned castle_size = 5;
	switch (type)
	{
		case EMPTY_PATH:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = EMPTY_PATH;
			break;
		}
		case HORIZONTAL_PATH:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = HORIZONTAL_PATH;
			break;
		}
		case VERTICLE_PATH:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = VERTICLE_PATH;
			break;
		}
		case L_JUNCTION_1:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = L_JUNCTION_1;
			break;
		}
		case L_JUNCTION_2:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = L_JUNCTION_2;
			break;
		}
		case L_JUNCTION_3:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = L_JUNCTION_3;
			break;
		}
		case L_JUNCTION_4:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = L_JUNCTION_4;
			break;
		}
		case T_JUNCTION_1:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = T_JUNCTION_1;
			break;
		}
		case T_JUNCTION_2:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = T_JUNCTION_2;
			break;
		}
		case T_JUNCTION_3:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = T_JUNCTION_3;
			break;
		}
		case T_JUNCTION_4:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = T_JUNCTION_4;
			break;
		}
		case X_JUNCTION:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = X_JUNCTION;
			break;
		}
		case EDGE_1:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = EDGE_1;
			break;
		}
		case EDGE_2:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = EDGE_2;
			break;
		}
		case EDGE_3:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = EDGE_3;
			break;
		}
		case EDGE_4:
		{
			grid.size_x = path_size;
			grid.size_y = path_size;
			grid.type = EDGE_4;
			break;
		}
		case TREE_1:
		{
			grid.size_x = tree_size;
			grid.size_y = tree_size;
			grid.type = TREE_1;
			break;
		}
		case TREE_2:
		{
			grid.size_x = tree_size;
			grid.size_y = tree_size;
			grid.type = TREE_2;
			break;
		}
		case TREE_3:
		{
			grid.size_x = tree_size;
			grid.size_y = tree_size;
			grid.type = TREE_3;
			break;
		}
		case TREE_4:
		{
			grid.size_x = tree_size;
			grid.size_y = tree_size;
			grid.type = TREE_4;
			break;
		}
		case TREE_5:
		{
			grid.size_x = tree_size;
			grid.size_y = tree_size;
			grid.type = TREE_5;
			break;
		}
		case CASTLE:
		{
			grid.size_x = castle_size;
			grid.size_y = castle_size;
			grid.type = CASTLE;
			break;
		}
		// a bit hard coding
		case TOWER:
		{
			grid.size_x = castle_size;
			grid.size_y = castle_size;
			grid.type = GRID_OCCUPIED;
		}
	}
	return grid;
}

/*!
@brief	Initialise the grid and relevant images

@param	fileName: file path to load the current level
*//*_____________________________________________________________________________*/
void InitGrid(const char* fileName)
{
#if BUILD_GRID
	buildMode = False;
	drawGrid = False;
	imageIndex = GRASS_PATH_01;
#endif

	char imageFile[40];
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		memcpy_s(imageFile, sizeof(imageFile), "Assets/Image/tiles/tile_", sizeof("Assets/Image/tiles/tile_"));
		char num[5]; _itoa_s(i + 1, num, 3, 10);
		strncat_s(imageFile, sizeof(imageFile), num, 3);
		strncat_s(imageFile, sizeof(imageFile), ".png", 5);

		path[i] = CP_Image_Load(imageFile);
	}

#if !LEVEL_EDITOR_MODE
	FileData fd = ReadFiles(fileName);
	int index = 0;
	for (unsigned i = 0; i < GRID_SYSTEM_ROWS; ++i)
	{
		for (unsigned j = 0; j < GRID_SYSTEM_COLS; ++j)
		{
			buildGrid[i][j] = InitGridType(atoi(fd->str[index++]));

			if (CASTLE == buildGrid[i][j].type)
			{
				Point p = { (float)i, (float)j };
				p = GetPositionOnGrid(p, GRID_CASTLE_WIDTH, GRID_CASTLE_HEIGHT);
				InitCastle(p.x, p.y, GRID_CASTLE_WIDTH * GRID_SYSTEM_WIDTH, GRID_CASTLE_HEIGHT * GRID_SYSTEM_HEIGHT);
			}
		}
	}
	FreeFileData(&fd);
#endif

	gridGameState = True;
}

/*!
@brief	draw paths
*//*_____________________________________________________________________________*/
void DrawGrid(void)
{
	if (!gridGameState)
		return;

	for (unsigned i = 0; i < GRID_SYSTEM_ROWS; ++i)
	{
		for (unsigned j = 0; j < GRID_SYSTEM_COLS; ++j)
		{
			if (TOTAL_TILES > buildGrid[i][j].type && EMPTY_PATH <= buildGrid[i][j].type)
				AddSprite(path[buildGrid[i][j].type], (i * GRID_SYSTEM_WIDTH) + (GRID_SYSTEM_WIDTH * buildGrid[i][j].size_x * 0.5f), (j * GRID_SYSTEM_HEIGHT) + (GRID_SYSTEM_HEIGHT * buildGrid[i][j].size_y * 0.5f), GRID_SYSTEM_WIDTH * buildGrid[i][j].size_x + 0.1f, GRID_SYSTEM_HEIGHT * buildGrid[i][j].size_y + 0.1f, ALPHA, PATH_LAYER);
		}
	}
}

/*!
@brief	Drawing of grid lines
*//*_____________________________________________________________________________*/
void DrawGridLine(void)
{
	// Drawing verticle lines
	for (unsigned i = 0; i < GRID_SYSTEM_COLS; ++i)
	{
		// Verticle
		AddLine(0.0f, (float)(GRID_SYSTEM_HEIGHT * (i + 1)), (float)CP_System_GetWindowWidth(), (float)(GRID_SYSTEM_HEIGHT * (i + 1)), 1.0f, COLOR_BLACK, GRID_LINE_LAYER);
	}
	// Drawing horizontal lines
	for (unsigned i = 0; i < GRID_SYSTEM_ROWS; ++i)
	{
		// Horizontal
		AddLine((float)(GRID_SYSTEM_WIDTH * (i + 1)), 0.0f, (float)(GRID_SYSTEM_WIDTH * (i + 1)), (float)CP_System_GetWindowHeight(), 1.0f, COLOR_BLACK, GRID_LINE_LAYER);
	}
}

/*!
@brief	Check if current grid can build tower

@param	pos: mouse position
		grid: grid information of tower

@return	true if the current grid is not occupied by any path/tower
*//*_____________________________________________________________________________*/
Boolean AbleToBuild(Point pos, Grid grid)
{
	if (0 > pos.x || GRID_SYSTEM_ROWS < pos.x + grid.size_x || 0 > pos.y || GRID_SYSTEM_COLS < pos.y + grid.size_y)
		return False;
	
	for (unsigned row = 0; row < grid.size_x; ++row)
	{
		for (unsigned col = 0; col < grid.size_y; ++col)
		{
			if (buildGrid[(int)pos.x + row][(int)pos.y + col].type > EMPTY_PATH)
				return False;
		}
	}
	return True;
}

/*!
@brief	Build and update build grid

@param	pos: mouse position
		grid: grid information of tower
*//*_____________________________________________________________________________*/
Boolean BuildOntoGrid(Point pos, Grid grid, GridType gridType)
{
	if (!AbleToBuild(pos, grid))
		return False;

	for (int row = 0; row < (int)grid.size_x; ++row)
	{
		for (int col = 0; col < (int)grid.size_y; ++col)
		{
			buildGrid[(int)pos.x + row][(int)pos.y + col].type = gridType;
		}
	}

	buildGrid[(int)pos.x][(int)pos.y].size_x = grid.size_x;
	buildGrid[(int)pos.x][(int)pos.y].size_y = grid.size_y;
	return True;
}

Point GetPositionOnGrid(Point pos, unsigned size_x, unsigned size_y)
{	
	float pos_x = (pos.x * GRID_SYSTEM_WIDTH) + (GRID_SYSTEM_WIDTH * size_y * 0.5f);
	float pos_y = (pos.y * GRID_SYSTEM_HEIGHT) + (GRID_SYSTEM_HEIGHT * size_x * 0.5f);

	Point p = { pos_x , pos_y };
	return p;
}

/*!
@brief	Removes the tower from the grid (call this when sell tower)

@param	pos: tower's position
*//*_____________________________________________________________________________*/
void RemoveTowerOffGrid(Point pos, Grid grid)
{
	int x = (int)(pos.x / GRID_SYSTEM_WIDTH) - 1;
	int y = (int)(pos.y / GRID_SYSTEM_HEIGHT) - 1;

	for (unsigned row = 0; row < grid.size_x; ++row)
	{
		for(unsigned col = 0; col < grid.size_y; ++col)
			buildGrid[x + row][y + col].type = GRID_NOT_OCCUPIED;
	}

	buildGrid[x][y].size_x = 1;
	buildGrid[x][y].size_y = 1;
}

/*!
@brief	Function to deallocate memories
*//*_____________________________________________________________________________*/
void FreeGridSystem(void)
{
	for (unsigned i = 0; i < TOTAL_TILES; ++i)
	{
		CP_Image_Free(&path[i]);
	}

	for (unsigned i = 0; i < GRID_SYSTEM_ROWS; ++i)
	{
		for (unsigned j = 0; j < GRID_SYSTEM_COLS; ++j)
			buildGrid[i][j].type = GRID_NOT_OCCUPIED;
	}
	gridGameState = False;
}

#if DEBUG_GRID_SYSTEM
CP_Image GetPathImage(int index)
{
	return path[index];
}
#endif