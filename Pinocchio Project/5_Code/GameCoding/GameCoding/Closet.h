#pragma once
#include "SpriteActor.h"
class Closet : public SpriteActor
{
	using Super = SpriteActor;
public:
	Closet();
	virtual ~Closet();
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

};

