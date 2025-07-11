#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetFlipbook(Flipbook* flipbook);
	Flipbook* GetFlipbook() { return _flipbook; }
	void Reset();
protected:
	Flipbook* _flipbook = nullptr;

	// flipbook의 진행 상태 관리 변수
	float _sumTime = 0.f;
	int32 _idx = 0;
};

