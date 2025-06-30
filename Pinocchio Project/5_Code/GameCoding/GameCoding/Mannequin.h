#pragma once
#include "SpriteActor.h"

enum class MannequinDir
{
	Left,
	Right,
};

class Player;
class Mannequin : public SpriteActor
{
	using Super = SpriteActor;
public:
	Mannequin();
	virtual ~Mannequin() override;
	void BeginPlay() override;
	void Tick() override;
	void Render(HDC hdc) override;


	/// <summary>
	///  플레이어를 받아옴. 
	/// </summary>
	/// <param name="player"></param>
	void SetActive(Player* player);
	bool IsActive() { return _isActive; }
private:
	bool _isActive = false;
	bool _isMove = false;
	Player* _player = nullptr;
	MannequinDir _dir = MannequinDir::Left;
	float _speed = 130.f;
};

