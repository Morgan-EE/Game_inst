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
    Count, // 아이템 타입 숫자
};

// 추상 클래스
// 자기 자신의 객체 생성 불가능
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
    
    virtual void SetStat() = 0;	// 아이템별 설정하려는 특정 스탯이 다르다.
    virtual void Show() = 0;	// 각 아이템별 출력 정보 다름

    void SetType(ItemType type) { m_Type = type; }

    int GetIndex() const { return m_Index; }
    string GetName() const { return m_Name; };
    int GetLevel() const { return m_Level; }
    char GetGrade() const { return m_Grade; }
    void LevelUp();
    ItemType GetType() const { return m_Type; }

protected:
    int m_Level;     // 아이템 레벨
    int m_Index;     // 고유 아이디
    string m_Name;   // 아이템 이름
    char m_Grade;    // 아이템 등급
    ItemType m_Type; // 아이템 타입
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