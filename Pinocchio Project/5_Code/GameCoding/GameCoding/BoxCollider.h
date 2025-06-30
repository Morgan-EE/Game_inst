#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
	using Super = Collider;
public:

	BoxCollider();
	virtual ~BoxCollider() override;

	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;
	bool CheckCollision(Collider* other) override;

	Vec2 GetSize() { return _size; }
	void SetSize(Vec2 size) { _size = size; }

	RECT GetRect();

	//
	

private:
	Vec2 _size = {};

};

