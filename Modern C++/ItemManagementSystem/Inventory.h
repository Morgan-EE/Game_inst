#pragma once
#include <vector>
#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	void AddItem(shared_ptr<Item> item);	// 인벤에 특정 종류의 아이템 하나 추가
	void Delete(int index);		// 가지고 있는 아이템 하나 삭제
	void GradeUp(int index, shared_ptr<Item> src1, shared_ptr<Item> src2);	// 두 아이템 합성으로 아이템 등급 상승
	bool SearchItem(int index);
	bool SortItem(int sortType);
	void Show();	// 소지 아이템 목록 출력

	shared_ptr<Item> GetItem(int index);

	int GetSize() { return m_ItemList.size(); }		// 소지 아이템 수를 리턴

public:
	int m_ID;

private:
	vector<shared_ptr<Item>> m_ItemList;
};
