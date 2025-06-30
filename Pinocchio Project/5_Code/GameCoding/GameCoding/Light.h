#pragma once
#include "SpriteActor.h"

#include <gdiplus.h>
using namespace Gdiplus;

class Light : public SpriteActor
{
public:
	Light();
	~Light();

	void AddLight(int32 x, int32 y);

private:
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	int32 _blackAlpha = 200; // 원 밖 투명도
	int32 _radius = 270;
	Region* _regionRectangle;

	SolidBrush* _blackAlphaBrush;
	vector<PathGradientBrush*> _EllipseBrushVector; // 원 그릴 때 사용 하는 그라데이션 브러쉬

	vector<GraphicsPath*> _lightVector;
};

