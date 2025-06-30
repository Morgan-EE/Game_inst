#include "pch.h"
#include "GameScene.h"

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
#include "TilemapActor.h"

#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "UIManager.h"

#include "Item.h"
#include "Key.h"
#include "Door.h"
#include "Closet.h"
#include "Trap.h"
#include "Obstacle.h"

#include "Pinocchio.h"
#include "Light.h"
#include "Cheese.h"
#include "Mannequin.h"
#include "Interactionable.h"
#include "Doll.h"
#include "DollCheck.h"
#include "UISprite.h"
#include "Hall.h"
#include "Room.h"
#include "Stage.h"

#include "TutorialPanel.h"

// Component
#include "CameraComponent.h"
#include "BoxCollider.h"
#include "Collider.h"
#include "StrongBox.h"

#include <locale>
#include <codecvt>
GameScene::GameScene()
{
	_playerText.insert(make_pair<string, wstring>("Player_Start", L"아으 머리야.. 제대로 온건가? 여긴 왜이렇게 어둡지? 일단 주변을 둘러볼까?"));
	_playerText.insert(make_pair<string, wstring>("RestRoom_NoKey", L"여긴 잠겨있어…"));
	_playerText.insert(make_pair<string, wstring>("RestRoom_Key", L"흠, 이 열쇠가 딱 맞을 것 같은데… 오, 열렸어! 이제 안에 무슨 비밀이 숨어있는지 알 수 있겠어!"));
	_playerText.insert(make_pair<string, wstring>("WareRoom_NoKey", L"여긴 잠겨있어…"));
	_playerText.insert(make_pair<string, wstring>("WareRoom_Key", L"(열쇠를 사용하여 문이 열립니다.)"));
	_playerText.insert(make_pair<string, wstring>("Kitchen_NoKey", L"여긴 잠겨있어…"));
	_playerText.insert(make_pair<string, wstring>("Kitchen_Key", L"(열쇠를 사용하여 문이 열립니다.)"));
	_playerText.insert(make_pair<string, wstring>("LittlePino1", L"(작은 피노키오) 안녕 ?"));
	_playerText.insert(make_pair<string, wstring>("LittlePino2", L"(알리도로) 으와, 뭐야 ? 너, 말할 수 있어 ?"));
	_playerText.insert(make_pair<string, wstring>("LittlePino3", L"(작은 피노키오) 그럼!나는 이곳의 가이드라고 할 수 있어."));
	_playerText.insert(make_pair<string, wstring>("LittlePino4", L"(알리도로) 정말이야 ? 그럼 너... 여기서 무슨 일이 일어나고 있는지 알고 있어 ?"));
	_playerText.insert(make_pair<string, wstring>("LittlePino5", L"(작은 피노키오) 그럼!하지만 모든 것을 말해주진 않을거야. 너 자신이 탐험하고 배워나가야 하니까."));
	_playerText.insert(make_pair<string, wstring>("LittlePino6", L"(알리도로) 알았어. 그럼 도와줘.어디로 가야 할지 모르겠어 여기 복도에 있는 문들..아무것도 열리지가 않아"));
	_playerText.insert(make_pair<string, wstring>("LittlePino7", L"(코가 길어진 작은 피노키오) 내가 방금 열쇠 하나를 주웠는데 이거 가지고 가볼래 ?"));
	_playerText.insert(make_pair<string, wstring>("LittlePino8", L"(알리도로) 고마워!그런데 너..갑자기 코가 길어졌어.."));
	_playerText.insert(make_pair<string, wstring>("LittlePino9", L"(코가 길어진 작은 피노키오) 신경쓰지마!이곳에서 무사히 나가길 바랄게!안녕!"));
	_playerText.insert(make_pair<string, wstring>("Switch_NoConneted", L"아무런 반응이 없어…"));
	_playerText.insert(make_pair<string, wstring>("Switch_Conneted", L"저기 있는 전등에 불이 켜졌어.. 가볼까..?"));
	_playerText.insert(make_pair<string, wstring>("Toilet_NoConneted", L"깜짝이야!! 도대체 이곳에 무슨 일이 있었던 거지?"));
	_playerText.insert(make_pair<string, wstring>("Toilet_Conneted", L"도대체 이게 무슨.. 어라? 여기에 무엇인가 있어"));
	_playerText.insert(make_pair<string, wstring>("Pino_NoConneted", L"이 끔찍하게 생긴 인형은 뭐지? 소름끼쳐.."));
	_playerText.insert(make_pair<string, wstring>("Pino_Conneted", L"여기에 분명 인형이 있었는데 어디로 사라진거지?"));
	_playerText.insert(make_pair<string, wstring>("RestRoom_GetKey", L"여기에 또 다른 열쇠가 있어!"));
	_playerText.insert(make_pair<string, wstring>("Cheese_NoTrap", L"바닥에 떨어진 음식을 주워 먹고 싶진 않아"));
	_playerText.insert(make_pair<string, wstring>("Cheese_Trap", L"이걸 이용한다면..?"));
	_playerText.insert(make_pair<string, wstring>("WareRoom_GetKey", L"열쇠다!!!"));
	_playerText.insert(make_pair<string, wstring>("GetPaint", L"새로운 그림 조각이다."));
	_playerText.insert(make_pair<string, wstring>("Mouse_NoCheese", L"으아 쥐다! 난 쥐가 너무 싫어…"));
	_playerText.insert(make_pair<string, wstring>("Mouse_Cheese", L"굳이 얘한테 먹이로 주고 싶지 않아.."));
	_playerText.insert(make_pair<string, wstring>("Trap_NoCheese", L"무섭게 생긴 덫이 있어.. 여길 지나가야 하는데…"));
	_playerText.insert(make_pair<string, wstring>("Trap_Cheese", L"이 치즈를 덫 위에 올려볼까..?"));
	_playerText.insert(make_pair<string, wstring>("MouseTrap", L"왜 쥐가 이걸 가지고 있던거야.."));

	_playerText.insert(make_pair<string, wstring>("UpStairs", L"(2층으로 올라갑니다.)"));
	_playerText.insert(make_pair<string, wstring>("DownStairs", L"(1층으로 내려갑니다.)"));

}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
	//SetText("Player_Start");
	LoadData();

	//Sound
	GET_SINGLE(SoundManager)->fVolume;
	GET_SINGLE(SoundManager)->LoadSound(L"Start", "Sounds\\Main\\Title.wav", SoundType::BGM);
	GET_SINGLE(SoundManager)->SetVolume(0.1f);
	GET_SINGLE(SoundManager)->GetVolume(&(GET_SINGLE(SoundManager)->fVolume));

	//GET_SINGLE(SoundManager)->PlayBackgroundSound(L"Start");

