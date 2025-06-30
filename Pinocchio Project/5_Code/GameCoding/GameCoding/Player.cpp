#include "pch.h"
#include "Player.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

#include "Scene.h"
#include "Flipbook.h"
#include "Utils.h"
#include "CameraComponent.h"
#include "BoxCollider.h"
#include "Item.h"
#include "Key.h"
#include "Door.h"
#include "Closet.h"
#include "Obstacle.h"
#include "Trap.h"
#include "Mannequin.h"
#include "Interactionable.h"
#include "Doll.h"
#include "UIManager.h"
#include "Hall.h"
#include "GameScene.h"
#include "StrongBox.h"

// Actor
#include "Room.h"
#include "Stage.h"
Player::Player()
{
	_flipbookUp = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveUp");
	_flipbookDown = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveDown");
	//_flipbookLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveLeft");
	//_flipbookRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveRight");
	_flipbookRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_CharacterRight");
	_flipbookLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_CharacterLeft");
	_flipbookIdleRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_CharacterIdleRight");
	_flipbookIdleLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_CharacterIdleLeft");
	/*CameraComponent* camera = new CameraComponent();
	AddComponent(camera);*/
}

Player::~Player()
{

}

void Player::BeginPlay()
{
	Super::BeginPlay();

	SetFlipbook(_flipbookRight);
	SetPlayerDir(PD_RIGHT);
	SetPlayerState(PlayerState::Move);

	_stat.speed = 200;

	// Item 초기화
	_pieceCount = 0;

	_hasCheese = false;

	for (int i = 0; i < 5; i++)
	{
		_key[i] = false;
	}
}

