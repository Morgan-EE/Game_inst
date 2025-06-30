#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "fmod.hpp"

// Scene
#include "GameScene.h"

FlipbookActor::FlipbookActor()
{

}

FlipbookActor::~FlipbookActor()
{

}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	int32 frameCount = (info.end - info.start + 1);
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	if (((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))->isTabToggle)
	{
		::TransparentBlt(hdc,
			((int32)_pos.x - info.size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2)) * (2.0f / 5.0f),
			(((int32)_pos.y - info.size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2))) + - 10,
			info.size.x / 2,
			info.size.y / 2,
			info.texture->GetDC(),
			(info.start + _idx) * info.size.x,
			info.line * info.size.y,
			info.size.x,
			info.size.y,
			info.texture->GetTransparent());
	}
	else
	{
		::TransparentBlt(hdc,
			((int32)_pos.x - info.size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2)),
			((int32)_pos.y - info.size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2)) + 150,
			info.size.x,
			info.size.y,
			info.texture->GetDC(),
			(info.start + _idx) * info.size.x,
			info.line * info.size.y,
			info.size.x,
			info.size.y,
			info.texture->GetTransparent());
	}
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	// 중복 실행 방지
	if (flipbook && _flipbook == flipbook)
		return;

	_flipbook = flipbook;
	Reset();
}

void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}
