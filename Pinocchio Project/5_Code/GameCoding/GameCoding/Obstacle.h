#pragma once
#include "SpriteActor.h"

enum OBSTACLE_POS_INFO
{
	OPI_LEFT,
	OPI_RIGHT,
	OPI_TOP,


	OPI_COUNT,
};

enum class ObstacleLevel
{
	Level1,
	Level2,
};

enum class ObstacleState
{
	Movable,
	Unmovable,
};

class Obstacle : public SpriteActor
{
	using Super = SpriteActor;
public:
	Obstacle();
	virtual ~Obstacle() override;
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;
	void OnComponentOverlap(Collider* collider, Collider* other) override;

public:
	//void SetPosInfo(OBSTACLE_POS_INFO posInfo, Vec2 pos) { _posInfo[posInfo] = pos; }
	Vec2 GetPosInfo(OBSTACLE_POS_INFO posInfo);
	
	void SetObstacleState(ObstacleState state) { _state = state; }
	ObstacleState GetObstacleState() { return _state; }

	void SetObstacleLevel(ObstacleLevel level) { _level = level; }
	ObstacleLevel GetObstacleLevel () { return _level; }
	/// <summary>
	/// ���� �Ǵ� �����ʿ� ���ڰ� ���� �ϴ����� ����. -> 2�� ������ ��� ���� �Ǵ� ������ �Ʒ��� ��ġ�� ���� �� ����.
	/// </summary>
	void ExistLeft() { _isExistLeft = true; }
	void ExistRight() { _isExistRight = true; }
	bool IsExistLeft() { return _isExistLeft;}
	bool IsExistRight() { return _isExistRight; }

private:
	Vec2 _posInfo[OPI_COUNT];

	// ���ڿ��� �Ÿ�
	float _distanceSide = 220.f;
	float _distanceTop = 130.f;
	ObstacleLevel _level = ObstacleLevel::Level1;
	ObstacleState _state = ObstacleState::Movable;

	bool _isExistLeft = false;
	bool _isExistRight = false;

};