void Player::Tick()
{
	Super::Tick();

	if (((GameScene*)GetMyScene()->isTabToggle))
	{
		//Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		//GET_SINGLE(SceneManager)->AddLightRegion((int32)_pos.x - 270 - ((int32)cameraPos.x - GWinSizeX / 2), 300);

		return;
	}

	if (_pos.x < 50)
	{
		_pos.x = 50;
	}
	else if (_pos.x > 4750)
	{
		_pos.x = 4750;
	}

	if (GetIsAlive() == false)
		return;
	//_currentSpeed = {};

	//////////////// CHEAT /////////////////
	if (GET_SINGLE(InputManager)->GetButton(KeyType::N))
	{
		switch(_pieceCount)
		{
			case 0:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE1);
				break;
			case 1:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE2);
				break;
			case 2:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE3);
				break;
			case 3:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE4);
				break;
			case 4:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE5);
				break;
			default:
				break;
		}
		_pieceCount++;
		if (_pieceCount >= 5)
			_pieceCount = 5;

	}


	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f)
		return;
	float range = 5.f;
	switch (_playerState)
	{
	case PlayerState::Idle:
		break;
	case PlayerState::Move:
	{
		//if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A))
		//{
		//	float speed = _moveSpeed;
		//	if (_height != 0)
		//		speed = 0.f;

		//	_pos.x -= _currentSpeed.x = speed * deltaTime;
		//	SetFlipbook(_flipbookLeft);
		//	SetPlayerDir(PD_LEFT);

		//	if (!_isWalking)
		//	{
		//		//_isWalking = true;
		//		GET_SINGLE(SoundManager)->LoadSound(L"Walk", "Sounds\\Walk\\walk short.wav", SoundType::SFX);
		//		GET_SINGLE(SoundManager)->PlaySFXSound(L"Walk", 1);
		//		_walkingTimer = 1.5f; // 재생 중지 시간 설정
		//	}
		//}
		//else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
		//{
		//	float speed = _moveSpeed;
		//	if (_height != 0)
		//		speed = 0.f;

		//	_pos.x += _currentSpeed.x = speed * deltaTime;
		//	SetFlipbook(_flipbookRight);
		//	SetPlayerDir(PD_RIGHT);

		//	if (!_isWalking)
		//	{
		//		GET_SINGLE(SoundManager)->LoadSound(L"Walk", "Sounds\\Walk\\walk short.wav", SoundType::SFX);
		//		GET_SINGLE(SoundManager)->PlaySFXSound(L"Walk", 1);
		//		//_isWalking = true;
		//		_walkingTimer = 2.0f; // 재생 중지 시간 설정
		//	}
		//}
		//else
		//{
		//	if (_playerDir == PD_RIGHT)
		//		SetFlipbook(_flipbookIdleRight);
		//	else
		//		SetFlipbook(_flipbookIdleLeft);

		//	_isWalking = false;
		//}

		//if (_isWalking)
		//{
		//	_walkingTimer -= deltaTime; // 타이머 감소

		//	if (_walkingTimer <= 0.f)
		//	{
		//		GET_SINGLE(SoundManager)->PauseSFXSound(1); // 효과음 일시 중지
		//		_isWalking = false;
		//	}
		//}
		// pause 버전
		//=====
		// original 버전
		//bool _isWalking=false;
		if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
		{

			//GET_SINGLE(SoundManager)->PlaySFXSound(L"Walk", 1);
			//_isWalking = true;
			GET_SINGLE(SoundManager)->LoadSound(L"Walk", "Sounds\\Walk\\walk short.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Walk", 1);

			// 이동 로직 추가
			float speed = _moveSpeed;
			// 1층 이상일때 방향만 바꾸고 움직이지 않게
			if (_height != 0)
				speed = 0.f;

			_pos.x -= _currentSpeed.x = speed * deltaTime;
			SetFlipbook(_flipbookLeft);
			SetPlayerDir(PD_LEFT);
		}
		else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
		{

			//GET_SINGLE(SoundManager)->PlaySFXSound(L"Walk", 1);
			//_isWalking = true;
			GET_SINGLE(SoundManager)->LoadSound(L"Walk", "Sounds\\Walk\\walk short.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Walk", 1);

			// 이동 로직 추가
			float speed = _moveSpeed;
			if (_height != 0)
				speed = 0.f;

			_pos.x += _currentSpeed.x = speed * deltaTime;
			SetFlipbook(_flipbookRight);
			SetPlayerDir(PD_RIGHT);
		}
		else
		{
			// IDLE
			//_isWalking = false;

			// IDLE
			if (_playerDir == PD_RIGHT)
				SetFlipbook(_flipbookIdleRight);
			else
				SetFlipbook(_flipbookIdleLeft);
		}
	}


	break;
	case PlayerState::Climb:
		break;
	case PlayerState::Hide:

		break;

	case PlayerState::AutoMove:
	{
		if (_pos.x <= _destinationSide.x + range && _pos.x >= _destinationSide.x - range)
		{
			// 현재의 위치부터 상자의 윗부분의 위치까지의 단위벡터를 구함.
			_moveDir = (_destinationTop - _pos);
			_moveDir.Normalize();

			//SetPlayerState(PlayerState::AutoClimb);


			// 2번째 방법:
			// 플레이어의 포지션은 가만히 냅두고 애니메이션 자체에서 움직임. 애니메이션이 끝나면 강제로 위치를 목표했던 위치로 바꿈
			// 애니메이션이 끝나는지를 알고 싶으면 FlipbookActor._idx == FlipbookActor.GetInfo().end를 통해 애니메이션이 끝났는지를 알 수 있음

			//SetFlipbook(_flipbookClimb);

			// 애니메이션 처음부터 재생
			_idx = 0;
			SetPlayerState(PlayerState::AutoClimb);

			break;
		}
		// PlayerAutoDir 필요 없는듯 함.
		/*if(GetPlayerAutoDir() == PlayerAutoDir::Right)
		{
			SetPlayerDir(PD_LEFT);
			SetFlipbook(_flipbookLeft);
		}
		else
		{
			SetPlayerDir(PD_RIGHT);
			SetFlipbook(_flipbookRight);
		}*/
		if (_pos.x <= _destinationSide.x)
		{
			SetPlayerDir(PD_RIGHT);
			SetFlipbook(_flipbookRight);
		}
		else
		{
			SetPlayerDir(PD_LEFT);
			SetFlipbook(_flipbookLeft);
		}
		_pos.x += _moveDir.x * _stat.speed * deltaTime;
	}
	break;


	case PlayerState::AutoClimb:
	{
		// 1번 방법
		/*if ((_pos.x <= _destinationTop.x + range && _pos.x >= _destinationTop.x - range)
			&& (_pos.y <= _destinationTop.y + range && _pos.y >= _destinationTop.y - range))
		{
			SetPlayerState(PlayerState::Move);
			break;
		}
		if(GetPlayerAutoDir() == PlayerAutoDir::Right)
		{
			SetPlayerDir(PD_RIGHT);
			SetFlipbook(_flipbookRight);
		}
		else
		{
			SetPlayerDir(PD_LEFT);
			SetFlipbook(_flipbookLeft);
		}
		_pos.x += _moveDir.x * _stat.speed * deltaTime;
		_pos.y += _moveDir.y * _stat.speed * deltaTime;*/

		// 2번 방법
		if (_idx == GetFlipbook()->GetInfo().end)
		{
			_pos = _destinationTop;
			//SetFlipbook(_flipbookRight);
			//SetPlayerState(PlayerState::OnBox);
			SetPlayerState(PlayerState::Move);
		}
	}
	break;

	case PlayerState::AutoFall:
	{
		if ((_pos.x <= _destinationTop.x + range && _pos.x >= _destinationTop.x - range)
			&& (_pos.y <= _destinationTop.y + range && _pos.y >= _destinationTop.y - range))
		{
			SetPlayerState(PlayerState::Move);
			break;
		}

		if (GetPlayerAutoDir() == PlayerAutoDir::Right)
		{
			_pos.x += _stat.speed * deltaTime;
			_pos.y += _stat.speed * deltaTime;
			SetPlayerDir(PD_RIGHT);
		}
		else
		{
			_pos.x -= _stat.speed * deltaTime;
			_pos.y += _stat.speed * deltaTime;
			SetPlayerDir(PD_LEFT);
		}

	}
	break;

	case PlayerState::OnBox:
		break;

	default:
		break;
	}

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	if (_height == 0)
	{
		GET_SINGLE(SceneManager)->AddLightRegion((int32)_pos.x - 270 - ((int32)cameraPos.x - GWinSizeX / 2), 400);
	}
	else if (_height == 1)
	{
		GET_SINGLE(SceneManager)->AddLightRegion((int32)_pos.x - 270 - ((int32)cameraPos.x - GWinSizeX / 2), 272);
	}
	else if (_height == 2)
	{
		GET_SINGLE(SceneManager)->AddLightRegion((int32)_pos.x - 270 - ((int32)cameraPos.x - GWinSizeX / 2), 144);
	}

	// 	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::O))
	// 	{
	// 		GET_SINGLE(SceneManager)->GetCurrentScene()->SaveData("playerX", std::to_string(_pos.x));
	// 		GET_SINGLE(SceneManager)->GetCurrentScene()->SaveData();
	// 	}
}

