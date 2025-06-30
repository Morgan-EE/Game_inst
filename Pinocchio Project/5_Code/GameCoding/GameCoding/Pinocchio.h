#pragma once
#include "FlipbookActor.h"

enum class PinoState
{
	Idle,
	Move,
	Attack
};

enum PINO_DIR
{
	PINO_RIGHT,
	PINO_LEFT,
};

class Pinocchio : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Pinocchio();
	virtual ~Pinocchio() override;
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;
	void OnComponentOverlap(Collider* collider, Collider* other) override;
	
	PinoState GetPinoState() { return _pinoState; }
	void SetPinoState(PinoState pinoState) { _pinoState = pinoState; }

	PINO_DIR GetPinoDir() { return _pinoDir; }
	void SetPinoDir(PINO_DIR dir) { _pinoDir = dir; }

	/// <summary>
	/// �÷��̾ �Ѿư�
	/// </summary>
	void ChasePlayer();


public:
	Flipbook* _flipbookLeft = nullptr;
	Flipbook* _flipbookRight = nullptr;
	Flipbook* _flipbookIdle = nullptr;
	Flipbook* _flipbookAttack = nullptr;
private:
	PinoState _pinoState = PinoState::Idle;
	PINO_DIR _pinoDir = PINO_LEFT;

	// �÷��̾ ã�Ҵ���
	bool _isFind = false;

	// �Ѵ� �ӵ�
	float _chaseSpeed = 200;

	// ���� ����
	float _attackRange;
};

