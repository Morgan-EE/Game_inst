#include "pch.h"
#include "Cheese.h"

Cheese::Cheese()
{

}

Cheese::~Cheese()
{

}

void Cheese::BeginPlay()
{
	Super::BeginPlay();
	SetItemType(ItemType::Cheese);
}

void Cheese::Tick()
{
	Super::Tick();
}

void Cheese::Render(HDC hdc)
{
	Super::Render(hdc);
}
