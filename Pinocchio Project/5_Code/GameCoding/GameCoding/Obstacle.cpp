#include "pch.h"
#include "Obstacle.h"
#include "BoxCollider.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{

}

void Obstacle::BeginPlay()
{
	Super::BeginPlay();
}

void Obstacle::Tick()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::O))
	{
		GET_SINGLE(SceneManager)->GetCurrentScene()->SaveData("boxCollider1X", std::to_string(_pos.x));
		GET_SINGLE(SceneManager)->GetCurrentScene()->SaveData();
	}
	Super::Tick();
}

void Obstacle::Render(HDC hdc)
{
	Super::Render(hdc);

	wstring str2 = std::format(L"pos {0}, {1}", (float)_pos.x, _pos.y);
	::TextOut(hdc, 10, 500 + 1 * 20, str2.c_str(), static_cast<int32>(str2.size()));
}

void Obstacle::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	// 만일을 대비해 다른 타입일경우 리턴
	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayerType() == CLT_OBSTACLES)
	{
		SetObstacleState(ObstacleState::Unmovable);
		Obstacle* obs = dynamic_cast<Obstacle*>(b2->GetOwner());
		if (obs->GetObstacleLevel() == ObstacleLevel::Level2)
		{
			if (b1->GetOwner()->GetPos().x < obs->GetPos().x)
			{
				obs->ExistLeft();
			}
			else
			{
				obs->ExistRight();
			}
		}
	}
}

void Obstacle::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

void Obstacle::OnComponentOverlap(Collider* collider, Collider* other)
{
}

Vec2 Obstacle::GetPosInfo(OBSTACLE_POS_INFO posInfo)
{
	
	switch (posInfo)
	{
	case OPI_LEFT:
	{
		if (GetObstacleLevel() == ObstacleLevel::Level1)
		{
			return { GetPos().x - _distanceSide, GetPos().y - 35 };
		}
		else
		{
			// 왼쪽으로 한 층만 내려갈때
			if (IsExistLeft())
			{
				return { GetPos().x - _distanceSide, GetPos().y - 35 };
			}
			else // 왼쪽으로 두 개의 층을 내려갈때
			{
				return { GetPos().x - _distanceSide, GetPos().y + _distanceTop - 35 };
			}
		}
	}
	case OPI_RIGHT:
	{
		if (GetObstacleLevel() == ObstacleLevel::Level1)
		{
			return { GetPos().x + _distanceSide, GetPos().y - 35 };
		}
		else
		{
			if (IsExistRight())
			{
				return { GetPos().x + _distanceSide, GetPos().y - 35 };
			}
			else
			{
				return { GetPos().x + _distanceSide, GetPos().y + _distanceTop - 35 };
			}
		}
	}
	case OPI_TOP:
	{
		return { GetPos().x, GetPos().y - _distanceTop };
	}
	default:
		return { 0,0 };
	}
}



