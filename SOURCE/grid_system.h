/*!
file:	grid_system.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	function declarations for handling grid system

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	GRID_SYSTEM_H
#define GRID_SYSTEM_H

#include "common_headers.h"
 
#define DEBUG_GRID_SYSTEM		1

typedef enum GridType
{
	// Path where towers can be built onto
	GRID_NOT_OCCUPIED = -1,
	EMPTY_PATH,

	// Path where towers cannot be built onto
	HORIZONTAL_PATH,
	VERTICLE_PATH,
	L_JUNCTION_1,
	L_JUNCTION_2,
	L_JUNCTION_3,
	L_JUNCTION_4,
	T_JUNCTION_1,
	T_JUNCTION_2,
	T_JUNCTION_3,
	T_JUNCTION_4,
	X_JUNCTION,
	EDGE_1,
	EDGE_2,
	EDGE_3,
	EDGE_4,
	TREE_1,
	TREE_2,
	TREE_3,
	TREE_4,
	TREE_5,
	CASTLE,
#if LEVEL_EDITOR_MODE
	WAY_POINTS,
#endif
	TOTAL_TILES,

	// Special tile enums
	GRID_OCCUPIED,	
	TOWER,
	// more to be added here
}GridType;

typedef struct Grid
{
	unsigned size_x;		// 1x1,2x2,3x1 etc...
	unsigned size_y;		// 1x1,2x2,3x1 etc...
	GridType type;
} Grid;

void InitGrid(const char* fileName);
void DrawGrid(void);
void DrawGridLine(void);
Boolean AbleToBuild(Point pos, Grid grid);
Boolean BuildOntoGrid(Point pos, Grid grid, GridType gridType);
Point GetPositionOnGrid(Point pos, unsigned size_x, unsigned size_y);
void RemoveTowerOffGrid(Point pos, Grid grid);

#if DEBUG_GRID_SYSTEM
CP_Image GetPathImage(int index);
#endif

#endif