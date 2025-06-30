#pragma once
#include "SpriteActor.h"

class Actor;
class Stage;

class Room : public Actor
{
public:
	Room();
	~Room();

	void Init(RoomNum number);

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	/// <summary>
	/// 배열 value를 바꾸는 swap 함수입니다.
	/// </summary>
	void SwaptoRight();			//왼쪽요소 오른쪽으로 이동
	void SwaptoLeft();			//오른쪽요소 왼쪽으로 이동
	void ClearStage();
	void PassingRightObject(Actor* actor, int32 index);
	void PassingLeftObject(Actor* actor, int32 index);

	bool isRightEnd;

	void DrawRectangle(HDC hdc, int stageNumber, COLORREF penColor);

	int GetPlayerstage();
public:
	RoomNum _roomNumber;  

	Stage* GetStage(int32 index) { return _stages[index]; }
	int32 curSelectNumber = 0;
	bool selectedStage = false;

public:
	vector<Stage*> _stages;
};

