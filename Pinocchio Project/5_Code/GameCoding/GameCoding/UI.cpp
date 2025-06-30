#include "pch.h"
#include "UI.h"
#include "InputManager.h"

UI::UI()
{

}

UI::~UI()
{

}

void UI::BeginPlay()
{

}

void UI::Tick()
{

}

void UI::Render(HDC hdc)
{

}

RECT UI::GetRect()
{
	RECT rect =
	{
		_pos.x - _size.x / 2,	// left
		_pos.y - _size.y / 2,	// top
		_pos.x + _size.x / 2,	// right
		_pos.y + _size.y / 2,	// bottom
	};
	return rect;
}

bool UI::IsMouseInRect()
{
	RECT rect = GetRect();
	
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// 점이 사각형안에 있는지 판별하는 함수
	return ::PtInRect(&rect, mousePos);
}
