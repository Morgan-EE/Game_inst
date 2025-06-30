#pragma once
#include "Scene.h"

class DeadScene : public Scene
{
	using Super = Scene;
public:
	DeadScene();
	virtual ~DeadScene() override;

private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void LateUpdate();

private:
	void ReadIntroText();

	// 버튼 누를 경우 실행되는 함수들
	void goToGameScene();
	void goToTitleScene();
};

