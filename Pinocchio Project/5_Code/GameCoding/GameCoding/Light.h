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
	int32 _blackAlpha = 200; // �� �� ����
	int32 _radius = 270;
	Region* _regionRectangle;

	SolidBrush* _blackAlphaBrush;
	vector<PathGradientBrush*> _EllipseBrushVector; // �� �׸� �� ��� �ϴ� �׶��̼� �귯��

	vector<GraphicsPath*> _lightVector;
};

