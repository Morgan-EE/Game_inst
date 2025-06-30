#pragma once
#include "UI.h"

class Sprite;



class UISprite : public UI
{
	using Super = UI;
public:
	UISprite();
	virtual ~UISprite();

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetSize(Vec2Int size) { _size = size; }
	Sprite* GetSprite(UISpriteState state) { return _sprites[state]; }
	void SetSprite(Sprite* sprite, UISpriteState state) { _sprites[state] = sprite; }
	UISpriteState GetState() { return _state; }
	void SetState(UISpriteState state) { _state = state; }
private:
	Sprite* _sprites[US_MaxCount] = {};
	UISpriteState _state = US_None;
};