#include "pch.h"
#include "DevScene.h"
#include "TimeManager.h"

#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "Flipbook.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "UI.h"
#include "Button.h"
#include "TestPanel.h"
#include "Tilemap.h"
#include "TilemapActor.h"
#include "InputManager.h"

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

// Component
#include "CameraComponent.h"
#include "BoxCollider.h"



DevScene::DevScene()
{

}

DevScene::~DevScene()
{

}

void DevScene::Init()
{
	LoadData();
	

	//////////////////////////////////////////////////////////////
	/// Load Resources ///
	//////////////////////////////////////////////////////////////

	{
		// TEMP 나중에 삭제
	// ResourceManager에 텍스처 불러오기
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
		//GET_SINGLE(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Quit", L"Sprite\\UI\\Quit.bmp", RGB(0, 255, 0));


		GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 0, 48, 48);


		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	}
	{
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
		GET_SINGLE(ResourceManager)->LoadTexture(L"Key", L"Sprite\\Object\\Key.bmp", RGB(0, 255, 0));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Key", GET_SINGLE(ResourceManager)->GetTexture(L"Key"));
	}

	// BackGround ( Temp )
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");
		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();

		// camera영역 설정
		GET_SINGLE(SceneManager)->SetBackgroundSize(size);

		background->SetPos(Vec2(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2)));
		//_actors.push_back(background);
		AddActor(background);
	}


	//////////////////////////////////////////////////////////////
	/// Actor ///
	//////////////////////////////////////////////////////////////
	/*{
		TestPanel* ui = new TestPanel();
		_uis.push_back(ui);
	}*/

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
	}

	{
		// 1층 장애물
		//Obstacle* obstacles = new Obstacle();
		//{
		//	{
		//		BoxCollider* collider = new BoxCollider();
		//		collider->SetSize({ 220,130 });
		//		collider->SetPos({ 0,35 });
		//		collider->SetCollisionLayer(CLT_OBSTACLES);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER2);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER3);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER4);
		//		GET_SINGLE(CollisionManager)->AddCollider(collider);	// 콜라이더 추가
		//		obstacles->AddComponent(collider);
		//	}
		//	obstacles->SetObstacleLevel(ObstacleLevel::Level1);
		//	obstacles->SetObstacleState(ObstacleState::Movable);
		//	obstacles->SetPos({ 400,335 });
		//}
		//AddActor(obstacles);

	}
	{
		// 1층 장애물
		//Obstacle* obstacles = new Obstacle();
		//{
		//	{
		//		BoxCollider* collider = new BoxCollider();
		//		collider->SetSize({ 178,130 });
		//		//collider->SetPos({ 0,35 });
		//		collider->SetCollisionLayer(CLT_OBSTACLES);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER2);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER3);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER4);
		//		GET_SINGLE(CollisionManager)->AddCollider(collider);	// 콜라이더 추가
		//		obstacles->AddComponent(collider);
		//	}
		//	obstacles->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"));
		//	obstacles->SetTransparent(true);
		//	obstacles->SetObstacleLevel(ObstacleLevel::Level1);
		//	obstacles->SetObstacleState(ObstacleState::Movable);
		//	obstacles->SetPos({ 1500,370 });
		//}
		//AddActor(obstacles);


	}

	{
		// 2층 장애물
		//Obstacle* obstacles = new Obstacle();
		//{
		//	{
		//		BoxCollider* collider = new BoxCollider();
		//		collider->SetSize({ 220,260 });
		//		collider->SetPos({ 0,100 });
		//		collider->SetCollisionLayer(CLT_OBSTACLES);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER2);
		//		collider->RemoveCollisionFlagLayer(CLT_TRIGGER3);
		//		GET_SINGLE(CollisionManager)->AddCollider(collider);	// 콜라이더 추가
		//		obstacles->AddComponent(collider);
		//	}

		//	obstacles->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box2"));
		//	obstacles->SetTransparent(true);
		//	obstacles->SetObstacleLevel(ObstacleLevel::Level2);
		//	obstacles->SetObstacleState(ObstacleState::Unmovable);
		//	obstacles->SetPos({ 800,205 });
		//}
		//AddActor(obstacles);
	}
	//{
	//	// key 1
	//	Key* key = new Key();
	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetSize({ 48,20 });
	//		collider->SetCollisionLayer(CLT_ITEM);
	//		collider->RemoveCollisionFlagLayerAll();
	//		collider->AddCollisionFlagLayer(CLT_TRIGGER);


	//		GET_SINGLE(CollisionManager)->AddCollider(collider);

	//		key->AddComponent(collider);
	//		key->SetPos({ 100,100 });
	//		key->SetKeyID(RoomNum::restRoom);
	//	}
	//	key->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key"));
	//	key->SetTransparent(true);
	//	AddActor(key);
	//}
	//{
	//	// key 2
	//	Key* key = new Key();
	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetSize({ 48,20 });
	//		collider->SetCollisionLayer(CLT_ITEM);
	//		collider->RemoveCollisionFlagLayerAll();
	//		collider->AddCollisionFlagLayer(CLT_TRIGGER);


	//		GET_SINGLE(CollisionManager)->AddCollider(collider);

	//		key->AddComponent(collider);
	//		key->SetPos({ 600,100 });
	//		key->SetKeyID(RoomNum::bedRoom);
	//	}
	//	key->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key"));
	//	key->SetTransparent(true);
	//	AddActor(key);
	//}
	//{
	//	Door* door = new Door();
	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetSize({ 100, 200 });
	//		collider->SetCollisionLayer(CLT_DOOR);
	//		collider->RemoveCollisionFlagLayerAll();
	//		collider->AddCollisionFlagLayer(CLT_TRIGGER);
	//		//collider->AddCollisionFlagLayer(CLT_PLAYER);

	//		GET_SINGLE(CollisionManager)->AddCollider(collider);

	//		door->AddComponent(collider);
	//		door->SetPos({ 800, 0 });
	//		door->SetRoomId(RoomNum::wareHouse);
	//	}
	//	AddActor(door);
	//}
	{
		// 리틀 피노키오 // 이미지 넣어야 함.
		/*Interactionable* littlePino = new Interactionable();
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 150,150 });
			collider->SetCollisionLayer(CLT_INTERACTIONABLE);
			collider->RemoveCollisionFlagLayerAll();
			collider->AddCollisionFlagLayer(CLT_TRIGGER2);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			littlePino->AddComponent(collider);
		}
		littlePino->SetPos({ 1000, 350 });
		littlePino->SetInteractionType(InteractionType::LittlePino);
		AddActor(littlePino);*/
	}
	

	{
		// 옷장
		//Closet* closet = new Closet();
		//{
		//	BoxCollider* collider = new BoxCollider();
		//	collider->SetSize({ 233, 334 });
		//	collider->SetCollisionLayer(CLT_CLOSET);
		//	collider->RemoveCollisionFlagLayerAll();
		//	collider->AddCollisionFlagLayer(CLT_TRIGGER);

		//	GET_SINGLE(CollisionManager)->AddCollider(collider);

		//	closet->AddComponent(collider);
		//	closet->SetPos({ 1100, 200 });
		//	//closet->
		//}
		//closet->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Closet"));
		//closet->SetTransparent(true);
		//AddActor(closet);
	}
	//{
	//	// 치즈
	//	Cheese* cheese = new Cheese();
	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetSize({ 40,40 });
	//		collider->SetCollisionLayer(CLT_ITEM);
	//		collider->RemoveCollisionFlagLayerAll();
	//		collider->AddCollisionFlagLayer(CLT_TRIGGER);

	//		GET_SINGLE(CollisionManager)->AddCollider(collider);

	//		cheese->AddComponent(collider);
	//		cheese->SetPos({ 1100,0 });
	//	}
	//	cheese->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Cheese"));
	//	cheese->SetTransparent(true);
	//	AddActor(cheese);
	//}
	//{
	//	// 함정

	//	Trap* trap = new Trap();
	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetSize({ 100, 50 });
	//		collider->SetCollisionLayer(CLT_TRAP);
	//		collider->RemoveCollisionFlagLayerAll();
	//		collider->AddCollisionFlagLayer(CLT_TRIGGER);
	//		collider->AddCollisionFlagLayer(CLT_TRIGGER2);

	//		GET_SINGLE(CollisionManager)->AddCollider(collider);

	//		trap->AddComponent(collider);
	//		trap->SetPos({ 1300, 0 });
	//	}
	//	AddActor(trap);
	//}
	{
		// 마네킹
		//Mannequin* mannequin = new Mannequin();
		//{
		//	BoxCollider* collider = new BoxCollider();
		//	collider->SetSize({ 100, 220 });
		//	collider->SetCollisionLayer(CLT_MANNEQUIN);
		//	collider->RemoveCollisionFlagLayerAll();
		//	GET_SINGLE(CollisionManager)->AddCollider(collider);
		//	mannequin->AddComponent(collider);
		//}
		//mannequin->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Mannequin"));
		//mannequin->SetTransparent(true);
		////mannequin->SetLayer(LAYER_BACKGROUND);
		//mannequin->SetPos({ 1000, 300 });
		//AddActor(mannequin);
	}
