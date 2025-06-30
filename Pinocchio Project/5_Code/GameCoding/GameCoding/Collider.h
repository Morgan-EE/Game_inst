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
	// ���� �ݶ��̴� Ÿ���� ���� �浹 Ȯ�� ����
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
	/// �浹 �� ��� �߰�
	/// </summary>
	/// <param name="layer"></param>
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayerAll();

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

private:

	unordered_set<Collider*> _collisionMap;	// �ߺ����� �浹 ó���� ���� ���� ���

	// �ڽ��� Ÿ��
	COLLISION_LAYER_TYPE _collisionLayer = CLT_OBJECT;
	
	// �浹�� Ÿ���� �����ϴ� ��Ʈ�÷���
	// ����Ʈ ���� ��� �浹
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

