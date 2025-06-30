#pragma once

class UI;
class UISprite;
class UIManager
{
	DECLARE_SINGLE(UIManager);
public:
	void Init(HWND hwnd);
	void Update();
	void Render(HDC hdc);

	void SetItem(UISprite* ui, UISpriteState state);
	void RemoveItem(UISpriteState state);
	void AddItem(UISpriteState state);

	void SetPiece(UISprite* ui, UISpriteState state);
	void RemovePiece(UISpriteState state);
	void AddPiece(UISpriteState state);
	
	void ShowStageInfo(RoomNum num);
private:
	HWND	_hwnd = {};
	Vec2 _inventoryPos[3] = {};



private:
	vector<UISprite*> _inventory = {};
	vector<UISprite*> _piece = {};


private:
	float _disappearTime = 0.f;
	wstring str = L"";
};
