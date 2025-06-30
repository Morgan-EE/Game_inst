#include "pch.h"
#include "Room.h"
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
#include "Scene.h"
#include "DevScene.h"
#include "GameScene.h"
#include "SoundManager.h"

#include "CameraComponent.h"
#include "SceneManager.h"
#include "Stage.h"

Room::Room()
{

}

Room::~Room()
{

}

void Room::Init(RoomNum number)
{
	_roomNumber = number; // Room을 구별하는 변수(enum)

	if (_roomNumber == RoomNum::restRoom)
	{
		// 스테이지 객체를 생성할 때 텍스쳐 이름과 배경 경로를 전달해서 불러온다
		// 스테이지를 for문으로 돌면서 스프라이트 액터 객체를 이용해서 정보를 넣음

		// Morgan : Stage* 변경하기..  // C >> Tab.
		Stage* Stage1 = new Stage(L"Stage1", L"Sprite\\Map\\restRoom\\1.bmp");
		Stage* Stage2 = new Stage(L"Stage2", L"Sprite\\Map\\restRoom\\2.bmp");
		Stage* Stage3 = new Stage(L"Stage3", L"Sprite\\Map\\restRoom\\3.bmp");
		Stage* Stage4 = new Stage(L"Stage4", L"Sprite\\Map\\restRoom\\4.bmp");
		Stage* Stage5 = new Stage(L"Stage5", L"Sprite\\Map\\restRoom\\5.bmp");

		Stage* newStage[] = { Stage1 ,Stage2, Stage3, Stage4, Stage5 };
		for (int32 i = 0; i < 5; i++)
		{
			newStage[i]->index = i;

			newStage[i]->SetLayer(LAYER_BACKGROUND);
			newStage[i]->myRoom = this;

			_stages.push_back(newStage[i]);
		}
		newStage[0]->SetStageID(StageID::Stage1);
		newStage[1]->SetStageID(StageID::Stage2);
		newStage[2]->SetStageID(StageID::Stage3);
		newStage[3]->SetStageID(StageID::Stage4);
		newStage[4]->SetStageID(StageID::Stage5);
	}
	else if (_roomNumber == RoomNum::wareHouse)
	{
		// 스테이지 객체를 생성할 때 텍스쳐 이름과 배경 경로를 전달해서 불러온다
		// 스테이지를 for문으로 돌면서 스프라이트 액터 객체를 이용해서 정보를 넣음

		// Morgan : Stage* 변경하기..  // C >> Tab.
		Stage* Stage1 = new Stage(L"WareStage1", L"Sprite\\Map\\wareHouse\\wareHouse1.bmp");
		Stage* Stage2 = new Stage(L"WareStage2", L"Sprite\\Map\\wareHouse\\wareHouse2.bmp");
		Stage* Stage3 = new Stage(L"WareStage3", L"Sprite\\Map\\wareHouse\\wareHouse3.bmp");
		Stage* Stage4 = new Stage(L"WareStage4", L"Sprite\\Map\\wareHouse\\wareHouse4.bmp");
		Stage* Stage5 = new Stage(L"WareStage5", L"Sprite\\Map\\wareHouse\\wareHouse5.bmp");

		Stage* newStage[] = { Stage1 ,Stage2, Stage3, Stage4, Stage5 };
		for (int32 i = 0; i < 5; i++)
		{
			newStage[i]->index = i;

			newStage[i]->SetLayer(LAYER_BACKGROUND);
			newStage[i]->myRoom = this;

			_stages.push_back(newStage[i]);
		}
	}
	else if (_roomNumber == RoomNum::kitchen)
	{
		// 스테이지 객체를 생성할 때 텍스쳐 이름과 배경 경로를 전달해서 불러온다
		// 스테이지를 for문으로 돌면서 스프라이트 액터 객체를 이용해서 정보를 넣음

		// Morgan : Stage* 변경하기..  // C >> Tab.
		Stage* Stage1 = new Stage(L"KitchenStage1", L"Sprite\\Map\\kitchen\\kitchen1.bmp");
		Stage* Stage2 = new Stage(L"KitchenStage2", L"Sprite\\Map\\kitchen\\kitchen2.bmp");
		Stage* Stage3 = new Stage(L"KitchenStage3", L"Sprite\\Map\\kitchen\\kitchen3.bmp");
		Stage* Stage4 = new Stage(L"KitchenStage4", L"Sprite\\Map\\kitchen\\kitchen4.bmp");
		Stage* Stage5 = new Stage(L"KitchenStage5", L"Sprite\\Map\\kitchen\\kitchen5.bmp");

		Stage* newStage[] = { Stage1 ,Stage2, Stage3, Stage4, Stage5 };
		for (int32 i = 0; i < 5; i++)
		{
			newStage[i]->index = i;

			newStage[i]->SetLayer(LAYER_BACKGROUND);
			newStage[i]->myRoom = this;

			_stages.push_back(newStage[i]);
		}
	}
	else if (_roomNumber == RoomNum::bedRoom)
	{
		// 스테이지 객체를 생성할 때 텍스쳐 이름과 배경 경로를 전달해서 불러온다
		// 스테이지를 for문으로 돌면서 스프라이트 액터 객체를 이용해서 정보를 넣음

		// Morgan : Stage* 변경하기..  // C >> Tab.
		Stage* Stage1 = new Stage(L"BedRoomStage1", L"Sprite\\Map\\bedRoom\\bedRoomDefault.bmp");
		Stage* Stage2 = new Stage(L"BedRoomStage2", L"Sprite\\Map\\bedRoom\\bedRoom2.bmp");
		Stage* Stage3 = new Stage(L"BedRoomStage3", L"Sprite\\Map\\bedRoom\\bedRoomDefault.bmp");
		Stage* Stage4 = new Stage(L"BedRoomStage4", L"Sprite\\Map\\bedRoom\\bedRoom4.bmp");
		Stage* Stage5 = new Stage(L"BedRoomStage5", L"Sprite\\Map\\bedRoom\\bedRoom5.bmp");

		Stage* newStage[] = { Stage1 ,Stage2, Stage3, Stage4, Stage5 };
		for (int32 i = 0; i < 5; i++)
		{
			newStage[i]->index = i;

			newStage[i]->SetLayer(LAYER_BACKGROUND);
			newStage[i]->myRoom = this;

			_stages.push_back(newStage[i]);
		}
	}	else if (_roomNumber == RoomNum::workRoom)
	{
		// 스테이지 객체를 생성할 때 텍스쳐 이름과 배경 경로를 전달해서 불러온다
		// 스테이지를 for문으로 돌면서 스프라이트 액터 객체를 이용해서 정보를 넣음

		// Morgan : Stage* 변경하기..  // C >> Tab.
		Stage* Stage1 = new Stage(L"WorkRoomStage1", L"Sprite\\Map\\workRoom\\workRoom1.bmp");
		Stage* Stage2 = new Stage(L"WorkRoomStage2", L"Sprite\\Map\\workRoom\\workRoom2.bmp");
		Stage* Stage3 = new Stage(L"WorkRoomStage3", L"Sprite\\Map\\workRoom\\workRoom3.bmp");
		Stage* Stage4 = new Stage(L"WorkRoomStage4", L"Sprite\\Map\\workRoom\\workRoom4.bmp");
		Stage* Stage5 = new Stage(L"WorkRoomStage5", L"Sprite\\Map\\workRoom\\workRoom5.bmp");

		Stage* newStage[] = { Stage1 ,Stage2, Stage3, Stage4, Stage5 };
		for (int32 i = 0; i < 5; i++)
		{
			newStage[i]->index = i;

			newStage[i]->SetLayer(LAYER_BACKGROUND);
			newStage[i]->myRoom = this;

			_stages.push_back(newStage[i]);
		}
	}
}

