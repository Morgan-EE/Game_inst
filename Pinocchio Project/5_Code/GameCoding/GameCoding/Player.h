#pragma once
#include "FlipbookActor.h"

class Flipbook;
class Collider;
class BoxCollider;
class Hall;

enum class PlayerState
{
	Idle,
	Move,
	Climb,
	Hide,
	AutoMove,
	AutoClimb,
	AutoFall,
	OnBox,
};
enum PLAYER_DIR
{
	PD_RIGHT,
	PD_LEFT,
};
enum class PlayerAutoDir
{
	Right,
	Left,
};
class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentOverlap(Collider* collider, Collider* other) override;

private:
	void Jump();
	void TickGravity();

	/// <summary>
	/// 콜라이더와의 충돌 (밀어내는 방식)
	/// </summary>
	/// <param name="b1"></param>
	/// <param name="b2"></param>
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

	/// <summary>
	/// 장애물을 움직임
	/// </summary>
	/// <param name="other"></param>
	void MoveOtherActor(Collider* other);


public:
	bool _isWalking;
	float _walkingTimer;
	void SetPlayerState(PlayerState state) { _playerState = state; }
	PlayerState GetPlayerState() { return _playerState; }

	void SetPlayerDir(PLAYER_DIR dir) { _playerDir = dir; }
	PLAYER_DIR GetPlayerDir() { return _playerDir; }

	void SetPlayerAutoDir(PlayerAutoDir dir) { _playerAutoDir = dir; }
	PlayerAutoDir GetPlayerAutoDir() { return _playerAutoDir; }

	/// <summary>
	/// ITEM
	/// </summary>
public:
	/// <summary>
	/// 플레이어가 키를 가지고 있는지를 id를 넣어 확인
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	bool GetKey(KeyID id) { return _key[static_cast<int>(id)]; }

	/// <summary>
	/// 플레이어에게 키를 추가함.
	/// </summary>
	/// <param name="id"></param>
	void AddKey(RoomNum id) { _key[static_cast<int>(id)] = true; }

	/// <summary>
	/// 현재 치즈를 가지고 있는지
	/// </summary>
	/// <returns></returns>
	bool HasCheese() { return _hasCheese; }

	/// <summary>
	/// 치즈를 가지고 있는지를 정함
	/// </summary>
	void SetCheese(bool cheese) { _hasCheese = cheese; }

	/// <summary>
	/// 현재 조각의 개수를 가져옴
	/// </summary>
	/// <returns></returns>
	int32 GetPieceCount() { return _pieceCount; }

	/// <summary>
	/// 조각 아이템을 얻을 때 개수를 추가함.
	/// </summary>
	void AddPiece() { _pieceCount++; }
	int32 GetPiece() { return _pieceCount; }
	/// <summary>
	/// 키와 방의 id를 비교한다.
	/// </summary>
	/// <param name="roomNumber"></param>
	bool CheckKey(RoomNum roomNumber);

	/// <summary>
	/// 현재 접촉한 문의 정보 체크
	/// 문과 키의 정보가 일치하면 문을 염
	/// </summary>
	/// <param name="other"></param>
	void RoomCheck(Collider* other);

	/// <summary>
	/// 플레이어가 살았는지를 가져움.
	/// </summary>
	/// <returns></returns>
	bool GetIsAlive() { return _isAlive; }
	void SetIsAlive(bool isAlive) { _isAlive = isAlive; }
private:
	Flipbook* _flipbookUp = nullptr;
	Flipbook* _flipbookDown = nullptr;
	Flipbook* _flipbookLeft = nullptr;
	Flipbook* _flipbookRight = nullptr;
	Flipbook* _flipbookIdleRight = nullptr;
	Flipbook* _flipbookIdleLeft = nullptr;


private:
	float _moveSpeed = 1800.f;
	Stat _stat = {};
	Vec2 _speed = {};
	int32 _gravity = 1000;
	bool _onGround = false;
	bool _isAlive = true;

// 장애물을 옮기기 위해 필요한 변수들
private:
	bool canOtherBoxMove = false;
	Vec2 _currentSpeed = {};

private:
	int32 _pieceCount = 0;
	bool _hasCheese = false;
	bool _key[5] = {};

private:
	PlayerState _playerState = PlayerState::Idle;
	PLAYER_DIR _playerDir = PD_RIGHT;
	Vec2 _destinationSide = {};
	Vec2 _destinationTop = {};
	PlayerAutoDir _playerAutoDir = PlayerAutoDir::Right;
	Vec2 _moveDir = {};


	// 플레이어가 몇층에 있는지
	uint32 _height = 0;

	// 상자 위에 올라갔을때 조금이라도 움직이기위해
	float _distance = 3.f;

public:
	void SetHall(Hall* hall) { _hall = hall; }
	//void SetRoom()
private:
	Hall* _hall = nullptr;
	RoomNum _currentRoomNum = RoomNum::hall1;
	//Room* _room = nullptr;
};