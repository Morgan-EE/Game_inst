#pragma once
#include "SpriteActor.h"

class Sprite;
class Room;
class Player;
class Scene;

class Hall : public SpriteActor
{
	using Super = SpriteActor;
public:
	Hall();
	~Hall();
	
	void Init();

	bool isRight;
	virtual void Tick() override;
	virtual void Render(HDC hdc);

	Sprite* _spriteHall;
	
	void AddActorStage(Actor* actor) { _actors.push_back(actor); }
	Actor* GetActorStage(int32 index) { return _actors[index]; }

public:
	vector<Actor*> _actors;
	vector<Sprite*> _backgroundSprites;

private:
	Room* _room1;
};