// 	{
// 		Pinocchio* pino = new Pinocchio();
// 		{
// 			{
// 				BoxCollider* collider = new BoxCollider();
// 				collider->SetSize({ 100, 220 });
// 				collider->SetCollisionLayer(CLT_PINO);
// 				collider->RemoveCollisionFlagLayerAll();
// 				GET_SINGLE(CollisionManager)->AddCollider(collider);
// 				pino->AddComponent(collider);
// 			}
// 			{
// 				BoxCollider* checkBox = new BoxCollider();
// 				checkBox->SetSize({ 800,200 });
// 				//checkBox->SetTrigger(false);
// 				checkBox->SetCollisionLayer(CLT_TRIGGER);	// 범위체크용 콜라이더는 반드시 모든 충돌을 꺼준 후 충돌을 체크 할 레이어만 켜줄 것? 그리고 Trigger를 켜주어야 함
// 				checkBox->RemoveCollisionFlagLayerAll();
// 				checkBox->AddCollisionFlagLayer(CLT_OBSTACLES);
// 				checkBox->SetTrigger(true);
// 				checkBox->SetPos({ 0, 0 });
// 				GET_SINGLE(CollisionManager)->AddCollider(checkBox);
// 				pino->AddComponent(checkBox);
// 			}
// 			pino->SetPos({ 1700, 300 });
// 			AddActor(pino);
// 		}
// 	}
// 	dollcheck = new DollCheck();
// 
// 	
// 	{
// 		// 인형
// 		Doll* doll = new Doll();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 100, 150 });
// 			collider->SetCollisionLayer(CLT_INTERACTIONABLE);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 			//collider->AddCollisionFlagLayer(CLT_TRIGGER2);
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			doll->AddComponent(collider);
// 			doll->SetPos({ 300, 400 });
// 		}
// 		doll->SetInteractionType(InteractionType::Doll);
// 		doll->SetDollID(C);
// 		//AddActor(doll);
// 		dollcheck->AddDoll(doll);
// 	}
// 	{
// 		// 인형
// 		Doll* doll = new Doll();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 100, 150 });
// 			collider->SetCollisionLayer(CLT_INTERACTIONABLE);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 			//collider->AddCollisionFlagLayer(CLT_TRIGGER2);
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			doll->AddComponent(collider);
// 			doll->SetPos({ 600, 400 });
// 		}
// 		doll->SetInteractionType(InteractionType::Doll);
// 		doll->SetDollID(A);
// 		//AddActor(doll);
// 		dollcheck->AddDoll(doll);
// 	}
// 	{
// 		// 인형
// 		Doll* doll = new Doll();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 100, 150 });
// 			collider->SetCollisionLayer(CLT_INTERACTIONABLE);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 			//collider->AddCollisionFlagLayer(CLT_TRIGGER2);
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			doll->AddComponent(collider);
// 			doll->SetPos({ 900, 400 });
// 		}
// 		doll->SetInteractionType(InteractionType::Doll);
// 		doll->SetDollID(B);
// 		//AddActor(doll);
// 		dollcheck->AddDoll(doll);
// 	}
// 	{
// 		// 인형
// 		Doll* doll = new Doll();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 100, 150 });
// 			collider->SetCollisionLayer(CLT_INTERACTIONABLE);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 			//collider->AddCollisionFlagLayer(CLT_TRIGGER2);
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			doll->AddComponent(collider);
// 			doll->SetPos({ 1200, 400 });
// 		}
// 		doll->SetInteractionType(InteractionType::Doll);
// 		doll->SetDollID(D);
// 		//AddActor(doll);
// 		dollcheck->AddDoll(doll);
// 	}
// 
// 	for (int32 i = 0; i < 4; i++)
// 	{
// 		AddActor(dollcheck->GetDoll(i));
// 	}

	{
		Light* light = new Light();
		//light->SetSprite(sprite);

		light->SetLayer(LAYER_BACKGROUND);
		GET_SINGLE(SceneManager)->SetLight(light);

		//const Vec2Int size = sprite->GetSize();
		//light->SetPos(Vec2(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2)));

		AddActor(light);
	}


