/*!
file:	quad.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	quad tree implementation

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "quad.h"
#include "common_headers.h"

#define QUAD_WIDTH				(float)CP_System_GetWindowWidth()
#define QUAD_HEIGHT				(float)CP_System_GetWindowHeight()
#define CIRCLE_DIAMETER			2.5f
#define STROKE_WEIGHT			1.25f
#define STROKE_WEIGHT_CIRCLE	0.1f

typedef struct Quad
{
	Node* node;

	Quad* topLeft;
	Quad* topRight;
	Quad* btmLeft;
	Quad* btmRight;

	Rect box;

	Boolean divided;
}Quad;

Quad *quadTree;
Enemy* quad_enemies;

//const int TREE_DEPTH = 5;
unsigned currEnemy;

void Insert(Quad** quad, Enemy* pos, float width, float height, float offsetWidth, float offsetHeight, int depth);
void QuadInsert(Enemy* enemy);

Quad* quadAllocator = NULL;
Node* nodeAllocator = NULL;
unsigned quadSize = 0, quadIndex = 0, nodeSize = 0, nodeIndex = 0;
const unsigned ALLOC_SIZE = 20;

/*!
@brief	to delete enemy's data from quad tree

@param	quad: reference to the current quad
		id: id tagged to the enemy
*//*__________________________________________________________*/
Boolean DeleteEnemyQuad(Quad** quad, const unsigned id)
{
	// if current quad is not initialised
	if (!(*quad))
		return False;
	// if current node is not initalised, search children
	else if (!(*quad)->node)
	{
		if (DeleteEnemyQuad(&(*quad)->topLeft, id));
		else if (DeleteEnemyQuad(&(*quad)->topRight, id));
		else if (DeleteEnemyQuad(&(*quad)->btmLeft, id));
		else if (DeleteEnemyQuad(&(*quad)->btmRight, id));

		// check if all the nodes in the current quad is null
		if (!(*quad)->topLeft && !(*quad)->topRight && !(*quad)->btmLeft && !(*quad)->btmRight)
		{
			(*quad) = NULL;
		}
		return True;
	}
	// if current node is initalised, search current node
	else if ((*quad)->node)
	{
		Boolean removed = False;

		for (unsigned i = 0; i < (*quad)->node->currNodeSize; ++i)
		{
			if ((*quad)->node->ePtr[i] && (*quad)->node->ePtr[i]->id != id)
				continue;

			(*quad)->node->ePtr[i] = NULL;
			(*quad)->node->currNodeSize -= 1;

			removed = True;
			break;
		}

		// if current node <= 0 
		if (0 >= (*quad)->node->currNodeSize)
		{
			// delete current node
			(*quad)->node = NULL;
		}
		return removed;
	}
	return False;
}

/*!
@brief	to delete enemy's data from quad tree
@param	id: id tagged to the enemy
*//*__________________________________________________________*/
void DeleteEnemy(const unsigned id)
{
	// recursive thru the entire to find the enemy with the same id;
	if (DeleteEnemyQuad(&quadTree->topLeft, id))
		return;
	if (DeleteEnemyQuad(&quadTree->topRight, id))
		return;
	if (DeleteEnemyQuad(&quadTree->btmLeft, id))
		return;
	if (DeleteEnemyQuad(&quadTree->btmRight, id))
		return;
}

void DeleteQuad(Quad** quad)
{
	if (!(*quad))
		return;
	else if ((*quad))
	{
		DeleteQuad(&(*quad)->topLeft);
		DeleteQuad(&(*quad)->topRight);
		DeleteQuad(&(*quad)->btmLeft);
		DeleteQuad(&(*quad)->btmRight);

		(*quad) = NULL;
	}
}

void DeleteQuadTree(void)
{
	if (!quadTree)
		return;

	DeleteQuad(&quadTree->topLeft);
	DeleteQuad(&quadTree->topRight);
	DeleteQuad(&quadTree->btmLeft);
	DeleteQuad(&quadTree->btmRight);
}

