#include "pch.h"
#include "Stage.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "Flipbook.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "UI.h"
#include "Button.h"
#include "TestPanel.h"
#include "Tilemap.h"
#include "TilemapActor.h"
#include "InputManager.h"

#include "SoundManager.h"
#include "Room.h"
#include "Scene.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "DevScene.h"

#include "GameScene.h"

Stage::Stage(wstring name, wstring path)//path
{
	// 스테이지의 텍스쳐를 _sprite에 저장
	GET_SINGLE(ResourceManager)->LoadTexture(name, path);
	GET_SINGLE(ResourceManager)->CreateSprite(name, GET_SINGLE(ResourceManager)->GetTexture(name));
	_sprite = GET_SINGLE(ResourceManager)->GetSprite(name);
}

Stage::Stage()
{

}

Stage::~Stage()
{

}

void Stage::Render(HDC hdc)
{
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int size = _sprite->GetSize();
	SetPos(Vec2(static_cast<float>(size.x * index), static_cast<float>(size.y * 0)));
	
	//_objectActor[index]->SetPos(Vec2(static_cast<float>(100 * index), static_cast<float>(0)));

	//GET_SINGLE(SceneManager)->GetCurrentScene()->AddActor(_objectActor[index]);
	
	bool isTabToggle = ((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->isTabToggle;

	if (isTabToggle) //Tab이 눌리면 Toggle and switch bool true/false
	{
		::StretchBlt(hdc,
			(int32)_pos.x * 0.4,
			300,
			size.x * ((double)2 / 5),	// 여기 부분을 조정하면 됨
			size.y * ((double)2 / 5),	// 여기 부분을 조정하면 됨
			_sprite->GetDC(),
			_sprite->GetPos().x,
			_sprite->GetPos().y,
			_sprite->GetSize().x,
			_sprite->GetSize().y,
			SRCCOPY);
	}
	else
	{
		::BitBlt(hdc,
			// 			(int32)_pos.x - size.x / 2 - ((int32)(cameraPos.x) - GWinSizeX / 2),
			// 			(int32)_pos.y - size.y * 1.2 - ((int32)(cameraPos.y) - GWinSizeX / 2),
			480 + (int32)_pos.x - size.x / 2 - ((int32)(cameraPos.x) - GWinSizeX / 2),
			(int32)_pos.y - size.y / 2 - ((int32)(cameraPos.y) - GWinSizeY / 2),
			size.x,
			size.y,
			_sprite->GetDC(), 
			_sprite->GetPos().x,
			_sprite->GetPos().y,
			SRCCOPY);
	}
}

void Stage::Tick()
{
	int offset = 960;

	// 예외처리
	for (int i = 0; i < _objectActor.size(); i++)
	{
		Player* player = ((GameScene*)GET_SINGLE(SceneManager)->GetCurrentScene())->_player;

		if (_objectActor[i] != player)
		{
			if (_objectActor[i]->GetPos().x < 100)
			{
				_objectActor[i]->SetPos(Vec2(100, _objectActor[i]->GetPos().y));
			}
			if (_objectActor[i]->GetPos().x >= 4700)
			{
				_objectActor[i]->SetPos(Vec2(4700, _objectActor[i]->GetPos().y));
			}
		}
	}

	for (int i = 0; i < _objectActor.size(); i++)
	{
		Vec2 pos = _objectActor[i]->GetPos();

		if (isLeftChanged != 0)
		{
			pos.x = pos.x - (((index + isLeftChanged) * offset));
		}
		else if (isRightChanged != 0)
		{
			pos.x = pos.x - (((index - isRightChanged) * offset));
		}
		else
		{
			pos.x -= (index)*offset;
		}

		_objectActor[i]->SetPos(Vec2(static_cast<float>(pos.x + index * offset), pos.y));
	}

	isLeftChanged = 0;
	isRightChanged = 0;

	for (int i = 0; i < _objectActor.size(); i++)
	{
		if (_objectActor[i]->GetPos().x < index * 960)
		{
			myRoom->PassingLeftObject(_objectActor[i], index - 1);
			_objectActor.erase(_objectActor.begin() + i);
		}
		else if (_objectActor[i]->GetPos().x > (index + 1) * 960)
		{
			myRoom->PassingRightObject(_objectActor[i], index + 1);
			_objectActor.erase(_objectActor.begin() + i);
		}
	}
}