void Room::BeginPlay()
{

}

void Room::Tick()
{
	bool* isTabToggle = &(((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->isTabToggle);
	// 탭 토글키로 블릿 전환 
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Tab))
	{
		selectedStage = false;
		if (_roomNumber == RoomNum::workRoom)
		{
			curSelectNumber = 4;
		}
		else
		{
			curSelectNumber = 0;
		}

		if (!(*isTabToggle))
		{
			const Vec2Int size = Vec2Int{ 0, 1080 };

			// camera영역 설정
			GET_SINGLE(SceneManager)->SetBackgroundSize(size);

		}
		else
		{
			const Vec2Int size = Vec2Int{ 2880, 1080 };

			// camera영역 설정

			GameScene* gameScene = dynamic_cast<GameScene*>(GetMyScene());
			if (gameScene != nullptr)
			{
				CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(gameScene->_player->_components[5]);
				if (cameraComponent != nullptr)
				{
					cameraComponent->SetCameraPosition(gameScene->_player->GetPos());
				}
			}

			GET_SINGLE(SceneManager)->SetBackgroundSize(size);


		}
		*isTabToggle = !(*isTabToggle);
		//false -> true; 일때 E키 입력으로 Scene Swap을 활성화할 예정.
	}

	if (*isTabToggle)
	{
		if (_roomNumber == RoomNum::workRoom)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D) && curSelectNumber <= 3)
			{
				if (selectedStage)
				{
					SwaptoRight();
				}
				else
				{
					curSelectNumber++;
				}
			}
		}
		else
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D) && curSelectNumber <= 2)
			{
				if (selectedStage)
				{
					SwaptoRight();
				}
				else
				{
					curSelectNumber++;
				}
			}
		}

		if (_roomNumber == RoomNum::workRoom)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A) && curSelectNumber >= 2)
			{
				if (selectedStage)
				{
					SwaptoLeft();
				}
				else
				{
					curSelectNumber--;
				}
			}
		}
		else
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A) && curSelectNumber >= 1)
			{
				if (selectedStage)
				{
					SwaptoLeft();
				}
				else
				{
					curSelectNumber--;
				}
			}
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		if (GetPlayerstage() != curSelectNumber)
		{
			selectedStage = !selectedStage;
		}
	}
}

