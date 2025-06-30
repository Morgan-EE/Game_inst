#pragma once
#include "Item.h"


class Key : public Item
{
	using Super = Item;
public:
	Key();
	virtual ~Key() override;

	RoomNum GetKeyID() { return _id; }
	void SetKeyID(RoomNum id) { _id = id; }

	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

private:
	RoomNum _id = RoomNum::restRoom;
};