#pragma region ResourceLoad
	{
		//GET_SINGLE(SoundManager)->Init();


		//float gVolume;
		//GET_SINGLE(SoundManager)->SetVolume(0.1f);

		


		//UI
		GET_SINGLE(ResourceManager)->LoadTexture(L"Quit", L"Sprite\\UI\\Quit.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Quit", GET_SINGLE(ResourceManager)->GetTexture(L"Quit"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Inventory", L"Sprite\\UI\\Inventory.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Inventory", GET_SINGLE(ResourceManager)->GetTexture(L"Inventory"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Piece1", L"Sprite\\Piece\\Piece1.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Piece1", GET_SINGLE(ResourceManager)->GetTexture(L"Piece1"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Piece2", L"Sprite\\Piece\\Piece2.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Piece2", GET_SINGLE(ResourceManager)->GetTexture(L"Piece2"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Piece3", L"Sprite\\Piece\\Piece3.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Piece3", GET_SINGLE(ResourceManager)->GetTexture(L"Piece3"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Piece4", L"Sprite\\Piece\\Piece4.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Piece4", GET_SINGLE(ResourceManager)->GetTexture(L"Piece4"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Piece5", L"Sprite\\Piece\\Piece5.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Piece5", GET_SINGLE(ResourceManager)->GetTexture(L"Piece5"));


		// HelpUI
		GET_SINGLE(ResourceManager)->LoadTexture(L"UI_Interaction", L"Sprite\\UI\\help\\Interaction.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"UI_Interaction", GET_SINGLE(ResourceManager)->GetTexture(L"UI_Interaction"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"UI_Move", L"Sprite\\UI\\help\\Move.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"UI_Move", GET_SINGLE(ResourceManager)->GetTexture(L"UI_Move"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"UI_StageChange1", L"Sprite\\UI\\help\\StageChange1.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"UI_StageChange1", GET_SINGLE(ResourceManager)->GetTexture(L"UI_StageChange1"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"UI_StageChange2", L"Sprite\\UI\\help\\StageChange2.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"UI_StageChange2", GET_SINGLE(ResourceManager)->GetTexture(L"UI_StageChange2"));
	}

	// Player
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"CharacterRight", L"Sprite\\MainCharacter\\CharacterRight.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"CharacterLeft", L"Sprite\\MainCharacter\\CharacterLeft.bmp", RGB(0, 255, 0));
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"CharacterRight");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_CharacterRight");
			fb->SetInfo({ texture, L"FB_CharacterRight", {220, 220}, 0, 3, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"CharacterLeft");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_CharacterLeft");
			fb->SetInfo({ texture, L"FB_CharacterLeft", {220, 220}, 0, 3, 0, 1.f }
			);
		}
		GET_SINGLE(ResourceManager)->LoadTexture(L"CharacterIdleRight", L"Sprite\\MainCharacter\\CharacterIdleRight.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"CharacterIdleLeft", L"Sprite\\MainCharacter\\CharacterIdleLeft.bmp", RGB(0, 255, 0));
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"CharacterIdleRight");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_CharacterIdleRight");
			fb->SetInfo({ texture, L"FB_CharacterIdleRight", {220, 220}, 0, 1, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"CharacterIdleLeft");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_CharacterIdleLeft");
			fb->SetInfo({ texture, L"FB_CharacterIdleLeft", {220, 220}, 0, 1, 0, 1.f });
		}
	}

	// Pino
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"PinoMoveRight", L"Sprite\\Pino\\PinoMoveRight.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"PinoMoveLeft", L"Sprite\\Pino\\PinoMoveLeft.bmp", RGB(0, 255, 0));
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PinoMoveRight");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PinoMoveRight");
			fb->SetInfo({ texture, L"FB_PinoMoveRight", {300, 450}, 0, 1, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PinoMoveLeft");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PinoMoveLeft");
			fb->SetInfo({ texture, L"FB_PinoMoveLeft", {300, 450}, 0, 1, 0, 1.f });
		}
	}

	// Object
	{
		// 마네킹
		GET_SINGLE(ResourceManager)->LoadTexture(L"Mannequin", L"Sprite\\Object\\Mannequin.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Mannequin", GET_SINGLE(ResourceManager)->GetTexture(L"Mannequin"));

		// 박스
		GET_SINGLE(ResourceManager)->LoadTexture(L"Box", L"Sprite\\Object\\Box.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Box", GET_SINGLE(ResourceManager)->GetTexture(L"Box"));

		// 박스2
		GET_SINGLE(ResourceManager)->LoadTexture(L"Box2", L"Sprite\\Object\\Box2.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Box2", GET_SINGLE(ResourceManager)->GetTexture(L"Box2"));

		// 옷장
		GET_SINGLE(ResourceManager)->LoadTexture(L"Closet", L"Sprite\\Object\\Closet.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Closet", GET_SINGLE(ResourceManager)->GetTexture(L"Closet"));

		// 치즈
		GET_SINGLE(ResourceManager)->LoadTexture(L"Cheese", L"Sprite\\Object\\Cheese.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Cheese", GET_SINGLE(ResourceManager)->GetTexture(L"Cheese"));

		// 키
		GET_SINGLE(ResourceManager)->LoadTexture(L"Key_yellow", L"Sprite\\Object\\Keyyellow.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key_yellow", GET_SINGLE(ResourceManager)->GetTexture(L"Key_yellow"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Key_red", L"Sprite\\Object\\Keyred.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key_red", GET_SINGLE(ResourceManager)->GetTexture(L"Key_red"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Key_blue", L"Sprite\\Object\\Keyblue.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key_blue", GET_SINGLE(ResourceManager)->GetTexture(L"Key_blue"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Key_purple", L"Sprite\\Object\\Keypurple.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key_purple", GET_SINGLE(ResourceManager)->GetTexture(L"Key_purple"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Key_white", L"Sprite\\Object\\KeyWhite.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key_white", GET_SINGLE(ResourceManager)->GetTexture(L"Key_white"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Key_brown", L"Sprite\\Object\\Keybrown.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key_brown", GET_SINGLE(ResourceManager)->GetTexture(L"Key_brown"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"Key_green", L"Sprite\\Object\\Keygreen.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key_green", GET_SINGLE(ResourceManager)->GetTexture(L"Key_green"));

		// 스위치
		/*GET_SINGLE(ResourceManager)->LoadTexture(L"Key", L"Sprite\\Object\\Key.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key", GET_SINGLE(ResourceManager)->GetTexture(L"Key"));*/


		// 쥐덫
		GET_SINGLE(ResourceManager)->LoadTexture(L"MouseTrap", L"Sprite\\Object\\MouseTrap.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"MouseTrap", GET_SINGLE(ResourceManager)->GetTexture(L"MouseTrap"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"MouseTrapped", L"Sprite\\Object\\MouseTrapped.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"MouseTrapped", GET_SINGLE(ResourceManager)->GetTexture(L"MouseTrapped"));

		// 금고
		GET_SINGLE(ResourceManager)->LoadTexture(L"SafeClosed", L"Sprite\\Object\\SafeClosed.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"SafeClosed", GET_SINGLE(ResourceManager)->GetTexture(L"SafeClosed"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"SafeOpen", L"Sprite\\Object\\SafeOpen.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"SafeOpen", GET_SINGLE(ResourceManager)->GetTexture(L"SafeOpen"));

		// 리틀 피노
		GET_SINGLE(ResourceManager)->LoadTexture(L"LittlePino", L"Sprite\\Object\\LittlePinocchio.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"LittlePino", GET_SINGLE(ResourceManager)->GetTexture(L"LittlePino"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"LittlePinoNose", L"Sprite\\Object\\LittlePinocchioLongNose.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"LittlePinoNose", GET_SINGLE(ResourceManager)->GetTexture(L"LittlePinoNose"));

	}
#pragma endregion ResourceLoad


	// Hall
	{
		Hall* newHall = new Hall();

		GET_SINGLE(ResourceManager)->LoadTexture(L"FirstHall1", L"Sprite\\Map\\hall1\\1.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"FirstHall1", GET_SINGLE(ResourceManager)->GetTexture(L"FirstHall1"));
		newHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"FirstHall1"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"FirstHall2", L"Sprite\\Map\\hall1\\2.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"FirstHall2", GET_SINGLE(ResourceManager)->GetTexture(L"FirstHall2"));
		newHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"FirstHall2"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"FirstHall3", L"Sprite\\Map\\hall1\\3.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"FirstHall3", GET_SINGLE(ResourceManager)->GetTexture(L"FirstHall3"));
		newHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"FirstHall3"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"FirstHall4", L"Sprite\\Map\\hall1\\4.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"FirstHall4", GET_SINGLE(ResourceManager)->GetTexture(L"FirstHall4"));
		newHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"FirstHall4"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"FirstHall5", L"Sprite\\Map\\hall1\\5.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"FirstHall5", GET_SINGLE(ResourceManager)->GetTexture(L"FirstHall5"));
		newHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"FirstHall5"));

		newHall->SetLayer(LAYER_BACKGROUND);

		const Vec2Int size = Vec2Int{ 2880, 1080 };

		// camera영역 설정
		GET_SINGLE(SceneManager)->SetBackgroundSize(size);

		AddActor(newHall);
		for (Actor* actor : newHall->_actors)
		{
			AddActor(actor);
		}

		_hallVector.push_back(newHall);
		_currentHall = newHall;

		{
			// Hall -> restroom 이동
			// Hall에 소속
			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_hallColliders.push_back(collider);
				collider->SetActive(true);

				door->AddComponent(collider);
				door->SetPos({ 620, -80 });
				door->SetRoomId(RoomNum::restRoom);

				door->OpenRoom();

				_hallVector[0]->_actors.push_back(door);
			}
			//AddActor(door);
			// TODO : Hall에 추가해야 함.
		}
		{
			// Hall -> 창고 이동
			// Hall에 소속
			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_hallColliders.push_back(collider);
				collider->SetActive(true);

				door->AddComponent(collider);
				door->SetPos({ 2400, -80 });
				door->SetRoomId(RoomNum::wareHouse);

				//door->OpenRoom();

				_hallVector[0]->_actors.push_back(door);
			}
			//AddActor(door);
			// TODO : Hall에 추가해야 함.
		}
		{
			// Hall -> 주방 이동
			// Hall에 소속
			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_hallColliders.push_back(collider);
				collider->SetActive(true);

				door->AddComponent(collider);
				door->SetPos({ 3370, -80 });
				door->SetRoomId(RoomNum::kitchen);

				//door->OpenRoom();

				_hallVector[0]->_actors.push_back(door);
			}
			//AddActor(door);
			// TODO : Hall에 추가해야 함.
		}
		{
			// Hall -> 홀2 이동
			// Hall에 소속
			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_hallColliders.push_back(collider);
				collider->SetActive(true);

				door->AddComponent(collider);
				door->SetPos({ 4640, -80 });
				door->SetRoomId(RoomNum::hall2);

				door->OpenRoom();

				_hallVector[0]->_actors.push_back(door);
			}
			//AddActor(door);
			// TODO : Hall에 추가해야 함.
		}
		{
			Interactionable* littlePino = new Interactionable();
			littlePino->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"LittlePino"));
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 150,150 });
				collider->SetCollisionLayer(CLT_INTERACTIONABLE);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(true);
				_hallColliders.push_back(collider);

				littlePino->AddComponent(collider);
			}
			littlePino->offset = 150;
			littlePino->SetInteractionType(InteractionType::LittlePino);
			littlePino->SetPos({ 3500, 50 });
			AddActor(littlePino);

			_hallVector[0]->_actors.push_back(littlePino);
		}
		{
			Key* key = new Key();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 48,20 });
				collider->SetPos({ 0, 0 });
				collider->SetCollisionLayer(CLT_ITEM);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);

				key->AddComponent(collider);
				key->SetPos({ 3550,100 });
				key->SetKeyID(RoomNum::restRoom);
				key->_myCollider = collider;
				collider->SetActive(false);
				key->isActive = false;

				_hallColliders.push_back(collider);
			}
			AddActor(key);
			key->offset = 150;
			key->SetItemType(ItemType::Key_red);
			key->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_red"));
			key->SetLayer(LAYER_OBJECT);
			key->SetTransparent(true);

			_restRoomKey = key;
		}
	}
	// Hall 2층 
	{
		Hall* secondHall = new Hall();

		GET_SINGLE(ResourceManager)->LoadTexture(L"SecondHall1", L"Sprite\\Map\\hall2\\1.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"SecondHall1", GET_SINGLE(ResourceManager)->GetTexture(L"SecondHall1"));
		secondHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"SecondHall1"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"SecondHall2", L"Sprite\\Map\\hall2\\2.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"SecondHall2", GET_SINGLE(ResourceManager)->GetTexture(L"SecondHall2"));
		secondHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"SecondHall2"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"SecondHall3", L"Sprite\\Map\\hall2\\3.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"SecondHall3", GET_SINGLE(ResourceManager)->GetTexture(L"SecondHall3"));
		secondHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"SecondHall3"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"SecondHall4", L"Sprite\\Map\\hall2\\4.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"SecondHall4", GET_SINGLE(ResourceManager)->GetTexture(L"SecondHall4"));
		secondHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"SecondHall4"));

		GET_SINGLE(ResourceManager)->LoadTexture(L"SecondHall5", L"Sprite\\Map\\hall2\\5.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"SecondHall5", GET_SINGLE(ResourceManager)->GetTexture(L"SecondHall5"));
		secondHall->_backgroundSprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"SecondHall5"));

		secondHall->SetLayer(LAYER_BACKGROUND);

		const Vec2Int size = Vec2Int{ 2880, 1080 };

		// camera영역 설정
		GET_SINGLE(SceneManager)->SetBackgroundSize(size);

		// 		AddActor(secondHall);
		// 		for (Actor* actor : secondHall->_actors)
		// 		{
		// 			AddActor(actor);
		// 		}

		_hallVector.push_back(secondHall);
		//_currentHall = secondHall;


		{
			// Hall2 -> 침실 이동
			// Hall에 소속
			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_hall2Colliders.push_back(collider);
				collider->SetActive(false);

				door->AddComponent(collider);
				door->SetPos({ 1570, -80 });
				door->SetRoomId(RoomNum::bedRoom);

				//door->OpenRoom();

				_hallVector[1]->_actors.push_back(door);
			}
			//AddActor(door);
			// TODO : Hall에 추가해야 함.
		}
		{
			// Hall2 -> 공방 이동
			// Hall에 소속
			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(false);
				_hall2Colliders.push_back(collider);


				door->AddComponent(collider);
				door->SetPos({ 3550, -80 });
				door->SetRoomId(RoomNum::workRoom);

				door->OpenRoom();

				_hallVector[1]->_actors.push_back(door);
			}
			//AddActor(door);
			// TODO : Hall에 추가해야 함.
		}
		{
			// Hall2 -> Hall1 이동
			// Hall에 소속
			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(false);
				_hall2Colliders.push_back(collider);


				door->AddComponent(collider);
				door->SetPos({ 4640, -80 });
				door->SetRoomId(RoomNum::hall1);

				door->OpenRoom();

				_hallVector[1]->_actors.push_back(door);
			}
			//AddActor(door);
			// TODO : Hall에 추가해야 함.
		}

		{
			Interactionable* ending = new Interactionable();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 150,150 });
				collider->SetCollisionLayer(CLT_INTERACTIONABLE);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(false);
				_hall2Colliders.push_back(collider);
				
				ending->AddComponent(collider);
			}
			ending->SetInteractionType(InteractionType::Ending);
			ending->SetPos({ 480, 0 });

			_hallVector[1]->_actors.push_back(ending);
		}
		//AddActor(door);
		//	// TODO : Hall에 추가해야 함.
		//}

	}
