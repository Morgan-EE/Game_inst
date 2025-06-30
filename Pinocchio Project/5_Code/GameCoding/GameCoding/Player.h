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
	/// �ݶ��̴����� �浹 (�о�� ���)
	/// </summary>
	/// <param name="b1"></param>
	/// <param name="b2"></param>
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

	/// <summary>
	/// ��ֹ��� ������
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
	/// �÷��̾ Ű�� ������ �ִ����� id�� �־� Ȯ��
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	bool GetKey(KeyID id) { return _key[static_cast<int>(id)]; }

	/// <summary>
	/// �÷��̾�� Ű�� �߰���.
	/// </summary>
	/// <param name="id"></param>
	void AddKey(RoomNum id) { _key[static_cast<int>(id)] = true; }

	/// <summary>
	/// ���� ġ� ������ �ִ���
	/// </summary>
	/// <returns></returns>
	bool HasCheese() { return _hasCheese; }

	/// <summary>
	/// ġ� ������ �ִ����� ����
	/// </summary>
	void SetCheese(bool cheese) { _hasCheese = cheese; }

	/// <summary>
	/// ���� ������ ������ ������
	/// </summary>
	/// <returns></returns>
	int32 GetPieceCount() { return _pieceCount; }

	/// <summary>
	/// ���� �������� ���� �� ������ �߰���.
	/// </summary>
	void AddPiece() { _pieceCount++; }
	int32 GetPiece() { return _pieceCount; }
	/// <summary>
	/// Ű�� ���� id�� ���Ѵ�.
	/// </summary>
	/// <param name="roomNumber"></param>
	bool CheckKey(RoomNum roomNumber);

	/// <summary>
	/// ���� ������ ���� ���� üũ
	/// ���� Ű�� ������ ��ġ�ϸ� ���� ��
	/// </summary>
	/// <param name="other"></param>
	void RoomCheck(Collider* other);

	/// <summary>
	/// �÷��̾ ��Ҵ����� ������.
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

// ��ֹ��� �ű�� ���� �ʿ��� ������
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


	// �÷��̾ ������ �ִ���
	uint32 _height = 0;

	// ���� ���� �ö����� �����̶� �����̱�����
	float _distance = 3.f;

public:
	void SetHall(Hall* hall) { _hall = hall; }
	//void SetRoom()
private:
	Hall* _hall = nullptr;
	RoomNum _currentRoomNum = RoomNum::hall1;
	//Room* _room = nullptr;
};