/*!
@brief	main function call to update quad tree
*//*__________________________________________________________*/
void UpdateQuadTree(void)
{
	DeleteQuadTree();
	quadIndex = 1;
	nodeIndex = 0;
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (!quad_enemies[i].alive)
			break;
		QuadInsert(&quad_enemies[i]);
	}
}

/*!
@brief	Reset variables for searching through quad tree to find enemies
*//*_____________________________________________________________________________*/
void DefaultSearchEnemy(void)
{
	currEnemy = 0;
}

/*!
@brief	Recursive function to search the quad tree to see if an enemy lies
		within the circle

@param	quad: reference to the current quad
		cir: circle area for checking
*//*_____________________________________________________________________________*/
void SearchCircleEnemy(Quad** quad, Enemy** eArr, Circle cir)
{
	// if current quad is empty, return
	if (!(*quad))
		return;
	// if current quad's node is empty, search for children
	else if (!(*quad)->node)
	{
		SearchCircleEnemy(&(*quad)->topLeft, eArr, cir);
		SearchCircleEnemy(&(*quad)->topRight, eArr, cir);
		SearchCircleEnemy(&(*quad)->btmLeft, eArr, cir);
		SearchCircleEnemy(&(*quad)->btmRight, eArr, cir);
		return;
	}
	// if current quad's node is not empty, and the quad is intersecting with the circle
	else if ((*quad)->node && CircleRectCollision(cir, (*quad)->box))
	{
		//search through all the elements in the array, then compare to see if the points is inside the circle
		for (unsigned i = 0; i < (*quad)->node->currNodeSize; ++i)
		{
			if (!(*quad)->node->ePtr[i])
				continue;
			Point enemy_min = { (*quad)->node->ePtr[i]->position.x - (*quad)->node->ePtr[i]->width * 0.5f, (*quad)->node->ePtr[i]->position.y - (*quad)->node->ePtr[i]->height * 0.5f };
			Point enemy_max = { (*quad)->node->ePtr[i]->position.x + (*quad)->node->ePtr[i]->width * 0.5f, (*quad)->node->ePtr[i]->position.y + (*quad)->node->ePtr[i]->height * 0.5f };
			Rect enemy_rect = {enemy_min, enemy_max, (*quad)->node->ePtr[i]->width, (*quad)->node->ePtr[i]->height };
			// use CircleRectCollision() to find collision between the skill radius and enemy's image (rect)
			if (!CircleRectCollision(cir, enemy_rect))
				continue;

			// if pArr overflows, break;
			if (ENEMY_SIZE <= currEnemy)
				break;

			for (unsigned j = 0; j < currEnemy; ++j)
			{
				if (eArr[j] && eArr[j]->id == (*quad)->node->ePtr[i]->id)
					return;
			}
			eArr[currEnemy++] = (*quad)->node->ePtr[i];
		}
		return;
	}
}

/*!
@brief	Get references to the enemy within the quad tree
		
@param	pos: position of object (skill/tower/etc...)
		radius: length from the pos within the circle
		
@return	An array of enemy if it is within the circle
*//*_____________________________________________________________________________*/
void GetEnemy(Enemy** eArr, Point pos, float radius)
{
	if (pos.x < 0 || pos.x > QUAD_WIDTH || pos.y < 0 || pos.y > QUAD_HEIGHT)
		return;

	Circle cir = { pos, radius };

	DefaultSearchEnemy();
	SearchCircleEnemy(&quadTree, eArr, cir);
}

void InitQuadTreeEnemyReference(Enemy* enemy)
{
	quad_enemies = enemy;
}

/*!
@brief	Set initial quad value
@param	quad: Reference to quad's children
		pos: position of the quad (AABB)
		width: width for AABB
		height: height for AABB
*//*_____________________________________________________________________________*/
void DefaultQuad(Quad** quad, Point pos, float width, float height)
{
	(*quad)->node = NULL;
	(*quad)->topLeft = NULL;
	(*quad)->topRight = NULL;
	(*quad)->btmLeft = NULL;
	(*quad)->btmRight = NULL;
	(*quad)->divided = False;

	// initialising of box
	Point min = { pos.x - width / 2.0f,  pos.y - height / 2.0f };
	(*quad)->box.Min = min;
	Point max = { pos.x + width / 2.0f, pos.y + height / 2.0f };
	(*quad)->box.Max = max;
	(*quad)->box.w = width;
	(*quad)->box.h = height;
}