#pragma region UI
	{
		// 인벤토리 배경
		{

			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 100, 100 });

			_uis.push_back(ui);
		}

		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 200, 100 });

			_uis.push_back(ui);
		}

		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 300, 100 });

			_uis.push_back(ui);
		}
	}
	{
		// 인벤토리 아이템 부분
		{

			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);

			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_red"), US_Key_red);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_brown"), US_Key_brown);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_yellow"), US_Key_yellow);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_green"), US_Key_green);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_blue"), US_Key_blue);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_purple"), US_Key_purple);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_white"), US_Key_white);

			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Cheese"), US_Cheese);

			GET_SINGLE(UIManager)->SetItem(ui, US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 100, 100 });

			_uis.push_back(ui);
		}

		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);

			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_red"), US_Key_red);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_brown"), US_Key_brown);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_yellow"), US_Key_yellow);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_green"), US_Key_green);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_blue"), US_Key_blue);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_purple"), US_Key_purple);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_white"), US_Key_white);

			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Cheese"), US_Cheese);
			GET_SINGLE(UIManager)->SetItem(ui, US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 200, 100 });

			_uis.push_back(ui);
		}

		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);

			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_red"), US_Key_red);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_brown"), US_Key_brown);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_yellow"), US_Key_yellow);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_green"), US_Key_green);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_blue"), US_Key_blue);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_purple"), US_Key_purple);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_white"), US_Key_white);

			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Cheese"), US_Cheese);
			GET_SINGLE(UIManager)->SetItem(ui, US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 300, 100 });

			_uis.push_back(ui);
		}
	}
	{
		// 그림조각 배경 부분
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1300, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1400, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1500, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1600, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetState(US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1700, 980 });

			_uis.push_back(ui);
		}
		// 그림조각 그림 부분
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece1"), US_PIECE1);

			ui->SetState(US_None);
			GET_SINGLE(UIManager)->SetPiece(ui, US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1300, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece2"), US_PIECE2);
			ui->SetState(US_None);
			GET_SINGLE(UIManager)->SetPiece(ui, US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1400, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece3"), US_PIECE3);
			ui->SetState(US_None);
			GET_SINGLE(UIManager)->SetPiece(ui, US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1500, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece4"), US_PIECE4);
			ui->SetState(US_None);
			GET_SINGLE(UIManager)->SetPiece(ui, US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1600, 980 });

			_uis.push_back(ui);
		}
		{
			//
			UISprite* ui = new UISprite();
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
			ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece5"), US_PIECE5);
			ui->SetState(US_None);
			GET_SINGLE(UIManager)->SetPiece(ui, US_None);
			ui->SetSize({ 90,97 });
			ui->SetPos({ 1700, 980 });

			_uis.push_back(ui);
		}
		/*{
			TestPanel* ui = new TestPanel();
			_uis.push_back(ui);
		}*/

		{
			TutorialPanel* ui = new TutorialPanel();
			ui->_gameScene = this;
			_uis.push_back(ui);
		}
		
	}
