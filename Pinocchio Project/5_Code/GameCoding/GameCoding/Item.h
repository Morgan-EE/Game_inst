#pragma once
#include "SpriteActor.h"

class BoxCollider;

class Item : public SpriteActor
{
	using Super = SpriteActor;
public:
	Item();
	virtual ~Item();

	ItemType GetItemType() { return _itemType; }
	void SetItemType(ItemType itemType) { _itemType = itemType; }

	BoxCollider* _myCollider;

	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

protected:
	ItemType _itemType = ItemType::None;
};

