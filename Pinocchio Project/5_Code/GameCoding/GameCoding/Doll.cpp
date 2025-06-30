#include "pch.h"
#include "Doll.h"

Doll::Doll()
{

}

Doll::~Doll()
{

}

void Doll::BeginPlay()
{
	Super::BeginPlay();
	DollReset();
}

void Doll::Tick()
{
	Super::Tick();
}

void Doll::Render(HDC hdc)
{
	Super::Render(hdc);
}



void Doll::DollReset()
{
	/*for (int i = 0; i < 4; i++)
	{
		g_isActive[i] = false;
	}*/
}