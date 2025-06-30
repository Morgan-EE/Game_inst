#pragma once
#include "SpriteActor.h"


class Interactionable : public SpriteActor
{
	using Super = SpriteActor;
public:
	Interactionable();
	virtual ~Interactionable();

	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

	virtual void SetActive();

	InteractionType GetInteractionType() { return _interactionType; }
	void SetInteractionType(InteractionType type) { _interactionType = type; }

private:
	InteractionType _interactionType = InteractionType::None;
};