#pragma endregion UI

	

	{
		Player* player = new Player();
		{
			auto mapData = _saveData.find("playerX");
			int32 playerX = stoi(mapData->second);

			mapData = _saveData.find("playerY");
			int32 playerY = stoi(mapData->second);

			player->SetPos(Vec2(playerX, playerY));

			{
				// 플레이어 자체 콜라이더. 사실 충돌 처리가
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 99,200 });
				collider->SetCollisionLayer(CLT_PLAYER);
				//collider->AddCollisionFlagLayer(CLT_WALL);
				//collider->RemoveCollisionFlagLayer(CLT_OBJECT);
				//collider->RemoveCollisionFlagLayer(CLT_DOOR);
				GET_SINGLE(CollisionManager)->AddCollider(collider);	// 콜라이더 추가
				player->AddComponent(collider);
				collider->SetActive(true);
			}

			{
				// 플레이어가 벽을 밀 때 필요한 콜라이더
				BoxCollider* checkBox = new BoxCollider();
				checkBox->SetSize({ 110,200 });
				//checkBox->SetTrigger(false);

				checkBox->SetCollisionLayer(CLT_TRIGGER);	// 범위체크용 콜라이더는 반드시 모든 충돌을 꺼준 후 충돌을 체크 할 레이어만 켜줄 것? 그리고 Trigger를 켜주어야 함
				checkBox->RemoveCollisionFlagLayerAll();
				checkBox->AddCollisionFlagLayer(CLT_OBSTACLES);
				checkBox->AddCollisionFlagLayer(CLT_DOOR);
				checkBox->SetTrigger(true);

				checkBox->AddCollisionFlagLayer(CLT_INTERACTIONABLE);

				checkBox->SetPos({ 0, 0 });
				GET_SINGLE(CollisionManager)->AddCollider(checkBox);
				player->AddComponent(checkBox);
			}

			{
				// 플레이어가 벽을 검사할 때 필요한 콜라이더 (양 옆)
				BoxCollider* checkBox = new BoxCollider();
				checkBox->SetSize({ 430,100 });
				//checkBox->SetTrigger(false);

				checkBox->SetCollisionLayer(CLT_TRIGGER2);	// 범위체크용 콜라이더는 반드시 모든 충돌을 꺼준 후 충돌을 체크 할 레이어만 켜줄 것? 그리고 Trigger를 켜주어야 함
				checkBox->RemoveCollisionFlagLayerAll();
				checkBox->AddCollisionFlagLayer(CLT_OBSTACLES);
				checkBox->AddCollisionFlagLayer(CLT_TRAP);
				checkBox->AddCollisionFlagLayer(CLT_MANNEQUIN);
				checkBox->AddCollisionFlagLayer(CLT_INTERACTIONABLE);

				checkBox->SetTrigger(true);

				checkBox->SetPos({ 0, 45 });
				GET_SINGLE(CollisionManager)->AddCollider(checkBox);
				player->AddComponent(checkBox);
			}
			{
				// 플레이어가 벽을 검사할 때 필요한 콜라이더 (저 아래 1층 검사)
				BoxCollider* checkBox = new BoxCollider();
				checkBox->SetSize({ 430,100 });
				//checkBox->SetTrigger(false);

				checkBox->SetCollisionLayer(CLT_TRIGGER4);	// 범위체크용 콜라이더는 반드시 모든 충돌을 꺼준 후 충돌을 체크 할 레이어만 켜줄 것? 그리고 Trigger를 켜주어야 함
				checkBox->RemoveCollisionFlagLayerAll();
				checkBox->AddCollisionFlagLayer(CLT_OBSTACLES);
				checkBox->SetTrigger(true);

				checkBox->SetPos({ 0, 300 });
				GET_SINGLE(CollisionManager)->AddCollider(checkBox);
				player->AddComponent(checkBox);
			}
			{
				// 플레이어가 벽을 검사할 때 필요한 콜라이더 (아래)
				BoxCollider* checkBox = new BoxCollider();
				checkBox->SetSize({ 50,200 });
				//checkBox->SetTrigger(false);

				checkBox->SetCollisionLayer(CLT_TRIGGER3);	// 범위체크용 콜라이더는 반드시 모든 충돌을 꺼준 후 충돌을 체크 할 레이어만 켜줄 것? 그리고 Trigger를 켜주어야 함
				checkBox->RemoveCollisionFlagLayerAll();
				checkBox->AddCollisionFlagLayer(CLT_OBSTACLES);
				checkBox->SetTrigger(true);

				checkBox->SetPos({ 0, 100 });
				GET_SINGLE(CollisionManager)->AddCollider(checkBox);
				player->AddComponent(checkBox);
			}
			CameraComponent* camera = new CameraComponent();
			player->AddComponent(camera);		// 카메라 추가
		}
		AddActor(player);
		_player = player;
		_player->SetLayer(LAYER_OBJECT);
		//newRestRoom->_stages[0]->AddObjectActor(_player);
	}

