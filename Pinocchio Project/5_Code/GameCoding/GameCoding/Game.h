#pragma once
class Game
{
public:
	Game();
	~Game();

	void Init(HWND hwnd);
	void Update();
	void Render();
	void LateUpdate();

private:
	HWND _hwnd = {};
	HDC hdc = {};

private:
	// Double Buffering
	RECT _rect = {};
	HDC hdcBack = {};
	HBITMAP _bmpBack = {};
};

