#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
	using Super = Scene;
public:
	TitleScene();
	virtual ~TitleScene() override;

private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void LateUpdate() override;

private:
	// 버튼 누를 경우 실행되는 함수들
	void ChangeCutScene();
	void ExitGame();
};