#pragma region restRoom
	// 화장실
	{
		// 화장실
		{
			Room* newRestRoom = new Room();
			newRestRoom->SetMyScene(this);
			newRestRoom->Init(RoomNum::restRoom);

			newRestRoom->SetLayer(LAYER_BACKGROUND);

			//AddActor(newRoom);

			_roomVector.push_back(newRestRoom);

			// 1층 장애물
			Obstacle* obstacles = new Obstacle();

			//GET_SINGLE(ResourceManager)->LoadTexture(L"Box", L"Sprite\\Object\\Box.bmp");
			//GET_SINGLE(ResourceManager)->CreateSprite(L"Box", GET_SINGLE(ResourceManager)->GetTexture(L"Box"));
			obstacles->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"));


			{
				Interactionable* deadBody = new Interactionable();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 150,150 });
					collider->SetCollisionLayer(CLT_INTERACTIONABLE);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_restRoomColliders.push_back(collider);

					deadBody->AddComponent(collider);
				}
				deadBody->SetInteractionType(InteractionType::Deadbody);
				deadBody->SetPos({ 4000, 0 });

				newRestRoom->_stages[4]->AddObjectActor(deadBody);
			}

			{
				Interactionable* Pino_interaction = new Interactionable();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 300,150 });
					collider->SetCollisionLayer(CLT_INTERACTIONABLE);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_restRoomColliders.push_back(collider);

					Pino_interaction->AddComponent(collider);
				}
				Pino_interaction->SetInteractionType(InteractionType::Pino_interaction);
				Pino_interaction->SetPos({ 4600, 0 });

				newRestRoom->_stages[4]->AddObjectActor(Pino_interaction);
			}

			// 스위치
			Interactionable* switchObject = new Interactionable();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 100, 300 });
				collider->SetCollisionLayer(CLT_INTERACTIONABLE);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_TRIGGER2);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_restRoomColliders.push_back(collider);
				collider->SetActive(false);

				switchObject->AddComponent(collider);
				switchObject->SetPos({ 500, -300 });
			}
			switchObject->SetInteractionType(InteractionType::Switch);
			newRestRoom->_stages[0]->AddObjectActor(switchObject);

			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_restRoomColliders.push_back(collider);
				collider->SetActive(false);
				door->AddComponent(collider);
				door->SetPos({ 220, -80 });

				// hall로 돌아가는 문
				door->SetRoomId(RoomNum::hall1);

				// 일단 열어놓음
				door->OpenRoom();
				newRestRoom->_stages[0]->AddObjectActor(door);
			}

			// 장애물
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 178, 130 });
				collider->SetPos({ 0, 0 });
				collider->SetCollisionLayer(CLT_OBSTACLES);
				collider->RemoveCollisionFlagLayer(CLT_TRIGGER);
				collider->RemoveCollisionFlagLayer(CLT_TRIGGER2);
				collider->RemoveCollisionFlagLayer(CLT_TRIGGER3);


				GET_SINGLE(CollisionManager)->AddCollider(collider);	// 콜라이더 추가
				_restRoomColliders.push_back(collider);
				collider->SetActive(false);

				obstacles->AddComponent(collider);
			}
			obstacles->SetObstacleState(ObstacleState::Movable);
			obstacles->SetPos({ 1100,40 });
			obstacles->SetLayer(LAYER_OBJECT);
			obstacles->SetTransparent(false);
			obstacles->offset = 150;

			newRestRoom->_stages[1]->AddObjectActor(obstacles);

			newRestRoom->_stages[0]->AddObjectActor(_player);
			newRestRoom->_stages[0]->HasPlayer = true;
			newRestRoom->_stages[0]->isVisited = true;

			//AddActor(obstacles);
			// 2층 장애물

			// 창고 키
			{
				Key* key = new Key();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 48,20 });
					collider->SetPos({ 0, 0 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);

					GET_SINGLE(CollisionManager)->AddCollider(collider);

					key->AddComponent(collider);
					key->SetPos({ 4200,100 });
					key->SetKeyID(RoomNum::wareHouse);
					key->_myCollider = collider;
					collider->SetActive(false);

					_restRoomColliders.push_back(collider);
				}
				key->offset = 150;
				key->SetItemType(ItemType::Key_brown);
				key->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_brown"));
				key->SetLayer(LAYER_OBJECT);
				key->SetTransparent(true);

				newRestRoom->_stages[4]->AddObjectActor(key);
				_wareHouseKey = key;
			}
			// 조각 1
			{
				// Piece
				Item* piece = new Item();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 48,20 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);


					GET_SINGLE(CollisionManager)->AddCollider(collider);
					_restRoomColliders.push_back(collider);
					collider->SetActive(false);

					piece->offset = 150;
					piece->_myCollider = collider;
					piece->AddComponent(collider);
					piece->SetPos({ 4300,100 });
				}
				piece->SetItemType(ItemType::Piece);
				piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece1"));
				piece->SetTransparent(true);

				newRestRoom->_stages[4]->AddObjectActor(piece);
				_piece1 = piece;
			}
		}
	}
#pragma endregion restRoom

#pragma region WareHouse
	// 창고
	{
		// hall에 문만들기

		// 창고
		{
			Room* newWareHouse = new Room();
			newWareHouse->SetMyScene(this);
			newWareHouse->Init(RoomNum::wareHouse);
			newWareHouse->SetLayer(LAYER_BACKGROUND);
			_roomVector.push_back(newWareHouse);

			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_wareHouseColliders.push_back(collider);
				collider->SetActive(false);
				door->AddComponent(collider);
				door->SetPos({ 220, -80 });

				// hall로 돌아가는 문
				door->SetRoomId(RoomNum::hall1);

				// 일단 열어놓음
				door->OpenRoom();
				newWareHouse->_stages[0]->AddObjectActor(door);
			}
			{
				// 상자
				Obstacle* box = new Obstacle();
				box->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"));
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 178, 130 });
					collider->SetPos({ 0, 0 });
					collider->SetCollisionLayer(CLT_OBSTACLES);
					collider->RemoveCollisionFlagLayer(CLT_TRIGGER);
					collider->RemoveCollisionFlagLayer(CLT_TRIGGER2);
					collider->RemoveCollisionFlagLayer(CLT_TRIGGER3);

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					_wareHouseColliders.push_back(collider);
					collider->SetActive(false);
					box->AddComponent(collider);
				}
				box->SetPos({ 1400 , 60 });
				box->offset = 150;

				newWareHouse->_stages[1]->AddObjectActor(box);
			}
			{
				// 2층 장애물
				Obstacle* box2 = new Obstacle();
				{
					{
						BoxCollider* collider = new BoxCollider();
						collider->SetSize({ 220,260 });
						collider->SetPos({ 0,100 });
						collider->SetCollisionLayer(CLT_OBSTACLES);
						collider->RemoveCollisionFlagLayer(CLT_TRIGGER);
						collider->RemoveCollisionFlagLayer(CLT_TRIGGER2);
						collider->RemoveCollisionFlagLayer(CLT_TRIGGER3);
						GET_SINGLE(CollisionManager)->AddCollider(collider);	// 콜라이더 추가
						_wareHouseColliders.push_back(collider);
						collider->SetActive(false);
						box2->AddComponent(collider);
					}

					box2->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box2"));

					box2->SetTransparent(true);
					box2->SetObstacleLevel(ObstacleLevel::Level2);
					box2->SetObstacleState(ObstacleState::Unmovable);
				}
				box2->SetPos({ 3400, -80 });
				box2->offset = 230;
				newWareHouse->_stages[3]->AddObjectActor(box2);
			}

			// 주방 키
			{
				Key* key = new Key();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 48,20 });
					collider->SetPos({ 0, 0 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);

					GET_SINGLE(CollisionManager)->AddCollider(collider);

					key->AddComponent(collider);
					key->SetPos({ 3400, -150 });
					key->SetKeyID(RoomNum::kitchen);
					key->_myCollider = collider;

					collider->SetActive(false);
					_wareHouseColliders.push_back(collider);
				}
				key->offset = 150;
				key->SetItemType(ItemType::Key_yellow);
				key->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_yellow"));
				key->SetLayer(LAYER_OBJECT);
				key->SetTransparent(true);

				newWareHouse->_stages[3]->AddObjectActor(key);
				_kitchenKey = key;
			}
			// 조각 1
			{
				// Piece
				Item* piece = new Item();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 48,20 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);


					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_wareHouseColliders.push_back(collider);

					piece->_myCollider = collider;
					piece->AddComponent(collider);
					piece->SetPos({ 4300,100 });


					piece->offset = 150;
				}
				piece->SetItemType(ItemType::Piece);
				piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece2"));
				piece->SetTransparent(true);

				newWareHouse->_stages[4]->AddObjectActor(piece);
				_piece2 = piece;
			}
			// cheese 치즈
			{
				Cheese* cheese = new Cheese();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 40,40 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);

					GET_SINGLE(CollisionManager)->AddCollider(collider);

					cheese->AddComponent(collider);
					cheese->SetPos({ 2500, 100 });
					cheese->offset = 150;

					collider->SetActive(false);
					_wareHouseColliders.push_back(collider);
				}
				cheese->SetItemType(ItemType::Cheese);
				cheese->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Cheese"));
				cheese->SetTransparent(true);

				newWareHouse->_stages[2]->AddObjectActor(cheese);
				_cheese = cheese;
			}
			newWareHouse->_stages[0]->AddObjectActor(_player);
			newWareHouse->_stages[0]->HasPlayer = true;
			newWareHouse->_stages[0]->isVisited = true;
		}
	}
