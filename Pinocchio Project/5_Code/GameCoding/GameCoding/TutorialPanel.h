#pragma once
#include "Panel.h"
class UI;
class GameScene;
class TutorialPanel : public Panel
{
	using Super = Panel;
public:
	TutorialPanel();
	virtual ~TutorialPanel() override;
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;

	void OnClickNextButton();

private:
	vector<UI*> _uiSprites;
	UI* _button;
	int32 _cursor = 0;

public:
	GameScene* _gameScene = nullptr;
};