#include "pch.h"
#include "Pinocchio.h"

#include "TimeManager.h"
#include "ResourceManager.h"

#include "Collider.h"
#include "BoxCollider.h"
#include "Player.h"
#include "GameScene.h"
#include "SceneManager.h"

Pinocchio::Pinocchio()
{

}

Pinocchio::~Pinocchio()
{

}

void Pinocchio::BeginPlay()
{
	Super::BeginPlay();
	_flipbookLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PinoMoveLeft");
	_flipbookRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PinoMoveRight");



	// TODO : SetFlipBook()
	SetPinoState(PinoState::Idle);
	SetFlipbook(_flipbookLeft);
	_chaseSpeed = 200;
	_attackRange = 50;
}

void Pinocchio::Tick()
{
	Super::Tick();

	if ((((GameScene*)GET_SINGLE(SceneManager)->GetCurrentScene())->isTabToggle))
	{
		return;
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	switch (_pinoState)
	{
	case PinoState::Idle:
		break;
	case PinoState::Move:
	{
		switch(_pinoDir)
		{
		case PINO_RIGHT:
		{
			_pos.x += _chaseSpeed * deltaTime;
			SetFlipbook(_flipbookRight);
		}
			break;
		case PINO_LEFT:
			_pos.x -= _chaseSpeed * deltaTime;
			SetFlipbook(_flipbookLeft);
			break;
		default:
			break;
		}
	}
		break;
	case PinoState::Attack:
		break;
	default:
		break;
		
	}
}

void Pinocchio::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Pinocchio::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	
}

void Pinocchio::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	// ������ ����� �ٸ� Ÿ���ϰ�� ����
	if (b1 == nullptr || b2 == nullptr)
		return;

	switch (other->GetCollisionLayerType())
	{
	case CLT_PLAYER:
	{
		SetPinoState(PinoState::Idle);
	}
	break;
	}
}

void Pinocchio::OnComponentOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	// ������ ����� �ٸ� Ÿ���ϰ�� ����
	if (b1 == nullptr || b2 == nullptr)
		return;



	// �÷��̾�� ��Ҵ����� �˻�
	switch (other->GetCollisionLayerType())
	{
	case CLT_PLAYER:
	{
		// �÷��̾ HIDE���¸� ��������.
		if (dynamic_cast<Player*>(other->GetOwner())->GetPlayerState() == PlayerState::Hide)
		{
			SetPinoState(PinoState::Idle);
			return;
		}

		Vec2 playerPos = other->GetOwner()->GetPos();
		if (playerPos.x < GetPos().x)
		{
			// �÷��̾ ������ ���ʿ� ����.

			// ���� �÷��̾ ���ݹ������� �ִ��� �˻�
			if (::abs(GetPos().x - playerPos.x) < _attackRange)
			{
				SetPinoState(PinoState::Attack);
			}
			else
			{
				SetPinoState(PinoState::Move);
				SetPinoDir(PINO_LEFT);
			}
		}
		else
		{
			//�÷��̾ ������ �����ʿ� ����.

			// ���� �÷��̾ ���ݹ������� �ִ��� �˻�
			if (::abs(GetPos().x - playerPos.x) < _attackRange)
			{
				SetPinoState(PinoState::Attack);
			}
			else
			{
				SetPinoState(PinoState::Move);
				SetPinoDir(PINO_RIGHT);
			}
		}
	}
	break;
	}
}