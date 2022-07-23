#pragma once
#include "libDependecies.h"
#include "Tile.h"
#include "AssetManager.h"
#include "Game.h"
#include "Vector2D.h"
#include <Map>
#include <deque>

const int ChunkSize = 2;
using namespace std;
class CellTileMap;
class CellChunk;

enum class CellProperties
{
	NONE =				0b00000000,
	MOVE_DOWN =			0b00000001,
	MOVE_DOWN_SIDE =	0b00000010,
	MOVE_SIDE =			0b00000100,
	MOVE_UP =			0b00001000,
	MOVE_UP_SIDE =		0b00010000,
};


enum class CellType
{
	EMPTY = 0b00000000,
	ROCK =	0b00000001,
	SAND =	0b00000010,
	WATER = 0b00000011,
	GRASS = 0b00000100,
	MIST =	0b00000101,
	FIRE =	0b00000110
	
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
	int				Density = 0;

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
	size_t localStart;
	size_t worldEnd;
	CellChunk* residingChunk;
	CellChunk* targetChunk;
	Move(size_t a, size_t b,  CellChunk* rc,  CellChunk* tc)
	{
		localStart = a;
		worldEnd = b;
		residingChunk = rc;
		targetChunk = tc;

	}
};

static Cell* CreateCell(size_t id)
{
	Cell* ptr;
	switch (id)
	{

	case 1:
		ptr = new Cell(
			CellType::ROCK,
			static_cast<int>(CellProperties::NONE),
			0,
			100
		);
		break;

	case 2:
		ptr = new Cell(
			CellType::SAND,
			static_cast<int>(CellProperties::MOVE_DOWN) + static_cast<Uint8>(CellProperties::MOVE_DOWN_SIDE) + static_cast<Uint8>(CellProperties::MOVE_SIDE),
			1,
			20
		);
		break;

	case 3:
		ptr = new Cell(
			CellType::WATER,
			static_cast<int>(CellProperties::MOVE_DOWN) + static_cast<Uint8>(CellProperties::MOVE_SIDE) + static_cast<Uint8>(CellProperties::MOVE_DOWN_SIDE),
			4,
			15
		);
		break;
	case 4:
		ptr = new Cell(
			CellType::GRASS,
			static_cast<int>(CellProperties::NONE),
			0,
			50
		);
		break;
	case 5:
		ptr = new Cell(
			CellType::MIST,
			static_cast<int>(CellProperties::MOVE_UP) + static_cast<int>(CellProperties::MOVE_SIDE),
			2,
			13
		);
		break;
	default:
		ptr = new Cell();
		break;
	}

	return ptr;
}

class CellChunk
{
public:
	size_t M_x;
	size_t M_y;
	const size_t C_width = ChunkSize;
	const size_t C_height = ChunkSize;
	deque<Move> cellMoves;
	vector<Cell*> Matrix;
	CellTileMap* world;

	CellChunk(size_t mx, size_t my, CellTileMap* wrld)
	{
		M_x = mx;
		M_y = my;
		world = wrld;
		cout << " Created CellChunk";
	}
	~CellChunk()
	{

	};

	void CreateEmptyChunk() { CreateEmptyChunk(0); }
	void CreateEmptyChunk(int t) { for (size_t i(0u); i < C_width * C_height; i++)	AddCell(i, 0); }
	void Update();
	void CommitMoves();

	
	void AddCell(size_t i, size_t id)				{ Matrix.insert(Matrix.begin() + i, 
													  CreateCell(id));					}
	const Cell* GetCell(size_t x, size_t y)			{ return Matrix[calcLocalIndex(x, y)];	}
	const Cell* GetCell(size_t index)				{ return Matrix[index];				}
	void SetCell(size_t x, size_t y, size_t id)		{ SetCell(y * ChunkSize + x, id);	}
	void SetCell(size_t i, size_t id)				{ Matrix[i] = CreateCell(id);		}
	static size_t calcLocalIndex(size_t x, size_t y)		{ return y * ChunkSize + x;			}

	bool InBounds(size_t x, size_t y) { return x >= 0 && y >= 0 && x < C_width && y < C_height; };
	bool InBounds(size_t i) { return i >= 0 && i < C_width* C_height; };
	bool IsEmpty(size_t x, size_t y) { return InBounds(x, y) && GetCell(x, y)->Type == CellType::EMPTY; };
	bool CompareDensityAndBounds(const Cell* cell,
		size_t xTaget, size_t yTarget);

	bool HasGreaterDensity(const Cell* cell1, const Cell* cell2)
	{
		return cell1->Density > cell2->Density;
	}

