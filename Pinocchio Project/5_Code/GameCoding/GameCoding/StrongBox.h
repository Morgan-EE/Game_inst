#pragma once
#include "Interactionable.h"

enum class StrongBoxState
{
	Closed,
	Opened,
};

class StrongBox : public Interactionable
{
	using Super = Interactionable;
public:
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;
	void SetActive() override;

	void SetStrongBoxState(StrongBoxState state) { _state = state; }
	StrongBoxState GetStrongBoxState() { return _state; }

private:
	StrongBoxState _state = StrongBoxState::Closed;
	
};

