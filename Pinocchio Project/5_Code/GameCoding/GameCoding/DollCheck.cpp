#include "pch.h"
#include "DollCheck.h"
#include "Doll.h"
#include "GameScene.h"
#include "Item.h"
#include "BoxCollider.h"
DollCheck::DollCheck()
{

}

DollCheck::~DollCheck()
{

}

void DollCheck::Init()
{
	
}

void DollCheck::Tick()
{
	for (Doll* doll : _dolls)
	{
		if (doll->GetIsActive() == true)
		{
			int id = doll->GetDollID();

			if (_isActive[id] == false)
			{
				_count++;
			}
			_isActive[id] = true;

			// TODO : 소리 끔

		}
	}

	for (int32 i = 0; i < _count; i++)
	{
		if (_isActive[i] == false)
		{
			// 비밀번호가 아니니 다시 초기화
			
			// _isActive 초기화
			for (int32 j = 0; j < 4; j++)
			{
				_isActive[j] = false;
			}
			// doll 초기화
			for (Doll* doll : _dolls)
			{
				doll->SetIsActive(false);
				//TODO : 소리 다시 재생
			}

			_count = 0;
			return;
		}
		if (i == 3)
		{
			// Clear
			static bool isActivatedOnceDollCheck = false;

			if (!isActivatedOnceDollCheck)
			{
				((GameScene*)(_dolls[0]->GetMyScene()))->_piece5->_myCollider->SetActive(true);
				((GameScene*)(_dolls[0]->GetMyScene()))->_piece5->isActive = true;
				isActivatedOnceDollCheck = true;
			}
			int a = 3;
		}
	}
	
}

void DollCheck::AddDoll(Doll* doll)
{
	_dolls.push_back(doll);
}