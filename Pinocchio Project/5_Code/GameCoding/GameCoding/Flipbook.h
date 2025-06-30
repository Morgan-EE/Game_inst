#pragma once
#include "ResourceBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;
	wstring name;
	Vec2Int size = {};		// �̹��� �� �� ĭ�� ������

	// �ؽ��߿����� �ش� ���ο� �������� �� [start,end]
	int32 start = 0;
	int32 end = 0;
	int32 line = 0;

	float duration = 1.f; // �� �ִϸ��̼� �ð�
	bool loop = true;
};

class Flipbook : public ResourceBase
{
public:
	Flipbook();
	virtual ~Flipbook() override;

	
	void SetInfo(const FlipbookInfo& info) { _info = info; }
	const FlipbookInfo& GetInfo() { return _info; }
private:
	FlipbookInfo _info;

};

