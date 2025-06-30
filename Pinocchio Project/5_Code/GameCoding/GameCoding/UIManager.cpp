#include "pch.h"
#include "UIManager.h"
#include "UI.h"
#include "UISprite.h"
#include "TimeManager.h"

void UIManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_inventoryPos[0] = { 100,100 };
	_inventoryPos[1] = { 200,100 };
	_inventoryPos[2] = { 300,100 };
}

void UIManager::Update()
{

}

void UIManager::Render(HDC hdc)
{
	if (_disappearTime >= 0.1f)
	{
		::TextOut(hdc, 10, 890, str.c_str(), static_cast<int32>(str.size()));
		_disappearTime -= GET_SINGLE(TimeManager)->GetDeltaTime();
	}
}

void UIManager::SetItem(UISprite* ui, UISpriteState state)
{
	if (ui == nullptr)
		return;
	_inventory.push_back(ui);
	ui->SetState(state);
}

void UIManager::RemoveItem(UISpriteState state)
{
	for (int32 i = 0; i < 3; i++)
	{
		if (_inventory[i]->GetState() == state)
		{
			_inventory[i]->SetState(US_None);
			return;
		}
	}
}

void UIManager::AddItem(UISpriteState state)
{
	for (int i = 0; i < 3; i++)
	{
		if (_inventory[i]->GetState() == US_None)
		{
			_inventory[i]->SetState(state);
			return;
		}
	}
}

void UIManager::SetPiece(UISprite* ui, UISpriteState state)
{
	if (ui == nullptr)
		return;
	_piece.push_back(ui);
	ui->SetState(state);
}

void UIManager::RemovePiece(UISpriteState state)
{
	for (int32 i = 0; i < 5; i++)
	{
		if (_piece[i]->GetState() == state)
		{
			_piece[i]->SetState(US_None);
			//return;
		}
	}
}

void UIManager::AddPiece(UISpriteState state)
{
	for (int i = 0; i < 5; i++)
	{
		if (_piece[i]->GetState() == US_None)
		{
			_piece[i]->SetState(state);
			return;
		}
	}
}

void UIManager::ShowStageInfo(RoomNum num)
{
	_disappearTime = 5.f;
	switch (num)
	{
	case RoomNum::restRoom:
		str = L"화장실";
		break;
	case RoomNum::wareHouse:
		str = L"방2";
		break;
	default:
		break;

	}
}