void Room::Render(HDC hdc)
{
	if (((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->isTabToggle)
	{
		COLORREF color;
		if (selectedStage)
		{
			color = RGB(0, 255, 0);
		}
		else
		{
			color = RGB(255, 0, 0);
		}
		DrawRectangle(hdc, curSelectNumber, color);
	}
}

void Room::SwaptoRight()
{
	if (_roomNumber != RoomNum::workRoom)
	{
		if (curSelectNumber == 3)
		{
			return;
		}

		int32 nextStage = curSelectNumber + 1;
		if (GetPlayerstage() == nextStage)
		{
			nextStage++;
		}

		if (nextStage == 4)
		{
			return;
		}

		if (_stages[curSelectNumber]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber + 1)
			{
				_stages[curSelectNumber]->isRightChanged += 1;
			}
			else
			{
				_stages[curSelectNumber]->isRightChanged += 2;
			}
		}
		if (_stages[nextStage]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber + 1)
			{
				_stages[nextStage]->isLeftChanged += 1;
			}
			else
			{
				_stages[nextStage]->isLeftChanged += 2;
			}
		}

		Stage* stage = _stages[curSelectNumber];
		_stages[curSelectNumber] = _stages[nextStage];
		_stages[nextStage] = stage;

		int temp = _stages[curSelectNumber]->index;
		_stages[curSelectNumber]->index = _stages[nextStage]->index;
		_stages[nextStage]->index = temp;

		curSelectNumber = nextStage;
	}
	else
	{
		if (curSelectNumber == 4)
		{
			return;
		}

		int32 nextStage = curSelectNumber + 1;
		if (GetPlayerstage() == nextStage)
		{
			nextStage++;
		}

		if (nextStage == 5)
		{
			return;
		}

		if (_stages[curSelectNumber]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber + 1)
			{
				_stages[curSelectNumber]->isRightChanged += 1;
			}
			else
			{
				_stages[curSelectNumber]->isRightChanged += 2;
			}
		}
		if (_stages[nextStage]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber + 1)
			{
				_stages[nextStage]->isLeftChanged += 1;
			}
			else
			{
				_stages[nextStage]->isLeftChanged += 2;
			}
		}

		Stage* stage = _stages[curSelectNumber];
		_stages[curSelectNumber] = _stages[nextStage];
		_stages[nextStage] = stage;

		int temp = _stages[curSelectNumber]->index;
		_stages[curSelectNumber]->index = _stages[nextStage]->index;
		_stages[nextStage]->index = temp;

		curSelectNumber = nextStage;
	}
}

