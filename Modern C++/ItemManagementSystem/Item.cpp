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
        cout << "이미 최고 레벨입니다." << endl;
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
        cout << "무기의 공격력을 입력하세요. (0 ~ 100 까지 설정 가능)" << endl;
        cout << "공격력: ";
        if (cin >> m_Damage && m_Damage >= 0 && m_Damage <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 까지의 수치로만 설정 가능합니다. 다시 입력해주세요." << endl;
            cin.clear();  // 입력 버퍼 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼 비우기
        }
    }
}

void Weapon::Show()
{
    Item::Show();
    cout << ", 공격력: " << m_Damage << endl;
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
        cout << "방어구의 방어력을 입력하세요. (0 ~ 100 까지 설정 가능)" << endl;
        cout << "방어력: ";
        if (cin >> m_Defense && m_Defense >= 0 && m_Defense <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 까지의 수치로만 설정 가능합니다. 다시 입력해주세요." << endl;
            cin.clear();  // 입력 버퍼 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼 비우기
        }
    }
}

void Armor::Show()
{
    Item::Show();
    cout << ", 방어력: " << m_Defense << endl;
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
        cout << "반지의 운(Luck) 스탯을 입력하세요. (0 ~ 100 까지 설정 가능)" << endl;
        cout << "운: ";
        if (cin >> m_Luck && m_Luck >= 0 && m_Luck <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 까지의 수치로만 설정 가능합니다. 다시 입력해주세요." << endl;
            cin.clear();  // 입력 버퍼 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼 비우기
        }
    }
}

void Ring::Show()
{
    Item::Show();
    cout << ", 운: " << m_Luck << endl;
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
        cout << "신발의 스피드(Speed) 스탯을 입력하세요. (0 ~ 100 까지 설정 가능)" << endl;
        cout << "스피드: ";
        if (cin >> m_Speed && m_Speed >= 0 && m_Speed <= 100)
        {
            break;
        }
        else
        {
            cout << "0 ~ 100 까지의 수치로만 설정 가능합니다. 다시 입력해주세요." << endl;
            cin.clear();  // 입력 버퍼 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼 비우기
        }
    }
}

void Boots::Show()
{
    Item::Show();
    cout << ", 스피드: " << m_Speed << endl;
}
