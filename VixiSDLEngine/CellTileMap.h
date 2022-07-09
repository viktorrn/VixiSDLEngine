#pragma once
#include "libDependecies.h"
#include "Tile.h"
#include "AssetManager.h"
#include "Game.h"
#include "Vector2D.h"
#include <Map>


using namespace std;

struct Cell;

class CellTileMap
{
public:
	SDL_Rect src, dest;
	size_t currentTileSelected = 3;
	size_t width;
	size_t height;
	vector<pair<size_t, size_t>> cellMoves;
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
	bool IsEmpty(size_t x, size_t y);
	bool CompareDensityAndBounds(size_t x, size_t y, const Cell* cell);
	bool CompareDensity(size_t i, const Cell* cell);

	bool MoveDown(size_t x, size_t y, const Cell* cell);
	bool MoveDownAndSide(size_t x, size_t y, const Cell* cell);
	bool MoveSide(size_t x, size_t y, const Cell* cell);
	int findIfEmptyToSide(size_t x, size_t y, size_t dir, int dispersity);
	
	void SetCell(size_t i, size_t id);
	void MoveCell(size_t x, size_t y, size_t xto, size_t yto);
	void AddCell(size_t i, size_t id);
	void CommitMoves();


private:

};