void Player::Render(HDC hdc)
{
	if (GetIsAlive() == false)
		return;
	// 플레이어가 숨을 경우 렌더하지 않음.
	if (GetPlayerState() == PlayerState::Hide)
		return;
	Super::Render(hdc);

	wstring str2 = std::format(L"pos {0}, {1}", (float)_pos.x, _pos.y);
	::TextOut(hdc, 10, 650 + 1 * 20, str2.c_str(), static_cast<int32>(str2.size()));
	wstring str1 = std::format(L"destination Side {0}", (float)_destinationSide.x);
	::TextOut(hdc, 10, 650 + 2 * 20, str1.c_str(), static_cast<int32>(str1.size()));
	wstring str3 = std::format(L"destination Top {0}, {1}", (float)_destinationTop.x, (float)_destinationTop.y);
	::TextOut(hdc, 10, 650 + 3 * 20, str3.c_str(), static_cast<int32>(str3.size()));
	wstring str5 = std::format(L"Height {0}", _height);
	::TextOut(hdc, 10, 650 + 5 * 20, str5.c_str(), static_cast<int32>(str5.size()));

	wstring str4 = std::format(L"IDLE");

	switch (_playerState)
	{
	case PlayerState::Idle:
		str4 = L"IDLE";
		break;
	case PlayerState::Move:
		str4 = L"Move";
		break;
	case PlayerState::Climb:
		str4 = L"Climb";
		break;
	case PlayerState::Hide:
		str4 = L"Hide";
		break;
	case PlayerState::AutoMove:
		str4 = L"AutoMove";
		break;
	case PlayerState::AutoClimb:
		str4 = L"AutoClimb";
		break;
	case PlayerState::AutoFall:
		str4 = L"AutoFall";
		break;
	default:
		break;
	}
	::TextOut(hdc, 10, 650 + 4 * 20, str4.c_str(), static_cast<int32>(str4.size()));
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (((GameScene*)GetMyScene()->isTabToggle))
	{
		return;
	}

	// 주의 : Collider를 BoxCollider만 받아온다는 가정하에 아래처럼 캐스팅을 함.
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	// 만일을 대비해 다른 타입일경우 리턴
	if (b1 == nullptr || b2 == nullptr)
		return;

	// 하나라도 isTrigger일 경우 밀어내지 않음.
	if (b1->GetTrigger() || b2->GetTrigger())
	{
		return;
	}

	//AdjustCollisionPos(b1, b2);

	if (other->GetCollisionLayerType() == CLT_GROUND)
	{
		//_playerState = PS_IDLE;
		if (GetPlayerState() == PlayerState::Hide)
			return;
		SetPlayerState(PlayerState::Move);
	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	if (((GameScene*)GetMyScene()->isTabToggle))
	{
		return;
	}

	// 주의 : Collider를 BoxCollider만 받아온다는 가정하에 아래처럼 캐스팅을 함.
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	// 만일을 대비해 다른 타입일경우 리턴
	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayerType() == CLT_GROUND)
	{
		//_playerState = PS_JUMP;
		if (GetPlayerState() == PlayerState::Hide)
			return;
		SetPlayerState(PlayerState::Move);
		//_speed.y = 500;
	}

	if (b1->GetCollisionLayerType() == CLT_TRIGGER2 && b2->GetCollisionLayerType() == CLT_MANNEQUIN)
	{
		Mannequin* mannequin = dynamic_cast<Mannequin*>(b2->GetOwner());
		mannequin->SetActive(this);

		//  마네킹의 콜라이더를 끄긴 하는데 혹시 나중에 수정 가능성 있음
		b1->RemoveCollisionFlagLayer(CLT_MANNEQUIN);
	}
}

