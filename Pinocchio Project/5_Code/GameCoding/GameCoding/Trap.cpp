#include "pch.h"
#include "Trap.h"

void Trap::BeginPlay()
{
	Super::BeginPlay();
}

void Trap::Tick()
{
	Super::Tick();
}

void Trap::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Trap::SetActive(bool isActive)
{
	 _isActive = isActive; 
	 if (_isActive)
	 {
		 // TODO: ���⼭ �̹����� ����
	 }
}
