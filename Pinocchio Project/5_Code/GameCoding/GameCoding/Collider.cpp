#include "pch.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Actor.h"

Collider::Collider(ColliderType colliderType)
	: _colliderType(colliderType)
{

}

Collider::~Collider()
{

}

void Collider::BeginPlay()
{

}

void Collider::TickComponent()
{
	
}

void Collider::Render(HDC hdc)
{

}

bool Collider::CheckCollision(Collider* other)
{
	uint32 layer = other->GetCollisionLayerType();
	if (_collisionFlag & (1 << layer))
		return true;

	return false;
}

bool Collider::CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	RECT intersect = {};
	return ::IntersectRect(&intersect, &r1, &r2);	// 두 개의 rect의 충돌여부와 충돌범위를 얻을 수 있는 함수
}

bool Collider::CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2)
{
	return false;
}

bool Collider::CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2)
{
	// 서로의 반지름의 합보다 서로의 중점까지의 거리가 작을경우 충돌 판정

	Vec2 p1 = s1->GetOwner()->GetPos();
	float r1 = s1->GetRadius();

	Vec2 p2 = s2->GetOwner()->GetPos();
	float r2 = s2->GetRadius();

	Vec2 dir = p1 - p2;
	float dist = dir.Length();

	return dist <= r1 + r2;
}

void Collider::AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag |= (1 << layer);
}

void Collider::RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag &= ~(1 << layer);
}





void Collider::RemoveCollisionFlagLayerAll()
{
	_collisionFlag = 0;
}

// https://m.blog.naver.com/winterwolfs/10165506488