void Player::OnComponentOverlap(Collider* collider, Collider* other)
{
	if (((GameScene*)GetMyScene()->isTabToggle))
	{
		return;
	}

	// 주의 : Collider를 BoxCollider만 받아온다는 가정하에 아래처럼 캐스팅을 함.
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	// 만일을 대비해 다른 타입일경우 리턴
	if (b1 == nullptr || b2 == nullptr)
		return;

	// 자기 자신이면 리턴
	if (other->GetCollisionLayerType() == CLT_PLAYER || other->GetCollisionLayerType() == CLT_TRIGGER
		|| other->GetCollisionLayerType() == CLT_TRIGGER2 || other->GetCollisionLayerType() == CLT_TRIGGER3
		|| other->GetCollisionLayerType() == CLT_TRIGGER4)
		return;

	if (GetPlayerState() == PlayerState::AutoMove || GetPlayerState() == PlayerState::AutoClimb
		|| GetPlayerState() == PlayerState::AutoFall)
		return;

	switch (other->GetCollisionLayerType())
	{
	case CLT_INTERACTIONABLE:
	{
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
		{
			Interactionable* interactionable = dynamic_cast<Interactionable*>(other->GetOwner());

			if (interactionable == nullptr)
				return;
			switch (interactionable->GetInteractionType())
			{
			case InteractionType::None:
				break;
			case InteractionType::LittlePino:
			{
				static int32 textNum = 0;
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;
				if (textNum == 0)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino1");
				}
				else if (textNum == 1)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino2");
				}
				else if (textNum == 2)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino3");
				}
				else if (textNum == 3)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino4");
				}
				else if (textNum == 4)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino5");
				}
				else if (textNum == 5)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino6");
				}
				else if (textNum == 6)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino7");
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->_restRoomKey->isActive = true;
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->_restRoomKey->_myCollider->SetActive(true);

					Interactionable* littlePino = interactionable;
					littlePino->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"LittlePinoNose"));
					((GameScene*)GetMyScene())->_isLittleTakingEnd = true;
				}
				else if (textNum == 7)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino8");
				}
				else if (textNum == 8)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("LittlePino9");
				}
				textNum++;
			}
			break;

			case InteractionType::Doll:
			{
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;
				int a = 3;
				// TODO : 각자의 Doll
				Doll* doll = dynamic_cast<Doll*>(interactionable);
				doll->SetIsActive(true);
			}
			break;

			case InteractionType::Switch:
			{
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;
				if (((GameScene*)GetMyScene())->_isRestRoomClear)
				{
					static bool isActivatedOnce = false;
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Switch_Conneted");
					// TODO : RoomClear
					((GameScene*)GetMyScene())->isUseSwitch = true;
					for (int i = 0; i < 5; i++)
					{
						((GameScene*)GetMyScene())->_roomVector[0]->_stages[i]->isVisited = true;

						GET_SINGLE(ResourceManager)->LoadTexture(L"Stage6", L"Sprite\\Map\\restRoom\\6.bmp");
						GET_SINGLE(ResourceManager)->CreateSprite(L"Stage6", GET_SINGLE(ResourceManager)->GetTexture(L"Stage6"));
						
						//스위치 온오프 사운드 추가
						GET_SINGLE(SoundManager)->LoadSound(L"Switch", "Sounds\\ETC\\switch on-off (wav).wav", SoundType::SFX);
						GET_SINGLE(SoundManager)->PlaySFXSound(L"Switch", 5);
						
						((GameScene*)GetMyScene())->_roomVector[0]->_stages[4]->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Stage6"));

						if (!isActivatedOnce)
						{
							((GameScene*)GetMyScene())->_wareHouseKey->_myCollider->SetActive(true);
							((GameScene*)GetMyScene())->_wareHouseKey->isActive = true;

							((GameScene*)GetMyScene())->_piece1->_myCollider->SetActive(true);
							((GameScene*)GetMyScene())->_piece1->isActive = true;
						}
					}
					isActivatedOnce = true;
				}
				else
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Switch_NoConneted");
				}
			}
			break;
			case InteractionType::Safe:
			{
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;
				StrongBox* safe = dynamic_cast<StrongBox*>(other->GetOwner());
				if (safe->GetStrongBoxState() == StrongBoxState::Closed)
				{
					static bool isActivatedOnceSafe = false;
					// TODO : 비밀번호 생성
					
					safe->SetActive();
					if (!isActivatedOnceSafe)
					{
						((GameScene*)GetMyScene())->_workRoomKey->_myCollider->SetActive(true);
						((GameScene*)GetMyScene())->_workRoomKey->isActive = true;
						isActivatedOnceSafe = true;
					}
				}
			}
				break;
			case InteractionType::Zepeto:
			{
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;
				Interactionable* zepeto = dynamic_cast<Interactionable*>(other->GetOwner());
				static bool isActivatedOnceZepeto = false;

				if (!isActivatedOnceZepeto)
				{
					((GameScene*)GetMyScene())->_piece4->_myCollider->SetActive(true);
					((GameScene*)GetMyScene())->_piece4->isActive = true;
					isActivatedOnceZepeto = true;
				}
			}
				break;

			case InteractionType::Ending:
			{
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;

				// 엔딩 
				if (_pieceCount == 5)
				{
					// TODO : 엔딩!
					//GET_SINGLE(SceneManager)->ChangeScene(SceneType::EndingScene);
					GetMyScene()->_sceneType = SceneType::EndingScene;
					//int a = 3;
				}
			}
			break;
			case InteractionType::Deadbody:
			{
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;

				// TODO : 시체
				GameScene* gameScene = ((GameScene*)GetMyScene());
				if (gameScene->_isRestRoomClear && gameScene->isUseSwitch)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Toilet_Conneted");
				}
				else
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Toilet_NoConneted");
				}
			}
			break;
			case InteractionType::Pino_interaction:
			{
				if (collider->GetCollisionLayerType() != CLT_TRIGGER)
					return;

				// TODO : 괴물 피노키오 화장실
				GameScene* gameScene = ((GameScene*)GetMyScene());
				if (gameScene->_isRestRoomClear && gameScene->isUseSwitch)
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Pino_Conneted");
				}
				else
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Pino_NoConneted");
				}
			}
			default:
				break;

			}
		}
		return;
	}
	break;


	case CLT_OBSTACLES:
	{
		bool Return = false;
		if (collider->GetCollisionLayerType() == CLT_TRIGGER4)
		{
			Obstacle* obstacles = dynamic_cast<Obstacle*>(other->GetOwner());
			if (obstacles->GetObstacleLevel() == ObstacleLevel::Level1)
			{
				int a = 3;
			}
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
			{
				if (obstacles->GetObstacleLevel() != ObstacleLevel::Level1)
				{
					return;
				}

				if (_playerDir == PD_RIGHT)
				{
					// 오른쪽을 보고 있는데 장애물이 나보다 왼쪽에 있을 경우
					if (obstacles->GetPos().x < _pos.x)
					{
						return;
					}
					Vec2 posRight = obstacles->GetPosInfo(OPI_RIGHT);
					Vec2 posTop = obstacles->GetPosInfo(OPI_TOP);
					_destinationSide = posTop;
					//_destinationTop = posRight;
					_destinationTop = posTop;

					_moveDir = (_destinationSide - _pos);
					_moveDir.Normalize();

					//SetPlayerState(PlayerState::AutoMove);
					SetPlayerState(PlayerState::AutoClimb);

					if (obstacles->GetObstacleLevel() == ObstacleLevel::Level2 && obstacles->IsExistRight() == false)
					{
						// 2층에서 0층으로 바로 떨어질 경우 예외 처리
						_height -= 1;
					}
					else
					{
						_height--;
					}
					return;
				}
				else if (_playerDir == PD_LEFT)
				{
					// 왼쪽을 보고 있는데 장애물이 나보다 오른쪽에 있을 경우
					if (obstacles->GetPos().x > _pos.x)
					{
						return;
					}

					Vec2 posLeft = obstacles->GetPosInfo(OPI_LEFT);
					Vec2 posTop = obstacles->GetPosInfo(OPI_TOP);
					_destinationSide = posTop;
					//_destinationTop = posLeft;
					_destinationTop = posTop;

					_moveDir = (_destinationSide - _pos);
					_moveDir.Normalize();

					//SetPlayerState(PlayerState::AutoMove);
					SetPlayerState(PlayerState::AutoClimb);

					if (obstacles->GetObstacleLevel() == ObstacleLevel::Level2 && obstacles->IsExistLeft() == false)
					{
						// 2층에서 0층으로 바로 떨어질 경우 예외 처리
						_height -= 1;
					}
					else
					{
						_height--;
					}
					return;
				}
			}
			return;
		}

		// 상자의 위치 가져오는 용도
		if (collider->GetCollisionLayerType() == CLT_TRIGGER2)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
			{
				// 오른쪽을 보고 있으면 상자의 왼쪽과 위의 위치를 가져옴.
				if (_playerDir == PD_RIGHT)
				{
					Obstacle* obstacles = dynamic_cast<Obstacle*>(other->GetOwner());
					// 만약 상자의 x 위치가 나의 x 위치보다 작을 경우 상자는 오른쪽에 있는 것이 아니게되니 함수를 종료
					if (obstacles->GetPos().x < _pos.x)
						return;

					// 상자가 2층이고 왼쪽 아래에 상자가 없으면 바로 못올라가게 예외처리
					if (obstacles->GetObstacleLevel() == ObstacleLevel::Level2)
					{
						if (_height == 1)
						{
							// 넘어가기
						}
						else if (obstacles->IsExistLeft() == false)
						{
							return;
						}
					}

					Vec2 posLeft = obstacles->GetPosInfo(OPI_LEFT);
					Vec2 posTop = obstacles->GetPosInfo(OPI_TOP);

					_destinationSide = posLeft;
					_destinationTop = posTop;

					_moveDir = (_destinationSide - _pos);
					_moveDir.Normalize();

					SetPlayerState(PlayerState::AutoClimb);

					SetPlayerAutoDir(PlayerAutoDir::Right);

					_height++;
					return;
				}
				// 왼쪽을 보고 있으면 상자의 오른쪽과 위의 위치를 가져옴.
				else if (_playerDir == PD_LEFT)
				{
					Obstacle* obstacles = dynamic_cast<Obstacle*>(other->GetOwner());
					// 만약 상자의 x 위치가 나의 x 위치보다 클 경우 상자는 왼쪽에 있는 것이 아니게되니 함수를 종료
					if (obstacles->GetPos().x > _pos.x)
						return;

					// 상자가 2층이고 왼쪽 아래에 상자가 없으면 바로 못올라가게 예외처리
					if (obstacles->GetObstacleLevel() == ObstacleLevel::Level2)
					{
						if (_height == 1)
						{
							// 넘어가기
						}
						else if (obstacles->IsExistRight() == false)
						{
							return;
						}
					}

					Vec2 posRight = obstacles->GetPosInfo(OPI_RIGHT);
					Vec2 posTop = obstacles->GetPosInfo(OPI_TOP);

					_destinationSide = posRight;
					_destinationTop = posTop;

					_moveDir = (_destinationSide - _pos);
					_moveDir.Normalize();

					//SetPlayerState(PlayerState::AutoMove);
					SetPlayerState(PlayerState::AutoClimb);
					SetPlayerAutoDir(PlayerAutoDir::Left);

					_height++;
					return;
				}
			}
			return;
		}


		// 떨어져야 하는 경우
		if (collider->GetCollisionLayerType() == CLT_TRIGGER3)
		{
			Obstacle* obstacles = dynamic_cast<Obstacle*>(other->GetOwner());
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
			{
				if (_playerDir == PD_RIGHT)
				{
					Vec2 posRight = obstacles->GetPosInfo(OPI_RIGHT);
					Vec2 posTop = obstacles->GetPosInfo(OPI_TOP);
					_destinationSide = posTop;
					_destinationTop = posRight;

					_moveDir = (_destinationSide - _pos);
					_moveDir.Normalize();

					SetPlayerState(PlayerState::AutoMove);
					SetPlayerAutoDir(PlayerAutoDir::Right);

					if (obstacles->GetObstacleLevel() == ObstacleLevel::Level2 && obstacles->IsExistRight() == false)
					{
						// 2층에서 0층으로 바로 떨어질 경우 예외 처리
						_height -= 2;
					}
					else
					{
						_height--;
					}
					return;
				}
				else if (_playerDir == PD_LEFT)
				{
					Vec2 posLeft = obstacles->GetPosInfo(OPI_LEFT);
					Vec2 posTop = obstacles->GetPosInfo(OPI_TOP);
					_destinationSide = posTop;
					_destinationTop = posLeft;

					_moveDir = (_destinationSide - _pos);
					_moveDir.Normalize();

					SetPlayerState(PlayerState::AutoMove);
					SetPlayerAutoDir(PlayerAutoDir::Left);

					if (obstacles->GetObstacleLevel() == ObstacleLevel::Level2 && obstacles->IsExistLeft() == false)
					{
						// 2층에서 0층으로 바로 떨어질 경우 예외 처리
						_height -= 2;
					}
					else
					{
						_height--;
					}
					return;
				}
			}
			return;
		}


		if (b1->GetTrigger() || b2->GetTrigger())
		{
			// 움직일 수 없으면 리턴

			if (((Obstacle*)other->GetOwner())->GetObstacleState() == ObstacleState::Unmovable)
			{
				return;
			}
			MoveOtherActor(other);
			return;
		}
	}
	break;
	case CLT_GROUND:
		break;
	case CLT_WALL:
		break;

	case CLT_TRIGGER:
		return;
	case CLT_TRIGGER2:
		return;
	case CLT_TRIGGER3:
		return;
	case CLT_TRIGGER4:
		return;

	case CLT_ITEM: {
		//GET_SINGLE(SceneManager)->GetCurrentScene()->RemoveActor(other->GetOwner());

		Item* item = dynamic_cast<Item*>(other->GetOwner());
		switch (item->GetItemType())
		{
		case ItemType::None:
			break;
		case ItemType::Key_red:
		{
			((GameScene*)GetMyScene())->_isGetRestRoomKey = true;
			//키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			Key* key = dynamic_cast<Key*>(item);
			AddKey(key->GetKeyID());

			//key->RemoveComponentAll();
			GET_SINGLE(UIManager)->AddItem(US_Key_red);

			// CollisionManager의 콜라이더를 삭제.
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			// 렌더 끄기
			key->isActive = false;
			// 콜라이더 끄기
			other->SetActive(false);
			break;
		}
		case ItemType::Key_brown:
		{
			//키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("RestRoom_GetKey");
			Key* key = dynamic_cast<Key*>(item);
			AddKey(key->GetKeyID());

			//key->RemoveComponentAll();
			GET_SINGLE(UIManager)->AddItem(US_Key_brown);

			// CollisionManager의 콜라이더를 삭제.
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			// 렌더 끄기
			key->isActive = false;
			// 콜라이더 끄기
			other->SetActive(false);
			break;
		}
		case ItemType::Key_yellow:
		{
			//키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("WareRoom_GetKey");
			Key* key = dynamic_cast<Key*>(item);
			AddKey(key->GetKeyID());

			//key->RemoveComponentAll();
			GET_SINGLE(UIManager)->AddItem(US_Key_yellow);

			// CollisionManager의 콜라이더를 삭제.
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			// 렌더 끄기
			key->isActive = false;
			// 콜라이더 끄기
			other->SetActive(false);
			break;
		}
		case ItemType::Key_green:
		{
			//키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			Key* key = dynamic_cast<Key*>(item);
			AddKey(key->GetKeyID());

			//key->RemoveComponentAll();
			GET_SINGLE(UIManager)->AddItem(US_Key_green);

			// CollisionManager의 콜라이더를 삭제.
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			// 렌더 끄기
			key->isActive = false;
			// 콜라이더 끄기
			other->SetActive(false);
			break;
		}
		case ItemType::Key_blue:
		{
			//키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			Key* key = dynamic_cast<Key*>(item);
			AddKey(key->GetKeyID());

			//key->RemoveComponentAll();
			GET_SINGLE(UIManager)->AddItem(US_Key_blue);

			// CollisionManager의 콜라이더를 삭제.
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			// 렌더 끄기
			key->isActive = false;
			// 콜라이더 끄기
			other->SetActive(false);
			break;
		}
		case ItemType::Key_purple:
		{
			//키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			Key* key = dynamic_cast<Key*>(item);
			AddKey(key->GetKeyID());

			//key->RemoveComponentAll();
			GET_SINGLE(UIManager)->AddItem(US_Key_purple);

			// CollisionManager의 콜라이더를 삭제.
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			// 렌더 끄기
			key->isActive = false;
			// 콜라이더 끄기
			other->SetActive(false);
			break;
		}
		case ItemType::Key_white:
		{
			//키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			Key* key = dynamic_cast<Key*>(item);
			AddKey(key->GetKeyID());

			//key->RemoveComponentAll();
			GET_SINGLE(UIManager)->AddItem(US_Key_white);

			// CollisionManager의 콜라이더를 삭제.
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			// 렌더 끄기
			key->isActive = false;
			// 콜라이더 끄기
			other->SetActive(false);
			break;
		}

		case ItemType::Cheese:
		{
			//=키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			SetCheese(true);
			GET_SINGLE(UIManager)->AddItem(US_Cheese);
			GET_SINGLE(CollisionManager)->RemoveCollider(other);

			item->isActive = false;
			other->SetActive(false);
		}
		break;
		case ItemType::Piece:
		{
			//=키획득 사운드
			GET_SINGLE(SoundManager)->LoadSound(L"Item", "Sounds\\ETC\\item.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Item", 3);

			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("GetPaint");
			AddPiece();

			switch (GetPiece())
			{
			case 1:
				((GameScene*)GetMyScene())->_isGetPiece1 = true;
				GET_SINGLE(UIManager)->AddPiece(US_PIECE1);
				break;
			case 2:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE2);
				break;
			case 3:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE3);
				break;
			case 4:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE4);
				break;
			case 5:
				GET_SINGLE(UIManager)->AddPiece(US_PIECE5);
				break;
			}
			GET_SINGLE(CollisionManager)->RemoveCollider(other);
			item->isActive = false;
		}
		default:
			break;
		}
		// Item일 경우 충돌 처리 안하고 리턴
		return;
	}
				 break;
	case CLT_OBJECT:
		break;
	case CLT_DOOR:
	{
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
		{
			GET_SINGLE(SoundManager)->LoadSound(L"Opened", "Sounds\\Door\\door open.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Opened", 7);

			RoomCheck(other);
			_height = 0;

			// TODO : 룸넘버

		}
		return;
	}
	break;
	case CLT_CLOSET:
	{
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
		{
			Closet* closet = dynamic_cast<Closet*>(other);
			if (GetPlayerState() != PlayerState::Hide)
			{
				SetPlayerState(PlayerState::Hide);

				//옷장 들어갈때 효과음
				GET_SINGLE(SoundManager)->LoadSound(L"Closet", "Sounds\\Door\\closet (wav).wav", SoundType::SFX);
				GET_SINGLE(SoundManager)->PlaySFXSound(L"Closet", 7);
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);

			}
			else
			{
				SetPlayerState(PlayerState::Move);
			}
		}
		return;
	}
	break;
	case CLT_TRAP:
	{
		if (collider->GetCollisionLayerType() == CLT_TRIGGER2)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
			{
				if (HasCheese())
				{
					dynamic_cast<Trap*>(other->GetOwner())->SetActive(true);
					dynamic_cast<SpriteActor*>(other->GetOwner())->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"MouseTrapped"));
					GET_SINGLE(UIManager)->RemoveItem(US_Cheese);

					static bool isActivatedOnceTrap = false;

					if (!isActivatedOnceTrap)
					{
						
						((GameScene*)GetMyScene())->_piece3->_myCollider->SetActive(true);
						((GameScene*)GetMyScene())->_piece3->isActive = true;
						isActivatedOnceTrap = true;
					}

				}
				else
				{
					((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Trap_NoCheese");
				}
			}

			return;
		}


		// 닿으면 사망
		if (dynamic_cast<Trap*>(other->GetOwner())->IsActive() == false)
		{
			SetIsAlive(false);
		}
		return;
	}
	break;

	case CLT_PINO:
	{
		// 닿으면 사망
		SetIsAlive(false);
		return;
	}
	break;
	case CLT_MANNEQUIN:
	{
		// 만약 마네킹이 작동하고 있을경우 닿으면 사망

		if (dynamic_cast<Mannequin*>(other->GetOwner())->IsActive() == true)
		{
			SetIsAlive(false);
		}
	}
	default:
		return;
		break;
	}

	AdjustCollisionPos(b1, b2);
}

