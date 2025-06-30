#include "pch.h"
#include "StrongBox.h"
#include "ResourceManager.h"
void StrongBox::BeginPlay()
{
	Super::BeginPlay();
}

void StrongBox::Tick()
{
	Super::Tick();
}

void StrongBox::Render(HDC hdc)
{
	Super::Render(hdc);
}

void StrongBox::SetActive()
{
	_state = StrongBoxState::Opened;
	// SetSprite ¹Ù²Ù±â
	SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"SafeOpen"));
}
