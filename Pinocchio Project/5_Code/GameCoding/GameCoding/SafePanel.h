#pragma once
#include "Panel.h"
class SafePanel : public Panel
{
	using Super = Panel;
public:
	SafePanel();
	virtual ~SafePanel() override;


public:
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;


// 	void OnClick0Button();
// 	void OnClick1Button();
// 	void OnClick2Button();
// 	void OnClick3Button();
// 	void OnClick4Button();
// 	void OnClick5Button();
// 	void OnClick6Button();
// 	void OnClick7Button();
// 	void OnClick8Button();
// 	void OnClick9Button();
};

