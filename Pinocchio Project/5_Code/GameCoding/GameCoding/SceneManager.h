#pragma once
#include "Light.h"

class Scene;
class SceneManager
{
	DECLARE_SINGLE(SceneManager);
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void LateUpdate();

	void Clear();

public:
	void ChangeScene(SceneType sceneType);
	Scene* GetCurrentScene() { return _scene; }
private:
	Scene* _scene = {};
	SceneType _sceneType = SceneType::None;


	// Camera
public:
	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 pos) { _cameraPos.x = pos.x; }

	void SetBackgroundSize(Vec2Int size) { _backgroundSize = size; }
	Vec2Int GetBackgroundSize() { return _backgroundSize; }

	void AddLightRegion(int32 x, int32 y);
	void SetLight(Light* light) { _light = light; }

private:
	Vec2 _cameraPos = { 0,0 };
	Vec2Int _backgroundSize = { 0,0 };

	Light* _light;
};

