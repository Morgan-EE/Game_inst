#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"
#include "Utils.h"
#include "TimeManager.h"
void CameraComponent::BeginPlay()
{
	_cameraPos = GetOwner()->GetPos();
}

void CameraComponent::TickComponent()
{
	if (_owner == nullptr)
		return;

	Vec2 pos = _owner->GetPos();

	float newPosX = Utils::Lerp(_cameraPos.x, pos.x, _cameraSpeed * GET_SINGLE(TimeManager)->GetDeltaTime());
	//float newPosX = ::lerp(_cameraPos.x, pos.x, 0.2f);

	// Temp Code
	// 
	// TODO : 
	// 3024.f 와 2064.f 는 현재 배경의 이미지 사이즈를 받아왔음. 
	// 반드시 따로 관리할 것.

	Vec2Int backgroundSize = GET_SINGLE(SceneManager)->GetBackgroundSize();

	//pos.x = ::clamp(pos.x, static_cast<float>(GWinSizeX / 2), backgroundSize.x - static_cast<float>(GWinSizeX / 2));
	//pos.y = ::clamp(pos.y, static_cast<float>(GWinSizeY / 2), backgroundSize.y - static_cast<float>(GWinSizeY / 2));

	
	// 게임씬 카메라
	//pos.x = ::clamp(pos.x, static_cast<float>(960), backgroundSize.x + 960 - static_cast<float>(0));
	newPosX = ::clamp(newPosX, static_cast<float>(960), backgroundSize.x + 960 - static_cast<float>(0));
	//pos.x = ::clamp(pos.x - 960, static_cast<float>(0), backgroundSize.x - static_cast<float>(0));
	//pos.y = ::clamp(pos.y, static_cast<float>(-500), backgroundSize.y * static_cast<float>(0));
	//GET_SINGLE(SceneManager)->SetCameraPos(pos);
	GET_SINGLE(SceneManager)->SetCameraPos({ newPosX , pos.y});
	_cameraPos.x = newPosX;
}

void CameraComponent::Render(HDC hdc)
{
	wstring str2 = std::format(L"pos {0}, {1}", (float)_cameraPos.x, _owner->GetPos().y);
	::TextOut(hdc, 580, 580, str2.c_str(), static_cast<int32>(str2.size()));

	wstring str3 = std::format(L"pos {0}, {1}", _owner->GetPos().x, _owner->GetPos().y);
	::TextOut(hdc, 580, 680, str3.c_str(), static_cast<int32>(str3.size()));
}
