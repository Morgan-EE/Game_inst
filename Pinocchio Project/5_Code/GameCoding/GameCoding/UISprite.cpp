#include "pch.h"
#include "UISprite.h"
#include "Sprite.h"
#include "Utils.h"

UISprite::UISprite()
{

}

UISprite::~UISprite()
{

}

void UISprite::BeginPlay()
{
	Super::BeginPlay();
}

void UISprite::Tick()
{
	Super::Tick();
}

void UISprite::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprites[_state])
	{
		::TransparentBlt(hdc,
			static_cast<int32>(_pos.x) - _size.x / 2,
			static_cast<int32>(_pos.y) - _size.y / 2,
			_size.x,
			_size.y,
			_sprites[_state]->GetDC(),
			_sprites[_state]->GetPos().x,
			_sprites[_state]->GetPos().y,
			_sprites[_state]->GetSize().x,
			_sprites[_state]->GetSize().y,
			_sprites[_state]->GetTransparent());
	}
	else
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}
}
