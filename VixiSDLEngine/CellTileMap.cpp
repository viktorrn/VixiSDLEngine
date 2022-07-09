#include "CellTileMap.h"
#include <random>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "SDL.h"
#include "Game.h"
#include <deque>



using namespace std;

enum class CellProperties
{
	NONE			= 0b00000000,
	MOVE_DOWN		= 0b00000001,
	MOVE_DOWN_SIDE	= 0b00000010,
	MOVE_SIDE		= 0b00000100,
};


enum class CellType
{
	EMPTY	= 0b00000000,
	ROCK	= 0b00000001,
	SAND	= 0b00000010,
	WATER	= 0b00000011
};

struct Cell
{
	CellType		Type = CellType::EMPTY;
	int				Props = static_cast<int>(CellProperties::NONE);
	bool			Active = false;
	int				FramesSinceMoving = 0;
	int				DispersityRate = 1;
	int				Density = 12;
	
	//deque<int>		Visited;
	
	Cell() {};
	Cell(CellType t, Uint8 p,int disp, int dens)
	{
		Type = t;
		Props = p;
		Active = true;
		DispersityRate = disp;
		Density = dens;
	}
};


void CellTileMap::LoadCellTypes() {

}


void CellTileMap::AddCell(size_t i, size_t id)
{
	Matrix.insert(Matrix.begin() + i, CreateCell(id));
}

Cell* CellTileMap::CreateCell(size_t id)
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
			2,
			20
		);

			break;
	case 3:


		ptr = new Cell(
			CellType::WATER,
			static_cast<int>(CellProperties::MOVE_DOWN)  + static_cast<Uint8>(CellProperties::MOVE_SIDE) + static_cast<Uint8>(CellProperties::MOVE_DOWN_SIDE),
			7,
			15
		);
		break;
	case 0:
	default:
		ptr = new Cell();
		break;
	}
	return ptr;
}
void CellTileMap::SetCell(size_t i, size_t id)
{
	//delete Matrix[i];
	Matrix[i] = CreateCell(id);
}

void CellTileMap::AdjustCellMap(size_t width, size_t height)
{
	this->width = width;
	this->height = height;
}

void CellTileMap::LoadCellMap(std::string path, size_t sizeX, size_t sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);
	size_t i = 0;
	for (size_t y = 0; y < sizeY; y++)
	{
		for (size_t x = 0; x < sizeX; x++)
		{
			i = y * sizeX + x;
			mapFile.get(c);
			AddCell(i,atoi(&c));
			
			mapFile.ignore();

		}
	}

	mapFile.close();
}

void CellTileMap::GenerateCellMap() { for (size_t i(0u); i < width * height; i++) AddCell(i,0); }

const Cell* CellTileMap::GetCell(size_t x, size_t y){ return Matrix[calcIndex(x, y)]; }

const Cell* CellTileMap::GetCell(size_t index) {	return Matrix[index];	}

size_t CellTileMap::calcIndex(size_t x, size_t y) { return y * width + x; }

bool CellTileMap::InBounds(size_t x, size_t y) { return x < width && y < height  && x >= 0 && y >= 0;  };
bool CellTileMap::IsEmpty(size_t x, size_t y) { return CellTileMap::InBounds(x, y) && CellTileMap::GetCell(x, y)->Type == CellType::EMPTY; };
bool CellTileMap::CompareDensityAndBounds(size_t x, size_t y, const Cell* cell)
{
	return CellTileMap::InBounds(x, y) && CompareDensity(calcIndex(x, y), cell);
}
bool CellTileMap::CompareDensity(size_t i,  const Cell* cell) {
	return GetCell(i)->Density < cell->Density;
}

void CellTileMap::MoveCell(size_t x, size_t y, size_t xto, size_t yto)
{
	cellMoves.emplace_back(calcIndex(xto, yto), calcIndex(x, y));
}

bool CellTileMap::MoveDown(size_t x, size_t y, const Cell* cell)
{
	//bool down = IsEmpty(x, y + 1) || CompareDensityAndBounds(x, y + 1, cell);
	bool down = CompareDensityAndBounds(x, y + 1, cell);
	//cout << 
	if (down) MoveCell(x, y, x, y + 1);
	return down;
}

bool CellTileMap::MoveDownAndSide(size_t x, size_t y, const Cell* cell)
{
	//bool downLeft = IsEmpty(x - 1, y + 1) || CompareDensityAndBounds(x -1, y + 1, cell);
	//bool downRight = IsEmpty(x + 1, y + 1) || CompareDensityAndBounds(x + 1, y + 1, cell);
	bool downLeft =  CompareDensityAndBounds(x - 1, y + 1, cell);
	bool downRight = CompareDensityAndBounds(x + 1, y + 1, cell);
	if (downLeft && downRight)
	{
		downLeft = Game::GetRandom(2);
		downRight = !downLeft;
	}
	if (downLeft) MoveCell(x, y, x - 1, y + 1);
	else if (downRight) MoveCell(x, y, x + 1, y + 1);
	
	return downLeft || downRight;
}

bool VisitedRecently(int p, deque<int> visited)
{
	for (int i = 0; i < visited.size(); i++)
		if (p == visited[i]) return true;
	return false;
}


int CellTileMap::findIfEmptyToSide(size_t x, size_t y,size_t dir, int dispersity)
{
	int i = 1;
	while (i <= dispersity)
	{
		if(IsEmpty(x + i * dir, y)) return i * dir; 
		if (!IsEmpty(x + i*dir, y)) return (i - 1) * dir;
			//if(CompareDensity(getCell))
		i++;

	}
	return i*dir;
}

