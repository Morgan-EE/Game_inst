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


	// ������ �ִ� collider�� ������ �浹 ���� 
	for (int32 i = 0; i < colliders.size(); i++)
	{
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			Collider* src = colliders[i];
			Collider* dest = colliders[j];

			// ������ �浹 Ȯ��
			if (src->CheckCollision(dest))
			{

				if (src->GetIsActive() == false || dest->GetIsActive() == false)
					continue;

				// ���� �̹� �浹���� �ʾ��� ��츸 �Ʒ� if�� ���� (�ߺ� �浹ó�� ����)
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
			// �浹���� �ʾ��� ���
			else
			{
				// ������ �浹ó���� �Ǿ����� ���
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
