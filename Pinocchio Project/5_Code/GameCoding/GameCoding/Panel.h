#pragma once
#include "UI.h"

class Sprite;

class Panel : public UI
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel();

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void AddChild(UI* ui);
	bool RemoveChild(UI* ui);

private:
	vector<UI*> _children;
};

