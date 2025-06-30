#include "Item.h"
#include "Inventory.h"
using namespace std;

void PrintMenu();
int GetInput();
void AddItem(shared_ptr<Inventory> inven);
void DeleteItem(shared_ptr<Inventory> inven);
void SearchItem(shared_ptr<Inventory> inven);
void SortItem(shared_ptr<Inventory> inven);
void GradeUpItem(shared_ptr<Inventory> inven);
void ShowItem(shared_ptr<Inventory> inven);
void InputItemInfo(string& name, int& level, char& grade);

int main()
{
	shared_ptr<Inventory> inven = make_shared<Inventory>();

	while (true)
	{
		PrintMenu();
		switch (GetInput())
		{
		case 0:
			// 시스템 종료
			cout << "시스템을 종료합니다." << endl;
			return 0;
		case 1:
			// 아이템 추가
			AddItem(inven);
			break;
		case 2:
			// 아이템 삭제
			DeleteItem(inven);
			break;
		case 3:
			// 아이템 검색
			SearchItem(inven);
			break;
		case 4:
			// 아이템 합성!
			GradeUpItem(inven);
			break;
		case 5:
			// 아이템 정렬
			SortItem(inven);
			break;
		case 6:
			// 소지 아이템 목록 출력
			ShowItem(inven);
			break;
		default:
			break;
		}
		
	}

	return 0;
}

void PrintMenu()
{
	cout << "--------------------------------------------------------------------\n";
	cout << "                       [ 인벤토리 - 강화하기 ]\n" << endl;
	cout << "1. 아이템 추가 2. 삭제 3. 검색 4. 합성 5. 정렬 6. 목록보기 0. 나가기" << endl;
	cout << "--------------------------------------------------------------------\n";
}


int GetInput()
{
	int output = 0;

	cout << "원하는 메뉴의 숫자를 입력해주세요. : ";
	cin >> output;
	cout << "\n";
	return output;
}


void AddItem(shared_ptr<Inventory> inven)
{

	int input = 0;
	ItemType itemType = {};
	string name = {};
	int level = 0;
	char grade = {};
	float damage = 0.0;

	cout << "아이템 추가 메뉴를 선택하였습니다." << endl;

	while (true)
	{
		// 무기, 방어구, 반지, 신발 중 선택
		cout << "추가할 아이템 종류를 선택하세요\n" << endl;
		cout << "1. 무기 2. 방어구 3. 반지 4. 신발 0. 취소" << endl;
		cin >> input;

		if (input >= 0 && input <= static_cast<int>(ItemType::Count))
		{
			if (input == 0)
			{
				cout << "아이템 추가를 취소합니다." << endl;
				return;
			}
			itemType = static_cast<ItemType>(input);
			break;
		}
		cout << "0 ~ " << static_cast<int>(ItemType::Count) << " 사이의 숫자를 입력해주세요." << endl;
	}

	// Call InputItemInfo for common item information
	InputItemInfo(name, level, grade);

	switch (itemType)
	{
	case ItemType::Weapon:
		cout << "무기 추가됨" << endl;
		inven->AddItem(make_shared<Weapon>(inven->m_ID++, name, level, grade));
		// 무기 추가
		break;
	case ItemType::Armor:
		cout << "방어구 추가됨" << endl;
		inven->AddItem(make_shared<Armor>(inven->m_ID++, name, level, grade));
		// 방어구 추가
		break;
	case ItemType::Ring:
		cout << "반지 추가됨" << endl;
		inven->AddItem(make_shared<Ring>(inven->m_ID++, name, level, grade));
		// 반지 추가
		break;
	case ItemType::Boots:
		cout << "부츠 추가됨" << endl;
		inven->AddItem(make_shared<Boots>(inven->m_ID++, name, level, grade));
		// 부츠 추가
		break;
	default:
		break;
	}
}

