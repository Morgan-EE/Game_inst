#pragma once
#include "ResourceBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;
	wstring name;
	Vec2Int size = {};		// 이미지 내 한 칸의 사이즈

	// 텍스텨에서의 해당 라인에 시작점과 끝 [start,end]
	int32 start = 0;
	int32 end = 0;
	int32 line = 0;

	float duration = 1.f; // 총 애니메이션 시간
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

