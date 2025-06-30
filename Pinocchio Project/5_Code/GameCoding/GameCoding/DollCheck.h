#pragma once

class Doll;
class DollCheck
{
public:
	DollCheck();
	~DollCheck();

	void Init();
	void Tick();

	void AddDoll(Doll* doll);

	Doll* GetDoll(int32 index) { return _dolls[index]; }

private:
	vector<Doll*> _dolls = {};
	bool _isActive[4];
	// 현재 입력될 커서
	int32 _cursor = 0;


	int32 _count = 0;
};