#pragma endregion WareHouse

#pragma region Kitchen

	// 주방
	{
		// 주방
		{
			Room* newKitchen = new Room();
			newKitchen->SetMyScene(this);
			newKitchen->Init(RoomNum::kitchen);

			newKitchen->SetLayer(LAYER_BACKGROUND);

			//AddActor(newRoom);

			_roomVector.push_back(newKitchen);

			// 조각 1
			{
				// Piece
				Item* piece = new Item();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 48,20 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);


					GET_SINGLE(CollisionManager)->AddCollider(collider);
					_kitchenColliders.push_back(collider);
					collider->SetActive(false);

					piece->_myCollider = collider;
					piece->AddComponent(collider);
					piece->SetPos({ 2100,100 });
				}
				piece->SetItemType(ItemType::Piece);
				piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece3"));
				piece->SetTransparent(true);

				newKitchen->_stages[2]->AddObjectActor(piece);
				_piece3 = piece;
			}

			Door* door = new Door();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 170, 400 });
				collider->SetCollisionLayer(CLT_DOOR);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_kitchenColliders.push_back(collider);
				collider->SetActive(false);
				door->AddComponent(collider);
				door->SetPos({ 220, -80 });

				// hall로 돌아가는 문
				door->SetRoomId(RoomNum::hall1);

				// 일단 열어놓음
				door->OpenRoom();
				newKitchen->_stages[0]->AddObjectActor(door);
			}


			// 함정

			Trap* trap = new Trap();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 100, 50 });
				collider->SetCollisionLayer(CLT_TRAP);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);
				collider->AddCollisionFlagLayer(CLT_TRIGGER2);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(false);
				_kitchenColliders.push_back(collider);

				trap->AddComponent(collider);
				trap->SetPos({ 2100, 100 });
				trap->offset = 150;
			}
			trap->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"MouseTrap"));
			//trap->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"MouseTrapped"));
			newKitchen->_stages[2]->AddObjectActor(trap);

			newKitchen->_stages[0]->AddObjectActor(_player);
			newKitchen->_stages[0]->HasPlayer = true;
			newKitchen->_stages[0]->isVisited = true;

			{
				Key* key = new Key();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 48,20 });
					collider->SetPos({ 0, 0 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);

					GET_SINGLE(CollisionManager)->AddCollider(collider);

					key->AddComponent(collider);
					key->SetPos({ 4200,100 });
					key->SetKeyID(RoomNum::bedRoom);
					key->_myCollider = collider;
					collider->SetActive(false);

					_kitchenColliders.push_back(collider);
				}
				key->offset = 150;
				key->SetItemType(ItemType::Key_green);
				key->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_green"));
				key->SetLayer(LAYER_OBJECT);
				key->SetTransparent(true);

				newKitchen->_stages[4]->AddObjectActor(key);
				//_wareHouseKey = key;
			}
		}
	}
#pragma endregion Kitchen

#pragma region workRoom

	// 공방
	{
		Room* newWorkRoom = new Room();
		newWorkRoom->SetMyScene(this);
		newWorkRoom->Init(RoomNum::workRoom);

		newWorkRoom->SetLayer(LAYER_BACKGROUND);

		//AddActor(newRoom);

		_roomVector.push_back(newWorkRoom);

		Door* door = new Door();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 170, 400 });
			collider->SetCollisionLayer(CLT_DOOR);
			collider->RemoveCollisionFlagLayerAll();
			collider->AddCollisionFlagLayer(CLT_TRIGGER);
			//collider->AddCollisionFlagLayer(CLT_PLAYER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			_workRoomColliders.push_back(collider);
			collider->SetActive(false);
			door->AddComponent(collider);
			door->SetPos({ 4600, -80 });

			// hall로 돌아가는 문
			door->SetRoomId(RoomNum::hall2);

			// 일단 열어놓음
			door->OpenRoom();
			newWorkRoom->_stages[4]->AddObjectActor(door);
		}
		//마네킹
		Mannequin* mannequin = new Mannequin();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 100, 220 });
			collider->SetCollisionLayer(CLT_MANNEQUIN);
			collider->RemoveCollisionFlagLayerAll();
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			collider->SetActive(false);
			_workRoomColliders.push_back(collider);

			mannequin->AddComponent(collider);
		}
		mannequin->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Mannequin"));

		mannequin->SetTransparent(true);
		//mannequin->SetLayer(LAYER_BACKGROUND);
		mannequin->SetPos({ 3500,-25 });
		//AddActor(mannequin);
		mannequin->offset = 150;
		newWorkRoom->_stages[3]->AddObjectActor(mannequin);

		{
			dollcheck = new DollCheck();
			{
				// 인형
				Doll* doll = new Doll();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 80, 150 });
					collider->SetCollisionLayer(CLT_INTERACTIONABLE);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_workRoomColliders.push_back(collider);

					doll->AddComponent(collider);
					doll->SetPos({ 300, 0 });
				}
				doll->SetMyScene(this);
				doll->SetInteractionType(InteractionType::Doll);
				doll->SetDollID(A);
				//AddActor(doll);
				dollcheck->AddDoll(doll);
			}
			{
				// 인형
				Doll* doll = new Doll();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 80, 150 });
					collider->SetCollisionLayer(CLT_INTERACTIONABLE);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);
					//collider->AddCollisionFlagLayer(CLT_TRIGGER2);

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_workRoomColliders.push_back(collider);

					doll->AddComponent(collider);
					doll->SetPos({ 460, 0 });
				}
				doll->SetMyScene(this);
				doll->SetInteractionType(InteractionType::Doll);
				doll->SetDollID(B);
				//AddActor(doll);
				dollcheck->AddDoll(doll);
			}
			{
				// 인형
				Doll* doll = new Doll();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 80, 150 });
					collider->SetCollisionLayer(CLT_INTERACTIONABLE);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);
					//collider->AddCollisionFlagLayer(CLT_TRIGGER2);

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_workRoomColliders.push_back(collider);

					doll->AddComponent(collider);
					doll->SetPos({ 620, 0 });
				}
				doll->SetMyScene(this);
				doll->SetInteractionType(InteractionType::Doll);
				doll->SetDollID(C);
				//AddActor(doll);
				dollcheck->AddDoll(doll);
			}
			{
				// 인형
				Doll* doll = new Doll();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 80, 150 });
					collider->SetCollisionLayer(CLT_INTERACTIONABLE);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);
					//collider->AddCollisionFlagLayer(CLT_TRIGGER2);

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_workRoomColliders.push_back(collider);

					doll->AddComponent(collider);
					doll->SetPos({ 780, 0 });
				}
				doll->SetMyScene(this);
				doll->SetInteractionType(InteractionType::Doll);
				doll->SetDollID(D);
				//AddActor(doll);
				dollcheck->AddDoll(doll);
			}

			for (int32 i = 0; i < 4; i++)
			{
				newWorkRoom->_stages[0]->AddObjectActor((dollcheck->GetDoll(i)));
			}

			// 조각 1
			{
				// Piece
				Item* piece = new Item();
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 48,20 });
					collider->SetCollisionLayer(CLT_ITEM);
					collider->RemoveCollisionFlagLayerAll();
					collider->AddCollisionFlagLayer(CLT_TRIGGER);


					GET_SINGLE(CollisionManager)->AddCollider(collider);
					_workRoomColliders.push_back(collider);
					collider->SetActive(false);

					piece->_myCollider = collider;
					piece->AddComponent(collider);
					piece->SetPos({ 4300,100 });
				}
				piece->SetItemType(ItemType::Piece);
				piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece3"));
				piece->SetTransparent(true);

				newWorkRoom->_stages[4]->AddObjectActor(piece);
				_piece5 = piece;
			}
		}


		// 스테이지 배치

		newWorkRoom->_stages[4]->AddObjectActor(_player);
		newWorkRoom->_stages[4]->HasPlayer = true;
		newWorkRoom->_stages[4]->isVisited = true;

	}

