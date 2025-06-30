#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{

}

void Tilemap::LoadFile(const wstring& path)
{
	wifstream ifs;
	ifs.open(path);

	ifs >> _mapSize.x;
	ifs >> _mapSize.y;

	for (int32 y = 0; y < _mapSize.y; y++)
	{
		wstring line;
		ifs >> line;
		for (int32 x = 0; x < _mapSize.x; x++)
		{
			// ascii¸¦ ¹Þ¾Æ¿È
			_tiles[y][x].value = line[x] - '0';
		}
	}
	ifs.close();
}

void Tilemap::SaveFile(const wstring& path)
{
	wofstream ofs;
	ofs.open(path);

	ofs << _mapSize.x << endl;
	ofs << _mapSize.y << endl;

	for (int32 y = 0; y < _mapSize.y; y++)
	{
		for (int32 x = 0; x < _mapSize.x; x++)
		{
			ofs << _tiles[y][x].value;
		}

		ofs << endl;
	}

	ofs.close();
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
		{
			_tiles[y][x] = Tile{ 0 };
		}
	}
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}

Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
		return nullptr;

	return &_tiles[pos.y][pos.x];
}
