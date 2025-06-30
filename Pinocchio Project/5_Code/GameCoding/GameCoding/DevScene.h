#pragma once
#include "Scene.h"

class Actor;
class UI;
class DollCheck;
class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	class TilemapActor* _tilemapActor = nullptr;

private:
	DollCheck* dollcheck = nullptr;

	//Player* player;//삭제가능 GameScene으로 옮김.
};