/*!
@brief	Splitting the current quad's node and allocating it into their children

@param	quad: Reference to quad's children
		pos: reference to the enemy
		width: width of the current square
		height: height of the current square
		offsetWidth: offset x position if it's on the right column
		offsetheight: offset y position if it's on the bottom row
*//*_____________________________________________________________________________________________________________________________*/
void DivideQuad(Quad** quad, Enemy* enemy, float width, float height, float offsetWidth, float offsetHeight, int depth)
{
	float w = (width / 2.0f) + offsetWidth;
	float h = (height / 2.0f) + offsetHeight;

	// top left
	if (enemy->position.x <= w && enemy->position.y <= h)
	{
		//printf("Top Left\n");
		Insert(&(*quad)->topLeft, enemy, (width / 2.0f), (height / 2.0f), offsetWidth, offsetHeight, depth++);
	}
	// top right
	else if (enemy->position.x > w && enemy->position.y <= h)
	{
		//printf("Top Right\n");
		Insert(&(*quad)->topRight, enemy, (width / 2.0f), (height / 2.0f), w, offsetHeight, depth++);
	}
	// btm left
	else if (enemy->position.x <= w && enemy->position.y > h)
	{
		//printf("Btm Left\n");
		Insert(&(*quad)->btmLeft, enemy, (width / 2.0f), (height / 2.0f), offsetWidth, h, depth++);
	}
	// btm right
	else if (enemy->position.x > w && enemy->position.y > h)
	{
		//printf("Btm Right\n");
		Insert(&(*quad)->btmRight, enemy, (width / 2.0f), (height / 2.0f), w, h, depth++);
	}
}

/*!
@brief	Insert into quad tree

@param	quad: Reference to quad's children
		pos: reference to the enemy
		width: width of the current square
		height: height of the current square
		offsetWidth: offset x position if it's on the right column
		offsetheight: offset y position if it's on the bottom row
*//*_____________________________________________________________________________________________________________________________*/
void Insert(Quad** quad, Enemy* enemy, float width, float height, float offsetWidth, float offsetHeight, int depth)
{
	//if (depth > TREE_DEPTH)
	//	return;
	if (!(*quad))
	{
		// ... initialise and store value here
		if (quadIndex + 1 >= quadSize)
		{
			quadSize += ALLOC_SIZE;
			Quad* tmp = quadAllocator;
			quadAllocator = (Quad*)malloc(sizeof(Quad) * quadSize);
			memcpy_s(quadAllocator, sizeof(Quad) * quadSize, tmp, sizeof(Quad) * (quadSize - ALLOC_SIZE));
			free(tmp);
		}
		(*quad) = quadAllocator + quadIndex++;

		Point p = { (width / 2.0f) + offsetWidth, (height / 2.0f) + offsetHeight };
		DefaultQuad(&(*quad), p, width, height);

		if (nodeIndex + 1 >= nodeSize)
		{
			nodeSize += ALLOC_SIZE;
			Node* tmp = nodeAllocator;
			nodeAllocator = (Node*)malloc(sizeof(Node) * nodeSize);
			memcpy_s(nodeAllocator, sizeof(Node) * nodeSize, tmp, sizeof(Node) * (nodeSize - ALLOC_SIZE));
			free(tmp);
		}
		(*quad)->node = nodeAllocator + nodeIndex++;

		// giving default null values (not holding any address)
		for (unsigned i = 0; i < NODE_SIZE; ++i)
			(*quad)->node->ePtr[i] = NULL;
		(*quad)->node->currNodeSize = 0;
		(*quad)->node->ePtr[(*quad)->node->currNodeSize] = enemy;
		(*quad)->node->checked = False;

		(*quad)->node->currNodeSize += 1;
	}
	else if ((*quad))
	{
		if (!(*quad)->divided)
		{
			// current node is storing < NODE_SIZE
			if (NODE_SIZE > (*quad)->node->currNodeSize)
			{
				// use current node to store reference to enemy
				for (unsigned i = 0; i < NODE_SIZE; ++i)
				{
					if (NULL != (*quad)->node->ePtr[i])
						continue;

					// find an empty storage and store it
					(*quad)->node->ePtr[(*quad)->node->currNodeSize] = enemy;
					break;
				}
				(*quad)->node->currNodeSize += 1;
				return;
			}
			// current node is trying to store < NODE_SIZE
			else
			{
				// divide the quad
				for (int i = 0; i < NODE_SIZE; ++i)
				{
					if (!(*quad)->node->ePtr[i])
						continue;
					DivideQuad(&(*quad), (*quad)->node->ePtr[i], width, height, offsetWidth, offsetHeight, depth++);
				}

				DivideQuad(&(*quad), enemy, width, height, offsetWidth, offsetHeight, depth++);
				(*quad)->divided = True;

				// then deallocate current's node memory
				(*quad)->node = NULL;
				return;
			}
		}
		else if((*quad)->divided)
		{
			DivideQuad(&(*quad), enemy, width, height, offsetWidth, offsetHeight, depth++);
		}
	}

	return;
}

