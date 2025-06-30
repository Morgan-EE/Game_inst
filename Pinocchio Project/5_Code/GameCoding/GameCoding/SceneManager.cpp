#include "pch.h"
#include "SceneManager.h"

// Scene
#include "DevScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "CutScene.h"
#include "DeadScene.h"
#include "EndingScene.h"


void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneManager::LateUpdate()
{
	if (_scene)
	{
		_scene->LateUpdate();
	}
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::None:
		break;
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	case SceneType::GameScene:
		newScene = new GameScene();
		break;
	case SceneType::TitleScene:
		newScene = new TitleScene();
		break;
	case SceneType::CutScene:
		newScene = new CutScene();
		break;
	case SceneType::DeadScene:
		newScene = new DeadScene();
		break;
	case SceneType::EndingScene:
		newScene = new EndingScene();
		break;
	default:
		break;
	}

	SAFE_DELETE(_scene);
	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}

void SceneManager::AddLightRegion(int32 x, int32 y)
{
	_light->AddLight(x, y);
}