#pragma endregion workRoom

#pragma region bedRoom

	// 침실
	{
		Room* newBedRoom = new Room();
		newBedRoom->SetMyScene(this);
		newBedRoom->Init(RoomNum::bedRoom);
		newBedRoom->SetLayer(LAYER_BACKGROUND);
		//AddActor(newRoom);
		_roomVector.push_back(newBedRoom);


		{
			// Piece
			Item* piece = new Item();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 48,20 });
				collider->SetCollisionLayer(CLT_ITEM);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);


				GET_SINGLE(CollisionManager)->AddCollider(collider);
				_bedRoomColliders.push_back(collider);
				collider->SetActive(false);

				piece->_myCollider = collider;
				piece->AddComponent(collider);
				piece->SetPos({ 1800,0 });
			}
			piece->SetItemType(ItemType::Piece);
			piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece4"));
			piece->SetTransparent(true);

			newBedRoom->_stages[1]->AddObjectActor(piece);
			_piece4 = piece;
		}

		// 제페토
		{
			Interactionable* zepeto = new Interactionable();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 150,150 });
				collider->SetCollisionLayer(CLT_INTERACTIONABLE);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER2);

				GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(false);
				_bedRoomColliders.push_back(collider);

				zepeto->AddComponent(collider);
			}
			zepeto->SetPos({ 1800, 0 });
			zepeto->SetInteractionType(InteractionType::Zepeto);
			newBedRoom->_stages[1]->AddObjectActor(zepeto);
			//AddActor(zepeto);
		}

		// 공방 키
		{
			Key* key = new Key();
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 48,20 });
				collider->SetPos({ 0, 0 });
				collider->SetCollisionLayer(CLT_ITEM);
				collider->RemoveCollisionFlagLayerAll();
				collider->AddCollisionFlagLayer(CLT_TRIGGER);

				GET_SINGLE(CollisionManager)->AddCollider(collider);

				key->AddComponent(collider);
				key->SetPos({ 300,100 });
				key->SetKeyID(RoomNum::workRoom);
				key->_myCollider = collider;
				collider->SetActive(false);

				_bedRoomColliders.push_back(collider);
			}
			key->offset = 150;
			key->SetItemType(ItemType::Key_blue);
			key->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key_blue"));
			key->SetLayer(LAYER_OBJECT);
			key->SetTransparent(true);

			newBedRoom->_stages[0]->AddObjectActor(key);

			// 공방키 
			_workRoomKey = key;
		}
		//금고

		StrongBox* safe = new StrongBox();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 230, 230 });
			collider->SetCollisionLayer(CLT_INTERACTIONABLE);
			collider->RemoveCollisionFlagLayerAll();
			collider->AddCollisionFlagLayer(CLT_TRIGGER);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			collider->SetActive(false);
			_bedRoomColliders.push_back(collider);

			safe->AddComponent(collider);
		}
		safe->SetInteractionType(InteractionType::Safe);
		safe->SetPos({ 300, safe->GetPos().y });
		safe->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"SafeClosed"));
		safe->SetLayer(LAYER_BACKGROUND);
		safe->offset = 150;
		newBedRoom->_stages[0]->AddObjectActor(safe);


		//옷장

		Closet* closet = new Closet();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 230, 334 });
			collider->SetCollisionLayer(CLT_CLOSET);
			collider->RemoveCollisionFlagLayerAll();
			collider->AddCollisionFlagLayer(CLT_TRIGGER);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			collider->SetActive(false);
			_bedRoomColliders.push_back(collider);

			closet->AddComponent(collider);
		}

		closet->SetLayer(LAYER_BACKGROUND);
		closet->SetPos({ 3500, -40 });
		closet->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Closet"));
		closet->SetTransparent(true);
		closet->offset = 150;
		//홀2로 가는 문 추가
		Door* door = new Door();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 170, 400 });
			collider->SetCollisionLayer(CLT_DOOR);
			collider->RemoveCollisionFlagLayerAll();
			collider->AddCollisionFlagLayer(CLT_TRIGGER);
			//collider->AddCollisionFlagLayer(CLT_PLAYER);
				//collider->AddCollisionFlagLayer(CLT_PLAYER);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			_bedRoomColliders.push_back(collider);
			collider->SetActive(false);
			door->AddComponent(collider);
			door->SetPos({ 4600, -80 });

			// hall로 돌아가는 문
			door->SetRoomId(RoomNum::hall2);

			// 일단 열어놓음
			door->OpenRoom();

		}
		// 스테이지 배치
		newBedRoom->_stages[3]->AddObjectActor(closet);
		newBedRoom->_stages[4]->AddObjectActor(door);

		{
			Pinocchio* pino = new Pinocchio();
			pino->_flipbookLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PinoMoveLeft");
			pino->_flipbookRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PinoMoveRight");
			{
				{
					BoxCollider* collider = new BoxCollider();
					collider->SetSize({ 100, 220 });
					collider->SetCollisionLayer(CLT_PINO);
					collider->RemoveCollisionFlagLayerAll();

					GET_SINGLE(CollisionManager)->AddCollider(collider);
					collider->SetActive(false);
					_bedRoomColliders.push_back(collider);

					pino->AddComponent(collider);
				}
				{
					BoxCollider* checkBox = new BoxCollider();
					checkBox->SetSize({ 3000,200 });
					//checkBox->SetTrigger(false);
					checkBox->SetCollisionLayer(CLT_TRIGGER);	// 범위체크용 콜라이더는 반드시 모든 충돌을 꺼준 후 충돌을 체크 할 레이어만 켜줄 것? 그리고 Trigger를 켜주어야 함
					checkBox->RemoveCollisionFlagLayerAll();
					checkBox->AddCollisionFlagLayer(CLT_OBSTACLES);
					checkBox->SetTrigger(true);
					checkBox->SetPos({ 0, 0 });

					GET_SINGLE(CollisionManager)->AddCollider(checkBox);
					checkBox->SetActive(false);
					_bedRoomColliders.push_back(checkBox);

					pino->AddComponent(checkBox);
				}
				pino->SetPos({ 1700, 0 });
				newBedRoom->_stages[0]->AddObjectActor(pino);
			}
		}




		newBedRoom->_stages[4]->AddObjectActor(_player);
		newBedRoom->_stages[4]->HasPlayer = true;
		newBedRoom->_stages[4]->isVisited = true;

	}

#pragma endregion bedRoom

	// 라이트 초기화 항상 마지막이어야 함
	{
		_light = new Light();
		GET_SINGLE(SceneManager)->SetLight(_light);

		_light->SetLayer(LAYER_OBJECT);
		AddActor(_light);
	}
	Super::Init();
}

void GameScene::Update()
{
	Super::Update();
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::ESC))
	{
		PostQuitMessage(0);
	}
	// 데드 씬 이동
	if (_player->GetIsAlive() == false)
	{
		GET_SINGLE(SceneManager)->SetCameraPos({ 0,0 });
		_sceneType = SceneType::DeadScene;
	}
	// 인형 순서 체크 -> 공방 스테이지 클리어 조건
	dollcheck->Tick();

	if (_isRestRoomClear && _currentRoom == _roomVector[0] && isUseSwitch)
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		GET_SINGLE(SceneManager)->AddLightRegion(3900 - ((int32)cameraPos.x - GWinSizeX / 2), 100);
	}
	// 	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::H))
	// 	{
	// 		EnterHall(RoomNum::bedRoom);
	// 	}

		/// 일단 여기에 화장실 스테이지 클리어 조건 만듦.
	{
		if (!_isRestRoomClear)
		{
			for (int i = 0; i < 5; i++)
			{
				switch (i)
				{
				case 0:
					if (_roomVector[0]->_stages[0]->GetStageID() == StageID::Stage1)
						continue;
					return;
				case 1:
					if (_roomVector[0]->_stages[1]->GetStageID() == StageID::Stage3)
						continue;
					return;
				case 2:
					if (_roomVector[0]->_stages[2]->GetStageID() == StageID::Stage2)
						continue;
					return;
				case 3:
					if (_roomVector[0]->_stages[3]->GetStageID() == StageID::Stage4)
						continue;
					return;
				case 4:
					if (_roomVector[0]->_stages[4]->GetStageID() == StageID::Stage5)
					{
						_isRestRoomClear = true;
					}
					break;
				}
			}
		}
	}


}