	int findIfEmptyToSide(size_t x, size_t y, size_t dir, int dispersity);
	bool MoveUp(size_t x, size_t y, const Cell* cell);
	bool MoveUpAndSide(size_t x, size_t y, const Cell* cell);
	bool MoveDown(size_t x, size_t y, const Cell* cell);
	bool MoveDownAndSide(size_t x, size_t y, const Cell* cell);
	bool MoveSide(size_t x, size_t y, const Cell* cell);

	void MoveCell(size_t x, size_t y, size_t xto, size_t yto)
	{
		cout << "Move cell activated " << endl;
		//cellMoves.emplace_back(calcIndex(x, y), calcIndex(xto, yto));
	
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
	std::map<pair<size_t, size_t>, CellChunk*> chunckMap;


	CellTileMap() {};

	~CellTileMap(){};

	void AdjustCellMap(size_t width, size_t height);
	void LoadCellMap(std::string path, size_t sizeX, size_t sizeY);
	void GenerateCellMap();
	void Draw();
	void Update();

	size_t calcWorldIndex(size_t x, size_t y) {
		cout << "calc world index " << (y * width + x) << endl; return y * width + x;
	}
	
	Cell* GetCell(size_t world_x, size_t world_y)			
	{
		CellChunk* chunk = GetChunk(world_x , world_y);
		return chunk->Matrix[CalcChunkCoords(chunk,world_x,world_y)];
	}
	
	Cell* GetCell(size_t world_x, size_t world_y, CellChunk* chunk)
	{
		return chunk->Matrix[CalcChunkCoords(chunk, world_x, world_y)];
	}
	
	Cell* GetCell(size_t index, CellChunk* chunk)
	{ 
		int wx, wy;
		wx = index % ChunkSize;
		wy = index / ChunkSize;
		cout << "calced world coords " << wx << "," << wy << endl;
		return chunk->Matrix[CalcChunkCoords(chunk, wx, wy)];
	}

	Cell* GetCell(size_t index)				{ 
		int wx, wy;
		wx = index % ChunkSize;
		wy = index / ChunkSize;
		cout << "calced world coords " << wx << "," << wy << endl;
		CellChunk* chunk = GetChunk(wx , wy );
		cout << "chunk ptr " << chunk << endl;
		return chunk->Matrix[CalcChunkCoords(chunk,wx,wy)];
	}

	CellChunk* GetChunk(size_t ox, size_t oy);
	
	int CalcChunkCoords(const CellChunk* chunk, size_t index)
	{
		int wx, wy;
		wx = index % ChunkSize;
		wy = index / ChunkSize;
		cout << "calced coords " << wx << "," << wy << endl;
		return(wx - chunk->M_x + (wy - chunk->M_y) * ChunkSize);
	}

	int CalcChunkCoords(const CellChunk* chunk, size_t x, size_t y)
	{
		cout << " res index " << (x - chunk->M_x + (y - chunk->M_y) * ChunkSize) << endl;
		cout << " M data " << chunk->M_x << "," << chunk->M_y << endl;
		return(x - chunk->M_x + (y - chunk->M_y) * ChunkSize);
	}


	void SetCell(size_t i, size_t id)				{ Matrix[i] = CreateCell(id);		}
	void AddCell(size_t i, size_t id)				{ Matrix.insert(Matrix.begin() + i, 
													  CreateCell(id));					}

	bool InBounds(size_t x, size_t y)				{ return x >= 0 && y >= 0 && x < width  && y < height;};
	bool InBounds(size_t i) { cout << "bounds Check " << endl; return i >= 0 && i < width* height; };
	bool IsEmpty(size_t x, size_t y)				{ return InBounds(x, y) && GetCell(x, y)->Type == CellType::EMPTY; };

	bool CompareDensityAndBounds(const Cell* cell, 
		size_t xTaget, size_t yTarget) {			return InBounds(xTaget, yTarget) && HasGreaterDensity(cell,
													  GetCell(calcWorldIndex(xTaget, yTarget))); };

	bool HasGreaterDensity(const Cell* cell1, const Cell* cell2) 
	{
		cout << " dens check " << endl; return cell1->Density > cell2->Density;
	}

	int findIfEmptyToSide(size_t x, size_t y, size_t dir, int dispersity);

	bool MoveUp(size_t x, size_t y, const Cell* cell);
	bool MoveUpAndSide(size_t x, size_t y, const Cell* cell);
	bool MoveDown(size_t x, size_t y, const Cell* cell);
	bool MoveDownAndSide(size_t x, size_t y, const Cell* cell);
	bool MoveSide(size_t x, size_t y, const Cell* cell);

	void MoveCell(size_t x, size_t y, size_t xto, size_t yto,  CellChunk*curr)
	{
		CellChunk* tc = GetChunk(xto, yto);
		cellMoves.emplace_back( CellChunk::calcLocalIndex(x,y), calcWorldIndex(curr->M_x + xto, curr->M_y + yto) , curr, tc);
	}


	void CommitMoves();
	void CommitUpdates();


private:

};