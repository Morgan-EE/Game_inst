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

			// TODO : �Ҹ� ��

		}
	}

	for (int32 i = 0; i < _count; i++)
	{
		if (_isActive[i] == false)
		{
			// ��й�ȣ�� �ƴϴ� �ٽ� �ʱ�ȭ
			
			// _isActive �ʱ�ȭ
			for (int32 j = 0; j < 4; j++)
			{
				_isActive[j] = false;
			}
			// doll �ʱ�ȭ
			for (Doll* doll : _dolls)
			{
				doll->SetIsActive(false);
				//TODO : �Ҹ� �ٽ� ���
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