bool CellTileMap::MoveSide(size_t x, size_t y, const Cell* cell)
{
	int ld = findIfEmptyToSide(x, y,  -1, cell->DispersityRate);
	int rd = findIfEmptyToSide(x, y, 1, cell->DispersityRate);
	//if(ld > 0 || rd > 0)
	//cout << " ld " << ld << " rd " << rd << endl;
	bool left = (ld == 0) ? false : true;
	bool right = (rd == 0) ? false : true;
	
	if (left && right)
	{
		int r = Game::GetRandom(1);
		left = r;
		right = !left;
	}
	if (left) MoveCell(x, y, x +ld, y);
	else if (right) MoveCell(x, y, x + rd, y);
	return false;
}

void CellTileMap::Update()
{
	for (int i = 0; i < 4; i++)
	{
		if(Game::inputs->GetInputState(to_string(i)))
		{
			currentTileSelected = i;
		}
	}

	if (Game::inputs->GetInputState("mbl"))
	{
		size_t x, y, px, py, k, dx, dy, d;
		x = static_cast<size_t>(Game::inputs->GetMouseX()) / (Game::drawScale * Game::tileSize);
		y = static_cast<size_t>(Game::inputs->GetMouseY()) / (Game::drawScale * Game::tileSize);

		px = static_cast<size_t>(Game::inputs->GetPrevMouseX()) / (Game::drawScale * Game::tileSize);
		py = static_cast<size_t>(Game::inputs->GetPrevMouseY()) / (Game::drawScale * Game::tileSize);

		dx = x - px;
		dy = y - py;
		d = static_cast<int>(sqrt(dx * dx + dy * dy) + 0.5f);
		/*if (dx == 0 && dy == 0)
			
		if (dx == 0)
		{
			k = dy;
			for (int i(0u); i < d; i++)
			{

			}
		}*/
		for (int i(0u); i < 1; i++)
			for (int ii(0u); ii < 1; ii++)
				if (InBounds(x+ii, y+i))
				{
					cout << " placed tile " << currentTileSelected << " at " << x << "," << y << endl;
					SetCell(calcIndex(x + ii, y + i), currentTileSelected);
				}		
	}
	

	for (size_t y = 0; y < height; y++)
	for (size_t x = 0; x < width; x++)
	{
		
		const Cell* cell = GetCell(x, y);
		     if ( static_cast<bool>( cell->Props & static_cast<Uint8>(CellProperties::MOVE_DOWN))			&& MoveDown			(x, y, cell));
		else if ( static_cast<bool>( cell->Props & static_cast<Uint8>(CellProperties::MOVE_DOWN_SIDE))		&& MoveDownAndSide	(x, y, cell));
		else if ( static_cast<bool>( cell->Props & static_cast<Uint8>(CellProperties::MOVE_SIDE))			&& MoveSide			(x, y, cell));
	}


	CommitMoves();	

};

void CellTileMap::CommitMoves()
{
	if (cellMoves.size() <= 0) return;
	for (size_t i(0u); i < cellMoves.size(); i++)
	{//Matrix[cellMoves[i].first]->Type != CellType::EMPTY && 
		if (!CompareDensity(cellMoves[i].first, GetCell(cellMoves[i].second) ) )
		{
			cellMoves[i] = cellMoves.back(); cellMoves.pop_back();
			i--;
		}
	}



	sort(cellMoves.begin(), cellMoves.end(),
		[](auto& a, auto& b) {return a.first > b.first;  }
	);
	

	Cell* temp;
	size_t iprev = 0;
	size_t dst, src, rand, amount;
	size_t i = cellMoves.size();
	//cout << "cellMoves " << cellMoves.size() << endl;
	
	while (i > 0)
	{
		amount = 0;
		if(i-1 > amount-1)
		while (cellMoves[i-1].first == cellMoves[i - 2 - amount].first) amount++;


		rand = Game::GetRandom(amount);
		rand == 0;

		dst = cellMoves[i-1 + rand].first;
		src = cellMoves[i-1 + rand].second;
		
		temp = Matrix[dst];

		
		/*//Matrix[src]->Visited.emplace_front(src);
		//Matrix[src]->Visited.emplace_front(dst);
		//if (Matrix[src]->Visited.size() > 5)
		if (Matrix[src]->Visited.size() > 0)
			Matrix[src]->Visited.pop_back();
			*/
		Matrix[dst] = Matrix[src];
		Matrix[src] = temp;

		while(amount-- >0) cellMoves.pop_back(); 
		if(i > 0)
			cellMoves.pop_back();

		i = cellMoves.size();
	}
	cellMoves.clear();

}



void CellTileMap::Draw()
{
	SDL_Rect src;
	SDL_Rect dest;
	dest.w = dest.h = Game::tileSize * Game::drawScale;
	src.h = src.w = Game::tileSize;
	dest.x = dest.y = src.y = 0; src.x = 0; 
	size_t i = 0; size_t id = 0;
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++) 
		{
			i = y * width + x;
			id = static_cast<int>(Matrix[i]->Type);
			src.x = Game::tileSize * id;
			dest.x = x * Game::tileSize * Game::drawScale;
			dest.y = y * Game::tileSize * Game::drawScale;
			TextureManager::Draw(Game::assets->GetTexture("tile"), src, dest, SDL_FLIP_NONE);
			
		}	
	}
}
