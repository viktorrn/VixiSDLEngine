#pragma once
#include "libDependecies.h"
#include "Tile.h"
#include "AssetManager.h"
#include "Game.h"
#include "Vector2D.h"
#include <Map>
#include <deque>


using namespace std;

enum class CellProperties
{
	NONE = 0b00000000,
	MOVE_DOWN = 0b00000001,
	MOVE_DOWN_SIDE = 0b00000010,
	MOVE_SIDE = 0b00000100,
};


enum class CellType
{
	EMPTY = 0b00000000,
	ROCK = 0b00000001,
	SAND = 0b00000010,
	WATER = 0b00000011
};

struct Cell
{
	CellType		Type = CellType::EMPTY;
	int				Props = static_cast<int>(CellProperties::NONE);
	bool			Active = false;
	bool			ForcedMove = false;
	int				FramesSinceMoving = 0;
	int				DispersityRate = 1;
	int				Variant = 0;
	int				Density = 12;

	Cell() {};
	Cell(CellType t, Uint8 p, int disp, int dens)
	{
		Type = t;
		Props = p;
		Active = true;
		DispersityRate = disp;
		Density = dens;		
		Variant = Game::GetRandom(1);
	}
};

struct Move
{
	size_t start;
	size_t end;

	Move(size_t a, size_t b)
	{
		start = a;
		end = b;
	}
};

class CellTileMap
{
public:
	SDL_Rect src, dest;
	size_t currentTileSelected = 3;
	size_t width;
	size_t height;
	deque<Move> cellMoves;
	vector<Cell*> Matrix;



	CellTileMap() 
	{
		
		//cellData.emplace(0, { CellType::EMPTY, CellProperties::NONE });
		//cellMoves = new vector<pair<size_t, size_t>>();
	};

	~CellTileMap()
	{
		//delete[] Matrix;
	};

	void AdjustCellMap(size_t width, size_t height);
	void LoadCellMap(std::string path, size_t sizeX, size_t sizeY);
	void LoadCellTypes();
	void GenerateCellMap();
	void Draw();
	void Update();

	size_t calcIndex(size_t x, size_t y);
	const Cell* GetCell(size_t x, size_t y);
	const Cell* GetCell(size_t index);
	Cell* CreateCell(size_t id);

	bool InBounds(size_t x, size_t y);
	bool InBounds(size_t i);
	bool IsEmpty(size_t x, size_t y);
	bool CompareDensityAndBounds(const Cell* cell, size_t xTaget, size_t yTarget);
	bool HasGreaterDensity(const Cell* cell1, const Cell* cell2);

	bool MoveUp(size_t x, size_t y, const Cell* cell);
	bool MoveUpAndSide(size_t x, size_t y, const Cell* cell);
	bool MoveDown(size_t x, size_t y, const Cell* cell);
	bool MoveDownAndSide(size_t x, size_t y, const Cell* cell);
	bool MoveSide(size_t x, size_t y, const Cell* cell);
	int findIfEmptyToSide(size_t x, size_t y, size_t dir, int dispersity);
	bool EnvokedMovment(const Cell* envoker, int& envI, const Cell* cell, int& cellI);
	void SetCell(size_t i, size_t id);
	void MoveCell(size_t x, size_t y, size_t xto, size_t yto);
	void AddCell(size_t i, size_t id);
	void CommitMoves();


private:

};