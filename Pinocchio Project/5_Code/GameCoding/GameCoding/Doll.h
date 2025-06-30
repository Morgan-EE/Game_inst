#pragma once
#include "Interactionable.h"

enum DollID
{
	// 비밀 번호 순서
	C = 0,
	A,
	B,
	D,
};

class Doll : public Interactionable
{
	using Super = Interactionable;
public:
	Doll();
	virtual ~Doll() override;
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;


	void SetIsActive(bool active) { _isActive = active; }
	bool GetIsActive() { return _isActive; }

	void DollReset();

	//bool IsClear() { return g_isClear; }


	void SetDollID(DollID id) { _id = id; }
	DollID GetDollID() { return _id; }
private:
	DollID _id;
	bool _isActive;
};