/*!
@brief	Insert a new data based on it's current 2D position

@param	pos: 2D position on the screen
		data: data to be stored
*//*_____________________________________________________________________________*/
void QuadInsert(Enemy* enemy) // changing this to take enemy reference
{
	if (enemy->position.x < 0 || enemy->position.x > QUAD_WIDTH || enemy->position.y < 0 || enemy->position.y > QUAD_HEIGHT)
		return;

	float w = (QUAD_WIDTH / 2.0f);
	float h = (QUAD_HEIGHT / 2.0f);

	if (!quadAllocator)
	{
		quadAllocator = (Quad*)malloc(sizeof(Quad) * ALLOC_SIZE);
		nodeAllocator = (Node*)malloc(sizeof(Node) * ALLOC_SIZE);

		quadSize = ALLOC_SIZE;
		nodeSize = ALLOC_SIZE;

		quadIndex = 0;
		nodeIndex = 0;

		quadTree = quadAllocator + quadIndex++;

		Point p = { w, h };
		DefaultQuad(&quadTree, p, QUAD_WIDTH, QUAD_HEIGHT);
	}

	// top left
	if (enemy->position.x <= w && enemy->position.y <= h)
	{
		//printf("Top Left\n");
		Insert(&quadTree->topLeft, enemy, w, h, 0, 0, 0);
	}
	// top right
	else if (enemy->position.x > w && enemy->position.y <= h)
	{
		//printf("Top Right\n");
		Insert(&quadTree->topRight, enemy, w, h, w, 0, 0);
	}
	// btm left
	else if (enemy->position.x <= w && enemy->position.y > h)
	{
		//printf("Btm Left\n");
		Insert(&quadTree->btmLeft, enemy, w, h, 0, h, 0);
	}
	// btm right
	else if (enemy->position.x > w && enemy->position.y > h)
	{
		//printf("Btm Right\n");
		Insert(&quadTree->btmRight, enemy, w, h, w, h, 0);
	}
}

