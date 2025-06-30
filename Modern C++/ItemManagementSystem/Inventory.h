#pragma once
#include <vector>
#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	void AddItem(shared_ptr<Item> item);	// �κ��� Ư�� ������ ������ �ϳ� �߰�
	void Delete(int index);		// ������ �ִ� ������ �ϳ� ����
	void GradeUp(int index, shared_ptr<Item> src1, shared_ptr<Item> src2);	// �� ������ �ռ����� ������ ��� ���
	bool SearchItem(int index);
	bool SortItem(int sortType);
	void Show();	// ���� ������ ��� ���

	shared_ptr<Item> GetItem(int index);

	int GetSize() { return m_ItemList.size(); }		// ���� ������ ���� ����

public:
	int m_ID;

private:
	vector<shared_ptr<Item>> m_ItemList;
};