void Player::Jump()
{
	if (GetPlayerState() == PlayerState::Climb)
		return;
	//점프시 효과음
	GET_SINGLE(SoundManager)->LoadSound(L"Jump", "Sounds\\Jump\\jump scare 3.wav", SoundType::SFX);
	GET_SINGLE(SoundManager)->PlaySFXSound(L"Jump", 6);
	_speed.y = -500;
}

void Player::TickGravity()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 디버그 할 때 deltaTime이 튀는 현상 방지
	if (deltaTime > 0.1f)
		return;
	//

	if (GetPlayerState() == PlayerState::Idle)
		return;

	// 중력으로 벽을 뚫는 것 방지
	if (_speed.y > 800.f)
	{
		_pos.y += 0.1f;
		return;
	}

	_speed.y += _gravity * deltaTime;
	_pos.y += _speed.y * deltaTime;
}

// 충돌하였을 경우 밀어내는 함수 - 작동방식 ) 일단 이동 후 다음에 밀침
void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();

	RECT intersect = {};
	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;

		if (w > h)
		{
			if (intersect.top == r2.top)
			{
				pos.y -= h;
			}
			else
			{
				pos.y += h;
			}
		}
		else
		{
			if (intersect.left == r2.left)
			{
				pos.x -= w;
			}
			else
			{
				pos.x += w;
			}
		}
	}
	SetPos(pos);
}

