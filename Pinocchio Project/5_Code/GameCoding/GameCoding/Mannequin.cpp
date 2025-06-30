#include "pch.h"
#include "Mannequin.h"
#include "Player.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameScene.h"
Mannequin::Mannequin()
{

}

Mannequin::~Mannequin()
{
	_player = nullptr;
}

void Mannequin::BeginPlay()
{
	Super::BeginPlay();

}

void Mannequin::Tick()
{
	Super::Tick();
	if ((((GameScene*)GET_SINGLE(SceneManager)->GetCurrentScene())->isTabToggle))
	{
		return;
	}

	if (_isActive == false)
	{
		return;
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_player->GetPos().x > _pos.x)
	{
		if (_player->GetPlayerDir() == PD_RIGHT)
		{
			// �����̱�
			_pos.x += _speed * deltaTime;
		}
		else
		{
			// ���߱�
		}
	}
	else
	{
		if (_player->GetPlayerDir() == PD_LEFT)
		{
			// �����̱�
			_pos.x -= _speed * deltaTime;
		}
		else
		{
			// ���߱�
		}
	}
	//if(_player->GetPlayerDir() == PD_LEFT && )

}

void Mannequin::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Mannequin::SetActive(Player* player)
{
	_isActive = true;
	_player = player;
}
