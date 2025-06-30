#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Utils.h"
#include "Sprite.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::BeginPlay()
{
	Super::BeginPlay();

	SetButtonState(BS_Default);
}

void Button::Tick()
{
	Super::Tick();

	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


	// clicked 상태에서 일정 시간이 지나면 default 상태로 바꿈
	if (_state == BS_Clicked)
	{
		_sumTime += deltaTime;
		if (_sumTime > 0.2f)
		{
			_sumTime = 0.f;
			SetButtonState(BS_Default);
		}
	}
	if (IsMouseInRect())
	{
		// 마우스가 눌린 상태 체크
		if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))
		{
			SetButtonState(BS_Pressed);
			// OnPressed
			
		}
		else
		{
			if (_state == BS_Pressed)
			{
				SetButtonState(BS_Clicked);
				// OnClicked
				if (_onClick)
					_onClick();
			}
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_currentSprite)
	{
		::TransparentBlt(hdc,
			static_cast<int32>(_pos.x) - _size.x / 2,
			static_cast<int32>(_pos.y) - _size.y / 2,
			_size.x,
			_size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			_currentSprite->GetSize().x,
			_currentSprite->GetSize().y,
			_currentSprite->GetTransparent());
	}
	else
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}
}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	// 만약 _sprits[state]에 이미지가 있을 경우 현재의 이미지를 state에 맞는 sprite로 바꿈
	if (_sprites[state])
		SetCurrentSprite(_sprites[state]);
}
