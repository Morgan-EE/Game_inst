#include "Inventory.h"
#include <algorithm>
using namespace std;

Inventory::Inventory()
	: m_ItemList(0), m_ID(0)
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(shared_ptr<Item> item)
{
	(*item).SetStat();
	m_ItemList.push_back(item);
}

void Inventory::Delete(int index)
{
	auto it = m_ItemList.begin();
	while (it != m_ItemList.end())
	{
		if ((*it)->GetIndex() == (index - 1))
		{
			it = m_ItemList.erase(it);
			cout << "아이템이 삭제되었습니다." << endl;
			return;
		}
		else
		{
			++it;
		}
	}
	cout << "아이템을 찾을 수 없습니다." << endl;
}

void Inventory::GradeUp(int index, shared_ptr<Item> src1, shared_ptr<Item> src2)
{
	// 두 아이템을 합성하여 새 객체를 만듦
	// 두 아이템은 삭제
	// 새로 만든 아이템을 인벤에 넣음

	if (src1->GetGrade() != src2->GetGrade())
	{
		cout << "같은 등급의 아이템만 합성 가능합니다." << endl;
		return;
	}
	if (src1->GetGrade() == 'S' || src2->GetGrade() == 'S')
	{
		cout << "이미 최고 등급의 아이템입니다." << endl;
		return;
	}
	if (src1->GetType() != src2->GetType())
	{
		cout << "같은 타입의 아이템끼리만 합성이 가능합니다." << endl;
		return;
	}

	int idx1 = src1->GetIndex();
	int idx2 = src2->GetIndex();

	ItemType type = src1->GetType();
	string name = src1->GetName();
	int level = 1;
	char grade = src1->GetGrade();

	switch (grade)
	{
	case 'C':
		grade = 'B';
		break;
	case 'B':
		grade = 'A';
		break;
	case 'A':
		grade = 'S';
		break;
	}

	// 새로운 아이템을 인벤에 추가
	switch (type)
	{
	case ItemType::Weapon:
		m_ItemList.push_back(make_shared<Weapon>(m_ID++, name, level, grade));
		break;
	case ItemType::Armor:
		m_ItemList.push_back(make_shared<Armor>(m_ID++, name, level, grade));
		break;
	case ItemType::Ring:
		m_ItemList.push_back(make_shared<Ring>(m_ID++, name, level, grade));
		break;
	}
	//switch (src1->GetType())
	//{
	//case ItemType::Weapon:
	//	m_ItemList.push_back(make_shared<Weapon>(index++, name, level, grade));
	//	break;
	//case ItemType::Armor:
	//	m_ItemList.push_back(make_shared<Armor>(index++, name, level, grade));
	//	break;
	//case ItemType::Ring:
	//	m_ItemList.push_back(make_shared<Ring>(index++, name, level, grade));
	//	break;
	//}

	// 두 아이템 삭제
		// 재료가 되는 아이템은 삭제
	for (auto it = m_ItemList.begin(); it != m_ItemList.end(); ++it)
	{
		if ((*it)->GetIndex() == idx2)
		{
			it = m_ItemList.erase(it);
			break;
		}
	}
	//m_ItemList.erase(remove_if(m_ItemList.begin(), m_ItemList.end(),
	//	[idx1, idx2](const shared_ptr<Item>& item)
	//	{
	//		return item->GetIndex() == idx1 || item->GetIndex() == idx2;
	//	}),
	//	m_ItemList.end());
}

bool Inventory::SearchItem(int index)
{
	for (const auto& item : m_ItemList)
	{
		if (item->GetIndex() == index)
		{
			item->Show();
			return true;
		}
	}

	cout << "해당 인덱스의 아이템을 찾을 수 없습니다." << endl;
	return false;
}

bool Inventory::SortItem(int sortType)
{
	switch (sortType)
	{
	case 1:		// 이름순 정렬
	{
		sort(m_ItemList.begin(), m_ItemList.end(), [](shared_ptr<Item> firstItem, shared_ptr<Item> secondItem)
			{
				return firstItem->GetName() < secondItem->GetName();
			});
	}
	break;
	case 2:		// 레벨순 정렬
	{
		sort(m_ItemList.begin(), m_ItemList.end(), [](shared_ptr<Item> firstItem, shared_ptr<Item> secondItem)
			{
				return firstItem->GetLevel() < secondItem->GetLevel();
			});
	}
	break;
	case 3:		// 등급순 정렬
	{
		sort(m_ItemList.begin(), m_ItemList.end(), [](shared_ptr<Item> firstItem, shared_ptr<Item> secondItem)
			{
				if (firstItem->GetGrade() == 'S')
					return true;

				if (static_cast<int>(firstItem->GetGrade()) < static_cast<int>(secondItem->GetGrade()) && secondItem->GetGrade() != 'S')
					return true;
				return false;
			});
	}
	break;
	default:
		return false;
	}

	return true;
}

void Inventory::Show()
{
	for (auto it : m_ItemList)	// 출력만 할 것이기에 값 복사 해도 괜찮다.
	{
		it->Show();
	}
}

shared_ptr<Item> Inventory::GetItem(int index)
{
	for (int i = 0; i < GetSize(); i++)
	{
		if (m_ItemList[i]->GetIndex() == index - 1)
			return m_ItemList[index - 1];
	}
	return nullptr;
}
