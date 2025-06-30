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
	/// �迭 value�� �ٲٴ� swap �Լ��Դϴ�.
	/// </summary>
	void SwaptoRight();			//���ʿ�� ���������� �̵�
	void SwaptoLeft();			//�����ʿ�� �������� �̵�
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

