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
			// �ý��� ����
			cout << "�ý����� �����մϴ�." << endl;
			return 0;
		case 1:
			// ������ �߰�
			AddItem(inven);
			break;
		case 2:
			// ������ ����
			DeleteItem(inven);
			break;
		case 3:
			// ������ �˻�
			SearchItem(inven);
			break;
		case 4:
			// ������ �ռ�!
			GradeUpItem(inven);
			break;
		case 5:
			// ������ ����
			SortItem(inven);
			break;
		case 6:
			// ���� ������ ��� ���
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
	cout << "                       [ �κ��丮 - ��ȭ�ϱ� ]\n" << endl;
	cout << "1. ������ �߰� 2. ���� 3. �˻� 4. �ռ� 5. ���� 6. ��Ϻ��� 0. ������" << endl;
	cout << "--------------------------------------------------------------------\n";
}


int GetInput()
{
	int output = 0;

	cout << "���ϴ� �޴��� ���ڸ� �Է����ּ���. : ";
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

	cout << "������ �߰� �޴��� �����Ͽ����ϴ�." << endl;

	while (true)
	{
		// ����, ��, ����, �Ź� �� ����
		cout << "�߰��� ������ ������ �����ϼ���\n" << endl;
		cout << "1. ���� 2. �� 3. ���� 4. �Ź� 0. ���" << endl;
		cin >> input;

		if (input >= 0 && input <= static_cast<int>(ItemType::Count))
		{
			if (input == 0)
			{
				cout << "������ �߰��� ����մϴ�." << endl;
				return;
			}
			itemType = static_cast<ItemType>(input);
			break;
		}
		cout << "0 ~ " << static_cast<int>(ItemType::Count) << " ������ ���ڸ� �Է����ּ���." << endl;
	}

	// Call InputItemInfo for common item information
	InputItemInfo(name, level, grade);

	switch (itemType)
	{
	case ItemType::Weapon:
		cout << "���� �߰���" << endl;
		inven->AddItem(make_shared<Weapon>(inven->m_ID++, name, level, grade));
		// ���� �߰�
		break;
	case ItemType::Armor:
		cout << "�� �߰���" << endl;
		inven->AddItem(make_shared<Armor>(inven->m_ID++, name, level, grade));
		// �� �߰�
		break;
	case ItemType::Ring:
		cout << "���� �߰���" << endl;
		inven->AddItem(make_shared<Ring>(inven->m_ID++, name, level, grade));
		// ���� �߰�
		break;
	case ItemType::Boots:
		cout << "���� �߰���" << endl;
		inven->AddItem(make_shared<Boots>(inven->m_ID++, name, level, grade));
		// ���� �߰�
		break;
	default:
		break;
	}
}

void DeleteItem(shared_ptr<Inventory> inven)
{
	shared_ptr<Item> item = nullptr;
	int input = -1;

	cout << "������ ���� �޴��� �����Ͽ����ϴ�." << endl;

	if (inven->GetSize() == 0)
	{
		cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
		return;
	}

	while (true)
	{
		cout << "������ �������� ���̵� �Է����ּ���." << endl;
		cout << "ID: ";
		cin >> input;

		item = inven->GetItem(input);

		if (item != nullptr)
		{
			break;
		}
		cout << "�������� �ʴ� �������Դϴ�. �ùٸ� ���̵� �Է����ּ���." << endl;
	}

	inven->Delete(input);
}

void SearchItem(shared_ptr<Inventory> inven)
{
	int input = -1;

	cout << "������ �˻� �޴��� �����Ͽ����ϴ�.\n";
	cout << "�˻��� �������� ID �� �Է��ϼ���.\n";
	cout << "ID: ";
	cin >> input;

	if (!inven->SearchItem(input))
		cout << "�κ��丮�� �������� �ʴ� �������Դϴ�.\n";
}

void SortItem(shared_ptr<Inventory> inven)
{
	int input = -1;

	cout << "������ ���� �޴��� �����Ͽ����ϴ�.\n";
	cout << "���� ������ �������ּ���. (1. �̸��� 2. ������ 3. ��޼�)\n";
	cout << "�Է�: ";
	cin >> input;

	if (!inven->SortItem(input))
		cout << "������ ���Ŀ� �����Ͽ����ϴ�.\n";
}


void GradeUpItem(shared_ptr<Inventory> inven)
{
	shared_ptr<Item> mainItem = nullptr;
	shared_ptr<Item> srcItem = nullptr;

	int mainItemID = -1, srcItemID = -1;

	cout << "������ �ռ� �޴��� �����Ͽ����ϴ�." << endl;

	if (inven->GetSize() == 0)
	{
		cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
		return;
	}

	while (true)
	{
		cout << "���� ����� �������� 2�� �Է��ϼ���." << endl;
		cout << "��ȭ�� ������ ID: ";
		cin >> mainItemID;
		cout << "��� ������ ID: ";
		cin >> srcItemID;

		if (mainItemID == srcItemID)
		{
			cout << "���� �ٸ� �������� �Է��ؾ� �մϴ�." << endl;
			continue;
		}

		mainItem = inven->GetItem(mainItemID);
		srcItem = inven->GetItem(srcItemID);

		if (mainItem != nullptr && srcItem != nullptr)
		{
			break;
		}
		cout << "�������� �ʴ� �������Դϴ�. �ùٸ� ���̵� �Է����ּ���." << endl;
	}

	inven->GradeUp(inven->m_ID, mainItem, srcItem);
}

void ShowItem(shared_ptr<Inventory> inven)
{
	cout << "������ ��� ��� �޴��� �����Ͽ����ϴ�." << endl;

	if (inven->GetSize() == 0)
	{
		cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
		return;
	}
	inven->Show();
}

void InputItemInfo(string& name, int& level, char& grade)
{
	while (true)
	{
		cin.ignore();	// �Է� ���� ����
		cout << "�������� �̸��� �Է��ϼ���. ( 1 ~ 20�� �̳� )" << endl;
		cout << "�̸�: ";
		getline(cin, name);

		if (name.size() <= 20)
		{
			break;
		}
		cout << "1 ~ 20�� �̳��θ� �Է��� �����մϴ�. �ٽ� �Է����ּ���." << endl;
	}

	while (true)
	{
		cout << "�������� ������ �Է��ϼ���. ( 1 ~ 10 ���� )" << endl;
		cout << "����: ";
		cin >> level;

		if (level >= 1 && level <= 10)
		{
			break;
		}
		cout << "1 ~ 10 ������ ���ڸ� �Է� �����մϴ�. �ٽ� �Է����ּ���." << endl;
	}

	while (true)
	{
		cout << "�������� ����� �Է��ϼ���. (��� ���� - S, A, B, C)" << endl;
		cout << "���: ";
		cin >> grade;

		if (grade == 'S' || grade == 'A' || grade == 'B' || grade == 'C')
		{
			break;
		}

		cout << "S, A, B, C �߿����� ������ �����մϴ�." << endl;
	}
}