void Room::SwaptoLeft()
{
	if (_roomNumber != RoomNum::workRoom)
	{
		if (curSelectNumber == 0)
		{
			return;
		}

		int32 nextStage = curSelectNumber - 1;
		if (GetPlayerstage() == nextStage)
		{
			nextStage--;
		}

		if (nextStage == -1)
		{
			return;
		}

		if (_stages[curSelectNumber]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber - 1)
			{
				_stages[curSelectNumber]->isLeftChanged += 1;
			}
			else
			{
				_stages[curSelectNumber]->isLeftChanged += 2;
			}
		}
		if (_stages[nextStage]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber - 1)
			{
				_stages[nextStage]->isRightChanged += 1;
			}
			else
			{
				_stages[nextStage]->isRightChanged += 2;
			}
		}

		Stage* stage = _stages[curSelectNumber];
		_stages[curSelectNumber] = _stages[nextStage];
		_stages[nextStage] = stage;

		int temp = _stages[curSelectNumber]->index;
		_stages[curSelectNumber]->index = _stages[nextStage]->index;
		_stages[nextStage]->index = temp;

		curSelectNumber = nextStage;
	}
	else
	{
		if (curSelectNumber == 1)
		{
			return;
		}

		int32 nextStage = curSelectNumber - 1;
		if (GetPlayerstage() == nextStage)
		{
			nextStage--;
		}

		if (nextStage == 0)
		{
			return;
		}

		if (_stages[curSelectNumber]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber - 1)
			{
				_stages[curSelectNumber]->isLeftChanged += 1;
			}
			else
			{
				_stages[curSelectNumber]->isLeftChanged += 2;
			}
		}
		if (_stages[nextStage]->GetObjectActorSize() != 0)
		{
			if (nextStage == curSelectNumber - 1)
			{
				_stages[nextStage]->isRightChanged += 1;
			}
			else
			{
				_stages[nextStage]->isRightChanged += 2;
			}
		}

		Stage* stage = _stages[curSelectNumber];
		_stages[curSelectNumber] = _stages[nextStage];
		_stages[nextStage] = stage;

		int temp = _stages[curSelectNumber]->index;
		_stages[curSelectNumber]->index = _stages[nextStage]->index;
		_stages[nextStage]->index = temp;

		curSelectNumber = nextStage;
	}
}

void Room::DrawRectangle(HDC hdc, int stageNumber, COLORREF penColor)
{
	// 펜 생성 및 설정
	HPEN hPen = CreatePen(PS_SOLID, 3, penColor);
	HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	// 배경 모드를 투명으로 설정
	SetBkMode(hdc, TRANSPARENT);

	// 사각형 내부를 그리지 않고 외곽선만 그리기
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, stageNumber * 384, 300, (stageNumber + 1) * 384, 540);

	// 사용한 펜 해제
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

int Room::GetPlayerstage()
{
	Vec2 playerPos = ((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->_player->GetPos();

	int32 offset = 960;

	if (playerPos.x > 0 && playerPos.x < offset)
		return 0;
	else if (playerPos.x > offset * 1 && playerPos.x < offset * 2)
		return 1;
	else if (playerPos.x > offset * 2 && playerPos.x < offset * 3)
		return 2;
	else if (playerPos.x > offset * 3 && playerPos.x < offset * 4)
		return 3;
	else if (playerPos.x > offset * 4 && playerPos.x < offset * 5)
		return 4;
}

void Room::ClearStage()
{
	_stages.clear();
}

/// <summary>
/// 스테이지 가로 크기(960)보다 오른쪽으로 넘어가면
/// 스테이지 백터 배열에서 오른쪽에 있는 스테이지 객체에 오브젝트를 전달한다.
/// </summary>
/// <param name="index"></param>
void Room::PassingRightObject(Actor* actor, int32 index)
{
	_stages[index]->AddObjectActor(actor);
	if (actor == ((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->_player)
	{
		_stages[index]->isVisited = true;
		_stages[index]->HasPlayer = true;
		_stages[index - 1]->HasPlayer = false;
	}
}
/// <summary>
/// 스테이지 가로 시작점(0)보다 왼쪽으로 넘어가면
/// 스테이지 백터 배열에서 왼쪽에 있는 스테이지 객체에 오브젝트를 전달한다.
/// </summary>
/// <param name="index"></param>
void Room::PassingLeftObject(Actor* actor, int32 index)
{
	_stages[index]->AddObjectActor(actor);
	if (actor == ((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->_player)
	{
		_stages[index]->isVisited = true;
		_stages[index]->HasPlayer = true;
		_stages[index + 1]->HasPlayer = false;
	}
}
