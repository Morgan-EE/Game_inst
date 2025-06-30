#include "Item.h"
using namespace std;

Item::~Item()
{
}

void Item::Show()
{
    cout << "ID: " << m_Index + 1 << ", Name: " << m_Name << ", Level: " << m_Level << ", Grade: '" << static_cast<char>(m_Grade) << "'";
}

void Item::LevelUp()
{
    if (m_Level < 10)
    {
        m_Level++;
    }
    else
    {
        cout << "�̹� �ְ� �����Դϴ�." << endl;
    }
}


Weapon::Weapon(int index, string name, int level, char grade)
    : Item(index, move(name), level, grade), m_Damage(0)
{
    SetType(ItemType::Weapon);
}

void Weapon::SetStat()
{
    while (true)
    {
        cout << "������ ���ݷ��� �Է��ϼ���. (0 ~ 100 ���� ���� ����)" << endl;
        cout << "���ݷ�: ";
        if (cin >> m_Damage && m_Damage >= 0 && m_Damage <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 ������ ��ġ�θ� ���� �����մϴ�. �ٽ� �Է����ּ���." << endl;
            cin.clear();  // �Է� ���� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ���� ����
        }
    }
}

void Weapon::Show()
{
    Item::Show();
    cout << ", ���ݷ�: " << m_Damage << endl;
}

// Armor.cpp
Armor::Armor(int index, string name, int level, char grade)
    : Item(index, move(name), level, grade), m_Defense(0)
{
    SetType(ItemType::Armor);
}

void Armor::SetStat()
{
    while (true)
    {
        cout << "���� ������ �Է��ϼ���. (0 ~ 100 ���� ���� ����)" << endl;
        cout << "����: ";
        if (cin >> m_Defense && m_Defense >= 0 && m_Defense <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 ������ ��ġ�θ� ���� �����մϴ�. �ٽ� �Է����ּ���." << endl;
            cin.clear();  // �Է� ���� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ���� ����
        }
    }
}

void Armor::Show()
{
    Item::Show();
    cout << ", ����: " << m_Defense << endl;
}

// Ring.cpp
Ring::Ring(int index, string name, int level, char grade)
    : Item(index, move(name), level, grade), m_Luck(0)
{
    SetType(ItemType::Ring);
}

void Ring::SetStat()
{
    while (true)
    {
        cout << "������ ��(Luck) ������ �Է��ϼ���. (0 ~ 100 ���� ���� ����)" << endl;
        cout << "��: ";
        if (cin >> m_Luck && m_Luck >= 0 && m_Luck <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 ������ ��ġ�θ� ���� �����մϴ�. �ٽ� �Է����ּ���." << endl;
            cin.clear();  // �Է� ���� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ���� ����
        }
    }
}

void Ring::Show()
{
    Item::Show();
    cout << ", ��: " << m_Luck << endl;
}

Boots::Boots(int index, string name, int level, char grade)
    : Item(index, move(name), level, grade), m_Speed(0)
{
    SetType(ItemType::Boots);
}

void Boots::SetStat()
{
    while (true)
    {
        cout << "�Ź��� ���ǵ�(Speed) ������ �Է��ϼ���. (0 ~ 100 ���� ���� ����)" << endl;
        cout << "���ǵ�: ";
        if (cin >> m_Speed && m_Speed >= 0 && m_Speed <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 ������ ��ġ�θ� ���� �����մϴ�. �ٽ� �Է����ּ���." << endl;
            cin.clear();  // �Է� ���� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ���� ����
        }
    }
}

void Boots::Show()
{
    Item::Show();
    cout << ", ���ǵ�: " << m_Speed << endl;
}
