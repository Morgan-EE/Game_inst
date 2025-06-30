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
			cout << "�������� �����Ǿ����ϴ�." << endl;
			return;
		}
		else
		{
			++it;
		}
	}
	cout << "�������� ã�� �� �����ϴ�." << endl;
}

void Inventory::GradeUp(int index, shared_ptr<Item> src1, shared_ptr<Item> src2)
{
	// �� �������� �ռ��Ͽ� �� ��ü�� ����
	// �� �������� ����
	// ���� ���� �������� �κ��� ����

	if (src1->GetGrade() != src2->GetGrade())
	{
		cout << "���� ����� �����۸� �ռ� �����մϴ�." << endl;
		return;
	}
	if (src1->GetGrade() == 'S' || src2->GetGrade() == 'S')
	{
		cout << "�̹� �ְ� ����� �������Դϴ�." << endl;
		return;
	}
	if (src1->GetType() != src2->GetType())
	{
		cout << "���� Ÿ���� �����۳����� �ռ��� �����մϴ�." << endl;
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

	// ���ο� �������� �κ��� �߰�
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

	// �� ������ ����
		// ��ᰡ �Ǵ� �������� ����
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

	cout << "�ش� �ε����� �������� ã�� �� �����ϴ�." << endl;
	return false;
}

bool Inventory::SortItem(int sortType)
{
	switch (sortType)
	{
	case 1:		// �̸��� ����
	{
		sort(m_ItemList.begin(), m_ItemList.end(), [](shared_ptr<Item> firstItem, shared_ptr<Item> secondItem)
			{
				return firstItem->GetName() < secondItem->GetName();
			});
	}
	break;
	case 2:		// ������ ����
	{
		sort(m_ItemList.begin(), m_ItemList.end(), [](shared_ptr<Item> firstItem, shared_ptr<Item> secondItem)
			{
				return firstItem->GetLevel() < secondItem->GetLevel();
			});
	}
	break;
	case 3:		// ��޼� ����
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
	for (auto it : m_ItemList)	// ��¸� �� ���̱⿡ �� ���� �ص� ������.
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
