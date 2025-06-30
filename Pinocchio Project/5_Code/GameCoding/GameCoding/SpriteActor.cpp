#define _HAS_STD_BYTE 0

#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Texture.h"

#include "GameScene.h"

#include <gdiplus.h>
using namespace Gdiplus;

SpriteActor::SpriteActor()
{

}

SpriteActor::~SpriteActor()
{

}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();


}

void SpriteActor::Tick()
{
	Super::Tick();


}

size_t truncate(int value)
{
	if (value < 0)
	{
		return 0;
	}
	if (value > 255)
	{
		return 255;
	}

	return value;
}

Gdiplus::Image* BitmapToImage(HBITMAP hBitmap)
{
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromHBITMAP(hBitmap, NULL);
	return static_cast<Gdiplus::Image*>(bitmap);
}

void SpriteActor::Render(HDC hdc)
{
	if (!isActive)
	{
		return;
	}

	Super::Render(hdc);

	if (_sprite == nullptr)
		return;

	Vec2Int size = _sprite->GetSize();

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	if (((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->isTabToggle)
	{
		::TransparentBlt(hdc,
			((int32)_pos.x - size.x / 2 - (static_cast<int32>(cameraPos.x) - GWinSizeX / 2)) * (2.0f / 5.0f),
			((int32)_pos.y - size.y / 2 - (static_cast<int32>(cameraPos.y) - GWinSizeY / 2)) - 50,
			size.x / 2,
			size.y / 2,
			_sprite->GetDC(),
			_sprite->GetPos().x,
			_sprite->GetPos().y,
			_sprite->GetSize().x,
			_sprite->GetSize().y,
			_sprite->GetTransparent());
	}
	else
	{
		::TransparentBlt(hdc,
			(int32)_pos.x - size.x / 2 - (static_cast<int32>(cameraPos.x) - GWinSizeX / 2),
			((int32)_pos.y - size.y / 2 - (static_cast<int32>(cameraPos.y) - GWinSizeY / 2)) + offset,
			size.x,
			size.y,
			_sprite->GetDC(),
			_sprite->GetPos().x,
			_sprite->GetPos().y,
			_sprite->GetSize().x,
			_sprite->GetSize().y,
			_sprite->GetTransparent());
	}
}
