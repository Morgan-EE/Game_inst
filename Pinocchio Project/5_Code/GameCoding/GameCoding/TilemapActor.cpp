#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"

TilemapActor::TilemapActor()
{

}

TilemapActor::~TilemapActor()
{

}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();
	TilePicking();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr)
		return;

	if (_showDebug == false)
		return;

	const Vec2Int mapSize = _tilemap->GetMapSize();
	const int32 tileSize = _tilemap->GetTileSize();

	vector<vector<Tile>>& tiles = _tilemap->GetTiles();

	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"TileO");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// 컬링: 보여야 할 애들만 보여주기
	int32 leftX = ((int32)cameraPos.x - GWinSizeX / 2);
	int32 leftY = ((int32)cameraPos.y - GWinSizeY / 2);
	int32 rightX = ((int32)cameraPos.x + GWinSizeX / 2);
	int32 rightY = ((int32)cameraPos.y + GWinSizeY / 2);

	int32 startX = static_cast<int32>((leftX - _pos.x) / static_cast<int32>(TILE_SIZEX));
	int32 startY = static_cast<int32>((leftY - _pos.y) / static_cast<int32>(TILE_SIZEY));
	int32 endX = static_cast<int32>((rightX - _pos.x) / static_cast<int32>(TILE_SIZEX));
	int32 endY = static_cast<int32>((rightY - _pos.y) / static_cast<int32>(TILE_SIZEY));

	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x <= endX; x++)
		{
			if (x < 0 || x >= mapSize.x)
				continue;
			if (y < 0 || y >= mapSize.y)
				continue;

			switch (tiles[y][x].value)
			{
				//empty
			case 0:
			{
				::TransparentBlt(hdc,
					static_cast<int32>(_pos.x + x * TILE_SIZEX - ((cameraPos.x) - GWinSizeX / 2)),
					static_cast<int32>(_pos.y + y * TILE_SIZEY - ((cameraPos.y) - GWinSizeY / 2)),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent()
				);
			}
				break;

				//wall
			case 1:
			{
				::TransparentBlt(hdc,
					static_cast<int32>(_pos.x + x * TILE_SIZEX - ((cameraPos.x) - GWinSizeX / 2)),
					static_cast<int32>(_pos.y + y * TILE_SIZEY - ((cameraPos.y) - GWinSizeY / 2)),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent()
				);
			}
				break;
			}
		}
	}
}

void TilemapActor::TilePicking()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

		// 왼쪽 상단 (스크린 기준, 인게임x)
		int32 screenX = static_cast<int32>(cameraPos.x - GWinSizeX / 2);
		int32 screenY = static_cast<int32>(cameraPos.y - GWinSizeY / 2);

		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({ x, y });
		if (tile)
			tile->value = 1;
	}
}
