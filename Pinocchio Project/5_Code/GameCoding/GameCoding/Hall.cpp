#include "pch.h"
#include "Hall.h"
#include "Room.h"

#include "Scene.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "Flipbook.h"
#include "SphereCollider.h"
#include "UI.h"
#include "Button.h"
#include "TestPanel.h"
#include "Tilemap.h"
#include "stage.h"
#include "TilemapActor.h"
#include "Room.h"

#include "Item.h"
#include "Key.h"
#include "Door.h"
#include "Closet.h"
#include "Trap.h"
#include "Obstacle.h"

#include "CameraComponent.h"
#include "BoxCollider.h"

#include "GameScene.h"

// Manager
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"

Hall::Hall()
{
	
}

Hall::~Hall()
{

}

void Hall::Init()
{

}

void Hall::Tick()
{

	//Obstacle* obstacles = (Obstacle*)(_room1->_stages[0]->_objectActor[0]);
	//obstacles->SetPos({ ::clamp(obstacles->GetPos().x, 0.f, 960.f), 0.f});
	Super::Tick();

	for (Actor* actor : _actors)
	{
		actor->Tick();
	}
}

void Hall::Render(HDC hdc)
{
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int size = _backgroundSprites[0]->GetSize();

	for (int i = 0; i < _backgroundSprites.size(); i++)
	{
		::BitBlt(hdc,
			480 + (int32)_pos.x + (i * 960) - size.x / 2 - ((int32)(cameraPos.x) - GWinSizeX / 2),
			(int32)_pos.y - size.y / 2 - ((int32)(cameraPos.y) - GWinSizeY / 2),
			size.x,
			size.y,
			_backgroundSprites[i]->GetDC(),
			_backgroundSprites[i]->GetPos().x,
			_backgroundSprites[i]->GetPos().y,
			SRCCOPY);
	}
	
}
	//wstring str2 = std::format(L"pos {0}, {1}", (float)cameraPos.x, cameraPos.y);
	//::TextOut(hdc, 10, 500, str2.c_str(), static_cast<int32>(str2.size()));

