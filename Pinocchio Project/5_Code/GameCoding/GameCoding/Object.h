#pragma once

enum class ObjectType
{
	None,
	Player,
	Monster,
	Projectile,
};

class Object
{
public:
	Object(ObjectType type);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	Pos GetPos() { return _pos; }
	void SetPos(Pos pos) { _pos = pos; }
	ObjectType GetObjectType() { return _type; }
protected:
	ObjectType _type = ObjectType::None;
	Vector _pos = {};
	Stat _stat = {};

};