void GameScene::EnterRoom(RoomNum roomNum)
{
	static bool isEnterWareHouse = false;
	static bool isEnterWorkRoom = false;


	_currentHall = nullptr;

	_actors[LAYER_BACKGROUND].clear(); // 배경 삭제 
	_actors[LAYER_OBJECT].clear();

	AddActor(_player);
	switch (roomNum)
	{
	case RoomNum::restRoom:
		if (_isRestRoomClear && isUseSwitch && !_isGetRestRoomKey && !_isGetPiece1)
		{
			_wareHouseKey->_myCollider->SetActive(true);
			_wareHouseKey->isActive = true;

			_piece1->_myCollider->SetActive(true);
			_piece1->isActive = true;
		}
		else
		{
			_wareHouseKey->_myCollider->SetActive(false);
			_wareHouseKey->isActive = false;

			_piece1->_myCollider->SetActive(false);
			_piece1->isActive = false;
		}

		_player->SetPos(Vec2(225, 0));
		dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 225,0 });
		_currentRoom = _roomVector[0];

		for (int i = 0; i < 5; i++)
		{
			Stage* stage = _roomVector[0]->GetStage(i);
			AddActor(stage);
			for (int i = 0; i < stage->_objectActor.size(); i++)
			{
				if (stage->_objectActor[i] == _player)
				{
					continue;
				}
				AddActor(stage->_objectActor[i]);
			}
		}
		AddActor(_roomVector[0]);
		break;
	case RoomNum::wareHouse:
		if (!isEnterWareHouse)
		{
			_kitchenKey->_myCollider->SetActive(true);
			_kitchenKey->isActive = true;
			_cheese->isActive = true;

			_piece2->_myCollider->SetActive(true);
			_piece2->isActive = true;

			isEnterWareHouse = true;
		}

		_player->SetPos(Vec2(225, 0));
		dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 225,0 });
		_currentRoom = _roomVector[1];

		for (int i = 0; i < 5; i++)
		{
			Stage* stage = _roomVector[1]->GetStage(i);
			AddActor(stage);
			for (int i = 0; i < stage->_objectActor.size(); i++)
			{
				if (stage->_objectActor[i] == _player)
				{
					continue;
				}
				AddActor(stage->_objectActor[i]);
			}
		}
		AddActor(_roomVector[1]);
		break;


	case RoomNum::kitchen:
	{
		_piece3->_myCollider->SetActive(false);
		_piece3->isActive = false;
		_player->SetPos(Vec2(225, 0));
		dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 225,0 });
		_currentRoom = _roomVector[2];

		for (int i = 0; i < 5; i++)
		{
			Stage* stage = _roomVector[2]->GetStage(i);
			AddActor(stage);
			for (int i = 0; i < stage->_objectActor.size(); i++)
			{
				if (stage->_objectActor[i] == _player)
				{
					continue;
				}
				AddActor(stage->_objectActor[i]);
			}
		}
		AddActor(_roomVector[2]);
	}
	break;

	case RoomNum::workRoom:
		/*if (!isEnterWorkRoom)
		{

			_piece3->_myCollider->SetActive(true);
			_piece3->isActive = true;

			isEnterWorkRoom = true;
		}*/
		_piece5->_myCollider->SetActive(false);
		_piece5->isActive = false;

		
		_player->SetPos(Vec2(4580, 0));
		dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 4580,0 });
		_currentRoom = _roomVector[3];

		for (int i = 0; i < 5; i++)
		{
			Stage* stage = _roomVector[3]->GetStage(i);
			AddActor(stage);
			for (int i = 0; i < stage->_objectActor.size(); i++)
			{
				if (stage->_objectActor[i] == _player)
				{
					continue;
				}
				AddActor(stage->_objectActor[i]);
			}
		}
		AddActor(_roomVector[3]);
		break;
	case RoomNum::bedRoom:
		_piece4->_myCollider->SetActive(false);
		_piece4->isActive = false;
		_workRoomKey->_myCollider->SetActive(false);
		_workRoomKey->isActive = false;
		_player->SetPos(Vec2(4580, 0));
		dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 4580,0 });
		_currentRoom = _roomVector[4];

		for (int i = 0; i < 5; i++)
		{
			Stage* stage = _roomVector[4]->GetStage(i);
			AddActor(stage);
			for (int i = 0; i < stage->_objectActor.size(); i++)
			{
				if (stage->_objectActor[i] == _player)
				{
					continue;
				}
				AddActor(stage->_objectActor[i]);
			}
		}
		AddActor(_roomVector[4]);
		break;

	}
	AddActor(_light);

}

void GameScene::EnterHall(RoomNum roomNum)
{
	float checkTime = 0;

	switch (roomNum)
	{
	case RoomNum::hall1:
		SetText("DownStairs");
		if (!_isGetRestRoomKey && _isLittleTakingEnd)
		{
			_restRoomKey->_myCollider->SetActive(true);
			_restRoomKey->isActive = true;
		}
		else
		{
			_restRoomKey->_myCollider->SetActive(false);
		}


		if (_currentRoom == _roomVector[0])
		{
			_player->SetPos(Vec2{ 615, 0 });
			dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 615,0 });
		}
		else if (_currentRoom == _roomVector[1])
		{
			_player->SetPos(Vec2(2400, 0));
			dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 2400,0 });
		}
		else if (_currentRoom == _roomVector[2])
		{
			_player->SetPos(Vec2(3370,  0));
			dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 3370,0 });
		}
		//_player->SetPos(Vec2(4500, 0));
		_currentRoom = nullptr;

		_actors[LAYER_BACKGROUND].clear(); // 배경 삭제 
		_actors[LAYER_OBJECT].clear();

		_currentHall = _hallVector[0];

		AddActor(_currentHall);
		AddActor(_player);

		for (int i = 0; i < _hallVector[0]->_actors.size(); i++)
		{
			AddActor(_hallVector[0]->_actors[i]);
		}
		AddActor(_light);
		break;

	case RoomNum::hall2:
		SetText("UpStairs");
		if (_currentRoom == _roomVector[3])
		{
			_player->SetPos(Vec2{ 3550, 0 });
			dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 3550,0 });
		}
		else if (_currentRoom == _roomVector[4])
		{
			_player->SetPos(Vec2(1570, 0));
			dynamic_cast<CameraComponent*>(_player->_components[5])->SetCameraPosition({ 1570,0 });
		}
		
		_currentRoom = nullptr;

		_actors[LAYER_BACKGROUND].clear(); // 배경 삭제 
		_actors[LAYER_OBJECT].clear();

		_currentHall = _hallVector[1];

		AddActor(_currentHall);
		AddActor(_player);

		for (int i = 0; i < _hallVector[1]->_actors.size(); i++)
		{
			AddActor(_hallVector[1]->_actors[i]);
		}
		AddActor(_light);
		break;
	}

}

void GameScene::Render(HDC hdc)
{
	Super::Render(hdc);
	if (_currentText != L"")
	{
		::TextOut(hdc, 960, 900, _currentText.c_str(), static_cast<int32>(_currentText.size()));
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E) && !isOnTextThisFrame)
	{
		_currentText = L"";
	}
	isOnTextThisFrame = false;
}

void GameScene::SetText(string key)
{
	if (_playerText.size() == 0)
		return;
	_currentText = _playerText[key];
	isOnTextThisFrame = true;
}