// 	{
// 		// Piece
// 		Item* piece = new Item();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 48,20 });
// 			collider->SetCollisionLayer(CLT_ITEM);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			piece->AddComponent(collider);
// 			piece->SetPos({ 600,100 });
// 		}
// 		piece->SetItemType(ItemType::Piece);
// 		piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece1"));
// 		piece->SetTransparent(true);
// 		AddActor(piece);
// 	}
// 	{
// 		// Piece
// 		Item* piece = new Item();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 48,20 });
// 			collider->SetCollisionLayer(CLT_ITEM);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			piece->AddComponent(collider);
// 			piece->SetPos({ 700,100 });
// 		}
// 		piece->SetItemType(ItemType::Piece);
// 		piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece2"));
// 		piece->SetTransparent(true);
// 		AddActor(piece);
// 	}
// 	{
// 		// Piece
// 		Item* piece = new Item();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 48,20 });
// 			collider->SetCollisionLayer(CLT_ITEM);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			piece->AddComponent(collider);
// 			piece->SetPos({ 750,100 });
// 		}
// 		piece->SetItemType(ItemType::Piece);
// 		piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece3"));
// 		piece->SetTransparent(true);
// 		AddActor(piece);
// 	}
// 	{
// 		// Piece
// 		Item* piece = new Item();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 48,20 });
// 			collider->SetCollisionLayer(CLT_ITEM);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			piece->AddComponent(collider);
// 			piece->SetPos({ 790,100 });
// 		}
// 		piece->SetItemType(ItemType::Piece);
// 		piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece4"));
// 		piece->SetTransparent(true);
// 		AddActor(piece);
// 	}
// 	{
// 		// Piece
// 		Item* piece = new Item();
// 		{
// 			BoxCollider* collider = new BoxCollider();
// 			collider->SetSize({ 48,20 });
// 			collider->SetCollisionLayer(CLT_ITEM);
// 			collider->RemoveCollisionFlagLayerAll();
// 			collider->AddCollisionFlagLayer(CLT_TRIGGER);
// 
// 
// 			GET_SINGLE(CollisionManager)->AddCollider(collider);
// 
// 			piece->AddComponent(collider);
// 			piece->SetPos({ 800,100 });
// 		}
// 		piece->SetItemType(ItemType::Piece);
// 		piece->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece5"));
// 		piece->SetTransparent(true);
// 		AddActor(piece);
// 	}
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
			//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key"), US_Key);
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
			//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key"), US_Key);
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
			//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Key"), US_Key);
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
	}
	{
		UISprite* ui = new UISprite();
	}
	{
		// UI test
		Button* ui = new Button();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"),BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"),BS_Clicked);

		ui->SetPos({ 200,200 });
		_uis.push_back(ui);
	}
	{
		TestPanel* ui = new TestPanel();
		_uis.push_back(ui);
	}


	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	//dollcheck->Tick();
	/*if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::O))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Tilemap\\Tilemap01.txt");
	}
	*/
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

