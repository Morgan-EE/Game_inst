#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class ItemType
{
    None,
    Weapon,
    Armor,
    Ring,
    Boots,
    Count, // ������ Ÿ�� ����
};

// �߻� Ŭ����
// �ڱ� �ڽ��� ��ü ���� �Ұ���
class Item
{
public:
    Item()
        : m_Index(0), m_Name(""), m_Level(0), m_Grade(' '), m_Type(ItemType::None)
    {
    }
    Item(int index, string name, int level, char grade)
        : m_Index(index), m_Name(name), m_Level(level), m_Grade(grade), m_Type(ItemType::None)
    {
    }
    ~Item();
    
    virtual void SetStat() = 0;	// �����ۺ� �����Ϸ��� Ư�� ������ �ٸ���.
    virtual void Show() = 0;	// �� �����ۺ� ��� ���� �ٸ�

    void SetType(ItemType type) { m_Type = type; }

    int GetIndex() const { return m_Index; }
    string GetName() const { return m_Name; };
    int GetLevel() const { return m_Level; }
    char GetGrade() const { return m_Grade; }
    void LevelUp();
    ItemType GetType() const { return m_Type; }

protected:
    int m_Level;     // ������ ����
    int m_Index;     // ���� ���̵�
    string m_Name;   // ������ �̸�
    char m_Grade;    // ������ ���
    ItemType m_Type; // ������ Ÿ��
};

class Weapon : public Item
{
public:
    Weapon(int index, std::string name, int level, char grade);
    void SetStat() override;
    void Show() override;

private:
    float m_Damage;
};

class Armor : public Item
{
public:
    Armor(int index, std::string name, int level, char grade);
    void SetStat() override;
    void Show() override;

private:
    float m_Defense;
};

class Ring : public Item
{
public:
    Ring(int index, std::string name, int level, char grade);
    void SetStat() override;
    void Show() override;

private:
    float m_Luck;
};

class Boots : public Item
{
public:
    Boots(int index, std::string name, int level, char grade);
    void SetStat() override;
    void Show() override;

private:
    float m_Speed;
};