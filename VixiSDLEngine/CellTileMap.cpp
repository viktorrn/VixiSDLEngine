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
void CellTileMap::GenerateCellMap() 
{ 
	int ox, oy;
	int i = 1;
	for (size_t y = 0; y < height; y++)
	{
		oy = y;
		for (size_t x = 0; x < width; x++)
		{
			ox = x;
			const auto& chunk = GetChunk(ox, oy);
			if (chunk == nullptr)
				{
				chunckMap[{ox, oy}] = new CellChunk( x, y, this );
				chunckMap[{ox, oy}]->CreateEmptyChunk(0);
				cout << "Created chunk at " << ox << "," << oy << " pos " << x << "," << y << endl;
				
				}
		}
	}

}

CellChunk* CellTileMap::GetChunk(size_t ox, size_t oy) {
	cout << " requsted chunk at "<< ox << "," << oy << endl;
	return chunckMap[{ox / ChunkSize, oy / ChunkSize}];
}

bool CellChunk::CompareDensityAndBounds(const Cell* cell,
	size_t xTaget, size_t yTarget) {
	return world->CompareDensityAndBounds(cell, M_x + xTaget, M_y + yTarget);
};


int CellChunk::findIfEmptyToSide(size_t x, size_t y, size_t dir, int dispersity)
{
	int i = 1;
	while (i <= dispersity)
	{
		if (!IsEmpty(x + i * dir, y)) return (i - 1) * dir;
		i++;

	}
	return (i - 1) * dir;
}

bool CellChunk::MoveDown(size_t x, size_t y, const Cell* cell)
{
	//cout << " pre down move ";
	bool down = CompareDensityAndBounds(cell, x, y + 1);
	if (down) world->MoveCell(x, y, x, y + 1,this);
	cout << " move down calced " << endl;
	return down;
}
bool CellChunk::MoveUp(size_t x, size_t y, const Cell* cell)
{
	//cout << " pre up move ";
	bool up = CompareDensityAndBounds(cell, x, y - 1);
	if (up) world->MoveCell(x, y, x, y - 1,this);
	//cout << " move up calced " << endl;
	return up;
}
bool CellChunk::MoveUpAndSide(size_t x, size_t y, const Cell* cell)
{

	bool upLeft = CompareDensityAndBounds(cell, x - 1, y - 1);
	bool upRight = CompareDensityAndBounds(cell, x + 1, y - 1);
	if (upLeft && upRight)
	{
		upLeft = Game::GetRandom(2);
		upRight = !upLeft;
	}
	if (upLeft) world->MoveCell(x, y, x - 1, y - 1, this);
	else if (upRight) world->MoveCell(x, y, x + 1, y - 1, this);

	return upLeft || upRight;
}
bool CellChunk::MoveDownAndSide(size_t x, size_t y, const Cell* cell)
{

	bool downLeft = CompareDensityAndBounds(cell, x - 1, y + 1);
	bool downRight = CompareDensityAndBounds(cell, x + 1, y + 1);
	if (downLeft && downRight)
	{
		downLeft = Game::GetRandom(2);
		downRight = !downLeft;
	}
	if (downLeft) world->MoveCell(x, y, x - 1, y + 1, this);
	else if (downRight) world->MoveCell(x, y, x + 1, y + 1, this);

	return downLeft || downRight;
}
bool CellChunk::MoveSide(size_t x, size_t y, const Cell* cell)
{
	int ld = findIfEmptyToSide(x, y, -1, cell->DispersityRate);
	int rd = findIfEmptyToSide(x, y, 1, cell->DispersityRate);

	bool left = (ld == 0) ? false : true;
	bool right = (rd == 0) ? false : true;

	if (left && right)
	{
		int r = Game::GetRandom(1);
		left = r;
		right = !left;
	}
	if (left) world->MoveCell(x, y, x + ld, y, this);
	else if (right) world->MoveCell(x, y, x + rd, y, this);
	return false;
}


void CellChunk::Update()
{
	cout << "CHunk ud " << endl;
	//SetCell(3, 3, Game::GetRandom(5));
	for (size_t y = 0; y < C_height; y++)
		for (size_t x = 0; x < C_width; x++)
		{
			//cout << "pre move dec " << endl;
			const Cell* cell = GetCell(x, y);
			if (static_cast<bool>(cell->Props & static_cast<Uint8>(CellProperties::NONE))) continue;
			if (static_cast<bool>(cell->Props & static_cast<Uint8>(CellProperties::MOVE_DOWN)) && MoveDown(x, y, cell));
			else if (static_cast<bool>(cell->Props & static_cast<Uint8>(CellProperties::MOVE_UP)) && MoveUp(x, y, cell));
			/*else if (static_cast<bool>(cell->Props & static_cast<Uint8>(CellProperties::MOVE_DOWN_SIDE)) && MoveDownAndSide(x, y, cell));
			else if (static_cast<bool>(cell->Props & static_cast<Uint8>(CellProperties::MOVE_UP_SIDE)) && MoveUpAndSide(x, y, cell));
			else if (static_cast<bool>(cell->Props & static_cast<Uint8>(CellProperties::MOVE_SIDE)) && MoveSide(x, y, cell));*/
			//cout << " pist move dec" << endl;
		}
}

