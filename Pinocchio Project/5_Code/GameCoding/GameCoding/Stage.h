#pragma once
#include "Room.h"
class Sprite;
class SpriteActor;

class Stage : public SpriteActor
{
public:
	Stage(wstring name, wstring path);
	Stage();
	~Stage();

	Room* myRoom;

	virtual void Render(HDC hdc);
	virtual void Tick();

	int32 index = 0;
	vector<Actor*> _objectActor;

	void SetStageID(StageID id) { _stageId = id; }
	StageID GetStageID() { return _stageId; }

	void AddObjectActor(Actor* actor) { _objectActor.push_back(actor); }
	int GetObjectActorSize() { return _objectActor.size(); }

	int isRightChanged = 0;
	int isLeftChanged = 0;

	bool HasPlayer = false;
	bool isVisited = false;
private:
	StageID _stageId = StageID::Stage1;
};