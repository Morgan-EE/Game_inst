#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider();
	
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }


	unordered_set<Collider*>& GetCollsionMap() { return _collisionMap; }

protected:
	// 각각 콜라이더 타입의 따른 충돌 확인 여부
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);

public:
	void SetCollisionLayer(COLLISION_LAYER_TYPE layer) { _collisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayerType() { return _collisionLayer; }


	void SetCollisionFlag(uint32 flag) { _collisionFlag = flag; }
	uint32 GetCollisionFlag() { return _collisionFlag; }

	void ResetCollisionFlag() { _collisionFlag = 0; }

	/// <summary>
	/// 충돌 할 상대 추가
	/// </summary>
	/// <param name="layer"></param>
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayerAll();

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

private:

	unordered_set<Collider*> _collisionMap;	// 중복으로 충돌 처리를 막기 위해 사용

	// 자신의 타입
	COLLISION_LAYER_TYPE _collisionLayer = CLT_OBJECT;
	
	// 충돌할 타입을 결정하는 비트플래그
	// 디폴트 값은 모두 충돌
	uint32 _collisionFlag = 0xFFFFFFFF;


	// pos
public:
	Vec2 GetPos() { return _pos; }
	void SetPos(Vec2 pos) { _pos = pos; }

protected:
	Vec2 _pos = {};

	// checkTrigger
public:
	bool GetTrigger() { return _isTrigger; }
	void SetTrigger(bool trigger) { _isTrigger = trigger; }

	void SetActive(bool active) { _isActive = active; }
	bool GetIsActive() { return _isActive; }
protected:
	bool _isTrigger = false;

	bool _isActive = true;
};