void CellTileMap::Update()
{
	currentTileSelected = Game::inputs->GetInputInt();
	cout << "cellTileMap update started " << endl;
	if (Game::inputs->GetInputState("mbl"))
	{
		size_t x, y, px, py, k, dx, dy, d;
		x = static_cast<size_t>(Game::inputs->GetMouseX()) / (Game::drawScale * Game::tileSize);
		y = static_cast<size_t>(Game::inputs->GetMouseY()) / (Game::drawScale * Game::tileSize);
		cout << "(" << x/ChunkSize << "," << y / ChunkSize << ")" << endl;
		

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
		int ox, oy;
		if (GetChunk(x , y ) == nullptr) cout << "null" << endl;
		else cout << " chunk on destination " << endl;
	
		cout << "(" << x << "," << y << ")" << endl;
		for (int i(0u); i < 1  ; i++)
			for (int ii(0u); ii < 1; ii++)
				if (InBounds(x+ii, y+i))
				{
					cout << " placed tile " << currentTileSelected << " at " << x << "," << y << endl;
					ox = (x + ii-1) / Game::tileSize;
					oy = (y + i-1) / Game::tileSize;
					 CellChunk* ptr = GetChunk((x + ii) , (y + i) );
					 if (ptr != nullptr)
					 {
						 ptr->SetCell(x - ptr->M_x, y - ptr->M_y, currentTileSelected);
					 }
					//SetCell(calcIndex(x + ii, y + i), currentTileSelected);
				}		
	}
	
	for (auto const& chunk : chunckMap)
	{
		if (chunk.second != nullptr)
		chunk.second->Update();
	}

	CommitMoves();
	//CommitUpdates();

};

void CellChunk::CommitMoves()
{

	//if (cellMoves.size() <= 0) return;
	//for (size_t i = cellMoves.size() - 1; i > 0; i--)
	//{//Matrix[cellMoves[i].first]->Type != CellType::EMPTY && 
	//	if (!InBounds(cellMoves[i].end) || !HasGreaterDensity(GetCell(cellMoves[i].start), GetCell(cellMoves[i].end)))
	//	{
	//		cellMoves.pop_back();
	//		//i--;
	//	}
	//}
	////cout << "post sort ";
	//sort(cellMoves.begin(), cellMoves.end(),
	//	[](auto& a, auto& b) {return a.end > b.end;  }
	//);

	//size_t srcX, srcY, dstX, dstY;
	//Cell* temp;
	//size_t iprev = 0;
	//size_t dst, src, rand, amount;
	//size_t i = cellMoves.size();
	////cout << "cellMoves " << cellMoves.size() << endl;
	////cout << cellMoves.size() << endl;
	//while (i > 0)
	//{
	//	amount = 0;
	//	if (i - 1 > amount - 1)
	//		while (cellMoves[i - 1].end == cellMoves[i - 2 - amount].end) amount++;

	//	//cout << " calced duped moves " << amount;

	//	rand = Game::GetRandom(amount);
	//	int v = i - 1 + rand;
	//	
	//	src = cellMoves[v].start;
	//	dst = cellMoves[v].end;
	//	
	//	
	//	//cout << " found v, src and dst " << v << " , " << src << " , " << dst;


	//	temp = Matrix[dst];

	//	//cout << " found temp ";
	//	Matrix[dst] = Matrix[src];
	//	Matrix[src] = temp;
	//	//cout << "moved tiles ";

	//	while (amount-- > 0) cellMoves.pop_back();
	//	if (i > 0)
	//		cellMoves.pop_back();

	//	i = cellMoves.size();
	//	//cout << " moves left " << i << endl;
	//}
	////cellMoves.clear();
	//cout << " post cell moves " << endl;
}

void swapCells(Cell*a, Cell*b)
{

}