void Player::MoveOtherActor(Collider* other)
{
	{
		canOtherBoxMove = true;
		Vec2 otherPos = other->GetOwner()->GetPos();
		_currentSpeed;
		_currentSpeed.y = 0.f;

		switch (_playerDir)
		{
		case PD_RIGHT:
			//상자밀기 효과음
			GET_SINGLE(SoundManager)->LoadSound(L"Push", "Sounds\\ETC\\push box.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Push", 6);
			if (otherPos.x < _pos.x)
			{
				return;
			}

			otherPos.x += _currentSpeed.x;
			break;
		case PD_LEFT:
			if (otherPos.x > _pos.x)
			{
				return;
			}
			otherPos.x -= _currentSpeed.x;
			break;
		}

		other->GetOwner()->SetPos(otherPos);
	}
}

bool Player::CheckKey(RoomNum roomNumber)
{
	// 현재 방의 정보를 불러왔을때 일치하는 키가 없을 경우
	if (!_key[(int32)roomNumber])
		return false;

	return true;
}

void Player::RoomCheck(Collider* other)
{
	Door* room = dynamic_cast<Door*>(other->GetOwner());

	if (!room->IsRoomOpen())
	{
		if ((CheckKey(room->GetRoomId())) && room->GetRoomId() == RoomNum::restRoom)
		{
			GET_SINGLE(SoundManager)->LoadSound(L"Opened", "Sounds\\Door\\door open.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Opened", 7);
			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("RestRoom_Key");
			room->OpenRoom();
			GET_SINGLE(UIManager)->RemoveItem(US_Key_red);
			GET_SINGLE(UIManager)->ShowStageInfo(RoomNum::restRoom);
		}
		else if ((CheckKey(room->GetRoomId())) && room->GetRoomId() == RoomNum::wareHouse)
		{
			GET_SINGLE(SoundManager)->LoadSound(L"Opened", "Sounds\\Door\\door open.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Opened", 7);
			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("WareRoom_Key");
			room->OpenRoom();
			GET_SINGLE(UIManager)->RemoveItem(US_Key_brown);
			GET_SINGLE(UIManager)->ShowStageInfo(RoomNum::wareHouse);
		}
		else if ((CheckKey(room->GetRoomId())) && room->GetRoomId() == RoomNum::kitchen)
		{
			GET_SINGLE(SoundManager)->LoadSound(L"Opened", "Sounds\\Door\\door open.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Opened", 7);
			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Kitchen_Key");
			room->OpenRoom();
			GET_SINGLE(UIManager)->RemoveItem(US_Key_yellow);
			GET_SINGLE(UIManager)->ShowStageInfo(RoomNum::kitchen);
		}
		else if ((CheckKey(room->GetRoomId())) && room->GetRoomId() == RoomNum::bedRoom)
		{
			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Kitchen_Key");
			GET_SINGLE(SoundManager)->LoadSound(L"Opened", "Sounds\\Door\\door open.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Opened", 7);
			room->OpenRoom();
			GET_SINGLE(UIManager)->RemoveItem(US_Key_green);
			GET_SINGLE(UIManager)->ShowStageInfo(RoomNum::kitchen);
		}
		else if ((CheckKey(room->GetRoomId())) && room->GetRoomId() == RoomNum::workRoom)
		{
				((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("Kitchen_Key");
			GET_SINGLE(SoundManager)->LoadSound(L"Opened", "Sounds\\Door\\door open.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Opened", 7);
			room->OpenRoom();
			GET_SINGLE(UIManager)->RemoveItem(US_Key_blue);
			GET_SINGLE(UIManager)->ShowStageInfo(RoomNum::kitchen);
		}
		else
		{
			GET_SINGLE(SoundManager)->LoadSound(L"Locked", "Sounds\\Door\\door locked.wav", SoundType::SFX);
			GET_SINGLE(SoundManager)->PlaySFXSound(L"Locked", 7);
			((GameScene*)(GET_SINGLE(SceneManager))->GetCurrentScene())->SetText("WareRoom_NoKey");
		}
	}
	else
	{
		// TODO : 방 이동하기


		switch (room->GetRoomId())
		{
		case RoomNum::restRoom:
		{
			// 홀에 있던 모든 콜라이더 비활성화
			for (Collider* collider : ((GameScene*)GetMyScene())->_hallColliders)
			{
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				collider->SetActive(false);
			}
			// 현재의 룸정보를 바꿈
			_currentRoomNum = RoomNum::restRoom;

			GetMyScene()->_actors[LAYER_BACKGROUND].clear();

			// 화장실 오브젝트 콜라이더를 매니저에 추가함.
			for (Collider* collider : ((GameScene*)GetMyScene())->_restRoomColliders)
			{
				// GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(true);
			}
			//_hall = ((GameScene*)GetMyScene())->_hall;
			((GameScene*)GetMyScene())->EnterRoom(RoomNum::restRoom);
		}
		break;
		case RoomNum::wareHouse:
		{
			for (Collider* collider : ((GameScene*)GetMyScene())->_hallColliders)
			{
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				collider->SetActive(false);
			}
			// 현재의 룸정보를 바꿈
			_currentRoomNum = RoomNum::wareHouse;

			GetMyScene()->_actors[LAYER_BACKGROUND].clear();

			// 화장실 오브젝트 콜라이더를 매니저에 추가함.
			for (Collider* collider : ((GameScene*)GetMyScene())->_wareHouseColliders)
			{
				// GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(true);
			}
			//_hall = ((GameScene*)GetMyScene())->_hall;
			((GameScene*)GetMyScene())->EnterRoom(RoomNum::wareHouse);
		}
		break;
		case RoomNum::kitchen:
		{
			for (Collider* collider : ((GameScene*)GetMyScene())->_hallColliders)
			{
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				collider->SetActive(false);
			}
			// 현재의 룸정보를 바꿈
			_currentRoomNum = RoomNum::kitchen;

			GetMyScene()->_actors[LAYER_BACKGROUND].clear();

			// 화장실 오브젝트 콜라이더를 매니저에 추가함.
			for (Collider* collider : ((GameScene*)GetMyScene())->_kitchenColliders)
			{
				// GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(true);
			}
			//_hall = ((GameScene*)GetMyScene())->_hall;
			((GameScene*)GetMyScene())->EnterRoom(RoomNum::kitchen);
		}
		break;
		case RoomNum::bedRoom:
			for (Collider* collider : ((GameScene*)GetMyScene())->_hall2Colliders)
			{
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				collider->SetActive(false);
			}
			_currentRoomNum = RoomNum::bedRoom;

			GetMyScene()->_actors[LAYER_BACKGROUND].clear();
			for (Collider* collider : ((GameScene*)GetMyScene())->_bedRoomColliders)
			{
				// GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(true);
			}
			((GameScene*)GetMyScene())->EnterRoom(RoomNum::bedRoom);
			break;
		case RoomNum::workRoom:
		{
			for (Collider* collider : ((GameScene*)GetMyScene())->_hall2Colliders)
			{
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				collider->SetActive(false);
			}
			// 현재의 룸정보를 바꿈
			_currentRoomNum = RoomNum::workRoom;

			GetMyScene()->_actors[LAYER_BACKGROUND].clear();

			// 화장실 오브젝트 콜라이더를 매니저에 추가함.
			for (Collider* collider : ((GameScene*)GetMyScene())->_workRoomColliders)
			{
				// GET_SINGLE(CollisionManager)->AddCollider(collider);
				collider->SetActive(true);
			}
			//_hall = ((GameScene*)GetMyScene())->_hall;
			((GameScene*)GetMyScene())->EnterRoom(RoomNum::workRoom);
		}
		break;
		case RoomNum::hall1:
		{
			// 다시 hall로 돌아갈때 각자의 collider삭제
			switch (_currentRoomNum)
			{
			case RoomNum::restRoom:
			{
				// 화장실 콜라이더 모두 꺼줌
				for (Collider* collider : ((GameScene*)GetMyScene())->_restRoomColliders)
				{
					//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
					collider->SetActive(false);
				}
			}
			break;
			case RoomNum::wareHouse:
			{
				// 창고 콜라이더 모두 꺼줌
				for (Collider* collider : ((GameScene*)GetMyScene())->_wareHouseColliders)
				{
					//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
					collider->SetActive(false);
				}
			}
			break;
			case RoomNum::kitchen:
			{
				// 창고 콜라이더 모두 꺼줌
				for (Collider* collider : ((GameScene*)GetMyScene())->_kitchenColliders)
				{
					//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
					collider->SetActive(false);
				}
			}
			break;

			
			case RoomNum::hall2:
				// 창고 콜라이더 모두 꺼줌
				for (Collider* collider : ((GameScene*)GetMyScene())->_hall2Colliders)
				{
					//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
					collider->SetActive(false);
				}
				break;
			default:
				break;
			}
			for (Collider* collider : ((GameScene*)GetMyScene())->_hallColliders)
			{
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				collider->SetActive(true);
			}
			((GameScene*)GetMyScene())->EnterHall(RoomNum::hall1);

			// TODO : hall로 돌아가기
		}
		break;
		case RoomNum::hall2:
		{
			switch (_currentRoomNum)
			{
			case RoomNum::hall1:
			{
				for (Collider* collider : ((GameScene*)GetMyScene())->_hallColliders)
				{
					//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
					collider->SetActive(false);
				}
			}
			break;
			case RoomNum::workRoom:
			{
				// 공방 콜라이더 모두 꺼줌
				for (Collider* collider : ((GameScene*)GetMyScene())->_workRoomColliders)
				{
					//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
					collider->SetActive(false);
				}
			}
			break;
			case RoomNum::bedRoom:
			{
				for (Collider* collider : ((GameScene*)GetMyScene())->_bedRoomColliders)
				{
					//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
					collider->SetActive(false);
				}
			}
			break;
			default:
				break;
			}
			for (Collider* collider : ((GameScene*)GetMyScene())->_hall2Colliders)
			{
				//GET_SINGLE(CollisionManager)->RemoveCollider(collider);
				collider->SetActive(true);
			}
			((GameScene*)GetMyScene())->EnterHall(RoomNum::hall2);
		}
		default:
			break;
		}

		_currentRoomNum = room->GetRoomId();
	}
}