void DeleteItem(shared_ptr<Inventory> inven)
{
	shared_ptr<Item> item = nullptr;
	int input = -1;

	cout << "아이템 삭제 메뉴를 선택하였습니다." << endl;

	if (inven->GetSize() == 0)
	{
		cout << "인벤토리가 비어있습니다." << endl;
		return;
	}

	while (true)
	{
		cout << "삭제할 아이템의 아이디를 입력해주세요." << endl;
		cout << "ID: ";
		cin >> input;

		item = inven->GetItem(input);

		if (item != nullptr)
		{
			break;
		}
		cout << "존재하지 않는 아이템입니다. 올바른 아이디를 입력해주세요." << endl;
	}

	inven->Delete(input);
}

void SearchItem(shared_ptr<Inventory> inven)
{
	int input = -1;

	cout << "아이템 검색 메뉴를 선택하였습니다.\n";
	cout << "검색할 아이템의 ID 를 입력하세요.\n";
	cout << "ID: ";
	cin >> input;

	if (!inven->SearchItem(input))
		cout << "인벤토리에 존재하지 않는 아이템입니다.\n";
}

void SortItem(shared_ptr<Inventory> inven)
{
	int input = -1;

	cout << "아이템 정렬 메뉴를 선택하였습니다.\n";
	cout << "정렬 기준을 선택해주세요. (1. 이름순 2. 레벨순 3. 등급순)\n";
	cout << "입력: ";
	cin >> input;

	if (!inven->SortItem(input))
		cout << "아이템 정렬에 실패하였습니다.\n";
}


void GradeUpItem(shared_ptr<Inventory> inven)
{
	shared_ptr<Item> mainItem = nullptr;
	shared_ptr<Item> srcItem = nullptr;

	int mainItemID = -1, srcItemID = -1;

	cout << "아이템 합성 메뉴를 선택하였습니다." << endl;

	if (inven->GetSize() == 0)
	{
		cout << "인벤토리가 비어있습니다." << endl;
		return;
	}

	while (true)
	{
		cout << "같은 등급의 아이템을 2개 입력하세요." << endl;
		cout << "강화할 아이템 ID: ";
		cin >> mainItemID;
		cout << "재료 아이템 ID: ";
		cin >> srcItemID;

		if (mainItemID == srcItemID)
		{
			cout << "서로 다른 아이템을 입력해야 합니다." << endl;
			continue;
		}

		mainItem = inven->GetItem(mainItemID);
		srcItem = inven->GetItem(srcItemID);

		if (mainItem != nullptr && srcItem != nullptr)
		{
			break;
		}
		cout << "존재하지 않는 아이템입니다. 올바른 아이디를 입력해주세요." << endl;
	}

	inven->GradeUp(inven->m_ID, mainItem, srcItem);
}

void ShowItem(shared_ptr<Inventory> inven)
{
	cout << "아이템 목록 출력 메뉴를 선택하였습니다." << endl;

	if (inven->GetSize() == 0)
	{
		cout << "인벤토리가 비어있습니다." << endl;
		return;
	}
	inven->Show();
}

void InputItemInfo(string& name, int& level, char& grade)
{
	while (true)
	{
		cin.ignore();	// 입력 버퍼 비우기
		cout << "아이템의 이름을 입력하세요. ( 1 ~ 20자 이내 )" << endl;
		cout << "이름: ";
		getline(cin, name);

		if (name.size() <= 20)
		{
			break;
		}
		cout << "1 ~ 20자 이내로만 입력이 가능합니다. 다시 입력해주세요." << endl;
	}

	while (true)
	{
		cout << "아이템의 레벨을 입력하세요. ( 1 ~ 10 사이 )" << endl;
		cout << "레벨: ";
		cin >> level;

		if (level >= 1 && level <= 10)
		{
			break;
		}
		cout << "1 ~ 10 사이의 숫자만 입력 가능합니다. 다시 입력해주세요." << endl;
	}

	while (true)
	{
		cout << "아이템의 등급을 입력하세요. (등급 종류 - S, A, B, C)" << endl;
		cout << "등급: ";
		cin >> grade;

		if (grade == 'S' || grade == 'A' || grade == 'B' || grade == 'C')
		{
			break;
		}

		cout << "S, A, B, C 중에서만 설정이 가능합니다." << endl;
	}
}