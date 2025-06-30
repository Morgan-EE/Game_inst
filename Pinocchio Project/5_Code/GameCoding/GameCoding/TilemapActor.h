#pragma once
#include "Actor.h"

class Tilemap;
class TilemapActor : public Actor
{
	using Super = Actor;

public:
	TilemapActor();
	virtual ~TilemapActor();

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	// 마우스 클릭으로 타일의 타입을 바꿈
	void TilePicking();

	void SetTilemap(Tilemap* tilemap) { _tilemap = tilemap; }
	Tilemap* GetTilemap() { return _tilemap; }

	void SetShowDebug(bool showDebug) { _showDebug = showDebug; }
protected:
	Tilemap* _tilemap = nullptr;
	bool _showDebug = false;
};

