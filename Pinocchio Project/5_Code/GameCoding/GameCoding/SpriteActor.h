#pragma once
#include "Actor.h"

class Sprite;

class SpriteActor : public Actor
{
	using Super = Actor;
public:
	SpriteActor();
	virtual ~SpriteActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetSprite(Sprite* sprite) { _sprite = sprite; }
	Sprite* GetSprite() { return _sprite; }

	void SetTransparent(bool transparent) { _isTransparent = transparent; }

	int offset;

protected:
	Sprite* _sprite = nullptr;
	bool _isTransparent = false;
};

