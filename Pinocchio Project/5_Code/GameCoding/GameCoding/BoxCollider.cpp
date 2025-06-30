#include "pch.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "Utils.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();
}

void BoxCollider::TickComponent()
{
	Super::TickComponent();
}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false)
		return;

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// Owner¿« pos
	Vec2 pos = GetOwner()->GetPos();

	// Collider¿« pos
	pos += _pos;

	pos.x -= (cameraPos.x - GWinSizeX / 2);
	pos.y -= (cameraPos.y - GWinSizeY / 2) - 150;
	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, pos, static_cast<int32>(_size.x), static_cast<int32>(_size.y));
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBox2Box(this, static_cast<BoxCollider*>(other));
		
	case ColliderType::Sphere:
		return CheckCollisionSphere2Box(static_cast<SphereCollider*>(other), this);

	default:
		break;
	}
	return false;
}

RECT BoxCollider::GetRect()
{
	Vec2 pos = GetOwner()->GetPos();
	Vec2 size = GetSize();

	/*RECT rect =
	{
		static_cast<int32>(pos.x - (size.x / 2)),
		static_cast<int32>(pos.y - (size.y / 2)),
		static_cast<int32>(pos.x + (size.x / 2)),
		static_cast<int32>(pos.y + (size.y / 2)),
	};			*/


	RECT rect =
	{
		static_cast<int32>(pos.x + _pos.x - (size.x / 2)),
		static_cast<int32>(pos.y + _pos.y - (size.y / 2)),
		static_cast<int32>(pos.x + _pos.x + (size.x / 2)),
		static_cast<int32>(pos.y + _pos.y + (size.y / 2)),
	};



	return rect;
}
