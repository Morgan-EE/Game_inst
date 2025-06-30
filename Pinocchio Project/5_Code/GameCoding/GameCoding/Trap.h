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
	// TODO : ġ�� �÷����� ��� ó��

	// �۵��Ǳ� �� -> ������ ���� (false)
	bool _isActive = false;
};

