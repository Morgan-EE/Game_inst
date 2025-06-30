#pragma once
#include "Scene.h"
class Sprite;
class EndingScene : public Scene
{
	using Super = Scene;
public:
	EndingScene();
	virtual ~EndingScene() override;

private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void LateUpdate();

private:
	void ReadIntroText();

	// ��ư ���� ��� ����Ǵ� �Լ���
	void NextPage();

private:
	vector<wstring> _introText;

	int32 _lastPageIndex;
	int32 _pageIndex;

	vector<Sprite*> cutSceneSpriteArray;
	vector<Actor*> cutSceneActors;
};

