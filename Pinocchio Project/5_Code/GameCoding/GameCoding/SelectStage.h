#pragma once
#include "Scene.h"
#include <Windows.h>

class Actor;

class SelectStage : public Scene
{
	using Super = Scene;
public:
	void DrawRectangle(HDC hdc, int x, int y, int width, int height);
	SelectStage();
	virtual ~SelectStage() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	bool isDrawRectangle = false;

};