/*!
@brief	Drawing of the quad tree

@param	quad: Reference to quad's children
		width: width of the current square
		height: height of the current square
		x1: first x position of the line
		y1: first y position of the line
		x2: second x position of the line
		y2: second y position of the line
*//*_____________________________________________________________________________________________________________________________*/
void DrawTree(Quad **quad, float width, float height, float x1, float y1, float x2, float y2)
{
	if (!(*quad))
		return;

	if ((*quad)->node)
	{
		CP_Settings_StrokeWeight(STROKE_WEIGHT_CIRCLE);
		CP_Settings_Fill(COLOR_RED);

		for (unsigned i = 0; i < (*quad)->node->currNodeSize; ++i)
		{
			if (!(*quad)->node->ePtr[i])
				continue;
			CP_Graphics_DrawCircle((*quad)->node->ePtr[i]->position.x, (*quad)->node->ePtr[i]->position.y, CIRCLE_DIAMETER);
		}
		return;
	}

	float w = (width / 2.0f) + x1;
	float h = (height / 2.0f) + y1;

	AddLine(x1, (y1 + y2) / 2.0f, x2, (y1 + y2) / 2.0f, 1.0f, COLOR_BLACK, QUAD_TREE_LAYER);
	AddLine((x1 + x2) / 2.0f, y1, (x1 + x2) / 2.0f, y2, 1.0f, COLOR_BLACK, QUAD_TREE_LAYER);

	// Top Left
	DrawTree(&(*quad)->topLeft, w, h, x1, y1, (x1 + x2) / 2.0f, (y1 + y2) / 2.0f);
	// Top Right
	DrawTree(&(*quad)->topRight, w, h, (x1 + x2) / 2.0f, y1, x2, (y1 + y2) / 2.0f);
	// Btm Left
	DrawTree(&(*quad)->btmLeft, w, h, x1, (y1 + y2) / 2.0f, (x1 + x2) / 2.0f, y2);
	// Btm Right
	DrawTree(&(*quad)->btmRight, w, h, (x1 + x2) / 2.0f, (y1 + y2) / 2.0f, x2, y2);
}

/*!
@brief	Draw quad tree using recursion
*//*________________________________________________________________________________________*/
void DrawQuadTree()
{
	if (!quadTree)
		return;

	float w = (QUAD_WIDTH / 2.0f);
	float h = (QUAD_HEIGHT / 2.0f);

	AddLine(0.0f, h, QUAD_WIDTH, h, 1.0f, COLOR_BLACK, QUAD_TREE_LAYER);
	AddLine(w, 0.0f, w, QUAD_HEIGHT, 1.0f, COLOR_BLACK, QUAD_TREE_LAYER);

	DrawTree(&quadTree->topLeft, w, h, 0, 0, w, h);
	DrawTree(&quadTree->topRight, w, h, w, 0, QUAD_WIDTH, h);
	DrawTree(&quadTree->btmLeft, w, h, 0, h, w, QUAD_HEIGHT);
	DrawTree(&quadTree->btmRight, w, h, w, h, QUAD_WIDTH, QUAD_HEIGHT);
}

/*!
@brief	Deallocation of memory in heap

@param	quad: Reference to quad's children
*//*________________________________________________________________________________________*/
void FreeQuadPointers(Quad **quad)
{
	if ((*quad))
	{
		// free current quad's node
		if ((*quad)->node)
		{
			(*quad)->node = NULL;
		}

		// then go in and find children's node and deallocate their memory from the heap
		if((*quad)->topLeft)
			FreeQuadPointers(&(*quad)->topLeft);

		if ((*quad)->topRight)
			FreeQuadPointers(&(*quad)->topRight);

		if ((*quad)->btmLeft)
			FreeQuadPointers(&(*quad)->btmLeft);

		if ((*quad)->btmRight)
			FreeQuadPointers(&(*quad)->btmRight);

		// finally, free this quad's memory
		if ((*quad))
		{
			(*quad) = NULL;
		}
	}

	// return if quad is NULL or when reaches the end
	return;
}

/*!
@brief	calls recursive function to deallocate
		memory of nodes
*//*__________________________________________________________*/
void FreeQuadTree()
{
	if (quadTree)
	{
		FreeQuadPointers(&quadTree->topLeft);
		FreeQuadPointers(&quadTree->topRight);
		FreeQuadPointers(&quadTree->btmLeft);
		FreeQuadPointers(&quadTree->btmRight);

		quadTree = NULL;
	}
	if (quadAllocator)
	{
		free(quadAllocator);
		quadAllocator = NULL;
	}
	if (nodeAllocator)
	{
		free(nodeAllocator);
		nodeAllocator = NULL;
	}

	quadSize = 0;
	quadIndex = 0;
	nodeSize = 0;
	nodeIndex = 0;
	currEnemy = 0;
}
