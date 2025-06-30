#pragma once
#include "Item.h"

class Cheese : public Item
{
	using Super = Item;
public:
	Cheese();
	virtual ~Cheese();

	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

private:

};

