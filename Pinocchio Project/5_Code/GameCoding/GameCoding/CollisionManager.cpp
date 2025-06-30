#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
	vector<Collider*>& colliders = _colliders;


	// 가지고 있는 collider간 서로의 충돌 여부 
	for (int32 i = 0; i < colliders.size(); i++)
	{
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			Collider* src = colliders[i];
			Collider* dest = colliders[j];

			// 서로의 충돌 확인
			if (src->CheckCollision(dest))
			{

				if (src->GetIsActive() == false || dest->GetIsActive() == false)
					continue;

				// 만약 이미 충돌하지 않았을 경우만 아래 if문 실행 (중복 충돌처리 막음)
				if (src->GetCollsionMap().contains(dest) == false)
				{
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);

					src->GetCollsionMap().insert(dest);
					dest->GetCollsionMap().insert(src);
				}
				else
				{
					src->GetOwner()->OnComponentOverlap(src, dest);
					dest->GetOwner()->OnComponentOverlap(dest, src);
				}
			}
			// 충돌하지 않았을 경우
			else
			{
				// 이전에 충돌처리가 되어있을 경우
				if (src->GetCollsionMap().contains(dest))
				{
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);

					src->GetCollsionMap().erase(dest);
					dest->GetCollsionMap().erase(src);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	_colliders.erase(std::remove(_colliders.begin(), _colliders.end(), collider), _colliders.end());
	//SAFE_DELETE(collider);
}