void CellTileMap::CommitMoves()
{
	cout <<  " Begin commit " << endl;
	if (cellMoves.size() <= 0) return;
	for (size_t i = cellMoves.size() - 1; i > 0; i--)
	{//Matrix[cellMoves[i].first]->Type != CellType::EMPTY && 
		if (!InBounds(cellMoves[i].worldEnd) 
			|| !HasGreaterDensity(cellMoves[i].residingChunk->Matrix[cellMoves[i].localStart], GetCell(cellMoves[i].worldEnd, cellMoves[i].targetChunk)))
		{
			cellMoves.pop_back();
			//i--;
		}
	}
	cout << "post sort ";
	sort(cellMoves.begin(), cellMoves.end(),
		[](auto& a, auto& b) {return a.worldEnd > b.worldEnd;  }
	);

	Cell* temp;
	CellChunk* srcC; 
	CellChunk* dstC;
	size_t iprev = 0;
	size_t rand, amount;
	size_t i = cellMoves.size();
	cout << "cellMoves " << cellMoves.size() << endl;
	//cout << "size " << cellMoves.size() << endl;
	while (i > 0)
	{
		amount = 0;
		if(i-1 > amount-1)
		while (cellMoves[i-1].worldEnd == cellMoves[i - 2 - amount].worldEnd) amount++;

		//cout << " calced duped moves " << amount;

		rand = Game::GetRandom(amount);
		int v = i - 1 + rand;
		cout << " v " << v << endl;
		//swap based on index v
		srcC = cellMoves[v].residingChunk;
		dstC = cellMoves[v].targetChunk;
		
		temp = srcC->Matrix[cellMoves[v].localStart];
		//cout << " temp " << temp << " localStart " << cellMoves[v].localStart << endl;
		//cout << " CK dst " << endl;
		//cout << CalcChunkCoords(dstC, cellMoves[v].worldEnd) << endl;
		srcC->Matrix[cellMoves[v].localStart] = GetCell(cellMoves[v].worldEnd, dstC);
		//cout << "cell under moved" << endl;
		dstC->Matrix[CalcChunkCoords(dstC, cellMoves[v].worldEnd)] = temp;
		
		//cout << " found v, src and dst " << v << " , " << srcC << " , " << dstC;



		//cout << " found temp ";

		//cout << "moved tiles ";

		while(amount-- >0) cellMoves.pop_back(); 
		if(i > 0)
			cellMoves.pop_back();

		i = cellMoves.size();
		//cout << " moves left " << i << endl;
	}
	cellMoves.clear();
	//cout << " post cell moves " << endl;
}

void CellTileMap::CommitUpdates()
{

}

void CellTileMap::Draw()
{
	SDL_Rect src;
	SDL_Rect dest;
	dest.w = dest.h = Game::tileSize * Game::drawScale;
	src.h = src.w = Game::tileSize;
	dest.x = dest.y = src.y = 0; src.x = 0; 
	size_t i = 0; size_t id = 0; size_t ox = 0; size_t oy = 0;

	for (auto const& chunk : chunckMap)
	{
		if (chunk.second == nullptr) continue;
		ox = chunk.second->M_x;
		oy = chunk.second->M_y;

		for (size_t y = 0; y < chunk.second->C_height; y++)
		{
			for (size_t x = 0; x < chunk.second->C_width; x++)
			{

				i = y * chunk.second->C_width + x;
				id = static_cast<int>(chunk.second->Matrix[i]->Type);
				src.x = Game::tileSize * id;
				src.y = chunk.second->Matrix[i]->Variant * Game::tileSize;
				dest.x = (ox + x) * Game::tileSize * Game::drawScale;
				dest.y = (oy + y) * Game::tileSize * Game::drawScale;
				TextureManager::Draw(Game::assets->GetTexture("tile"), src, dest, SDL_FLIP_NONE);
				
			}
		}
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, ox * Game::tileSize * Game::drawScale, oy * Game::tileSize * Game::drawScale, (ox + ChunkSize) * Game::tileSize * Game::drawScale, oy * Game::tileSize * Game::drawScale);
		SDL_RenderDrawLine(Game::renderer, (ox+ChunkSize) * Game::tileSize * Game::drawScale - 1, oy * Game::tileSize * Game::drawScale - 1, (ox + ChunkSize) * Game::tileSize * Game::drawScale - 1,(oy+ChunkSize) * Game::tileSize * Game::drawScale - 1);
		SDL_RenderDrawLine(Game::renderer, (ox + ChunkSize) * Game::tileSize * Game::drawScale - 1, (oy + ChunkSize) * Game::tileSize * Game::drawScale - 1, ox * Game::tileSize * Game::drawScale, (oy+ChunkSize) * Game::tileSize * Game::drawScale - 1);
		SDL_RenderDrawLine(Game::renderer, ox * Game::tileSize * Game::drawScale, oy * Game::tileSize * Game::drawScale, ox * Game::tileSize * Game::drawScale,(oy +ChunkSize) * Game::tileSize * Game::drawScale - 1);
	
	}
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}


