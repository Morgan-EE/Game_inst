#pragma once
#include "SpriteActor.h"
class Trap : public SpriteActor
{
	using Super = SpriteActor;

public:
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

	bool IsActive() { return _isActive; }
	void SetActive(bool isActive);

private:
	// TODO : 치즈 올려놨을 경우 처리

	// 작동되기 전 -> 닿으면 죽음 (false)
	bool _isActive = false;
};

