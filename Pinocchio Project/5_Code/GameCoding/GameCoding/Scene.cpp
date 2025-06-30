#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "UI.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

// saveData 입출력
#include<fstream>

Scene::Scene()
{
	_sceneType = SceneType::None;
}

Scene::~Scene()
{
	
}

void Scene::Init()
{
	// Actor BeginPlay
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->BeginPlay();
		}
	}

	// UI BeginPlay
	for (UI* ui : _uis)
	{
		ui->BeginPlay();
	}
}

void Scene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	GET_SINGLE(CollisionManager)->Update();

	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Tick(); 
		}
	}
	for (UI* ui : _uis)
	{
		if (_uis.size() != 0)
		{
			ui->Tick();
		}
	}
}

void Scene::Render(HDC hdc)
{
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			// 이미지 경로가 제대로 설정되어 있지 않은면 널값 참조로 오류가 날 수 있음!
			// 오류가 난다면 이미지 경로를 다시 한번 살펴볼 것.
			actor->Render(hdc);
		}
	}
	for (UI* ui : _uis)
	{
		ui->Render(hdc);
	}
}

void Scene::LateUpdate()
{
	if (_sceneType != SceneType::None)
	{
		GET_SINGLE(SceneManager)->SetCameraPos({ 0,0 });
		GET_SINGLE(SceneManager)->ChangeScene(_sceneType);
	}
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	vector<Actor*>& v = _actors[actor->GetLayer()];
	//actor->RemoveComponent()
	actor->RemoveComponentAll();

	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}

void Scene::AddUI(UI* ui)
{
	if (ui == nullptr)
		return;

	_uis.push_back(ui);
}

void Scene::RemoveUI(UI* ui)
{
	if (ui == nullptr)
		return;

	_uis.erase(std::remove(_uis.begin(), _uis.end(), ui), _uis.end());
}

void Scene::SaveData(string key, string value)
{
	_saveData[key] = value;
}

void Scene::SaveData()
{
	std::ofstream saveData("saveData.txt", std::ios::trunc);

	for (auto i = _saveData.begin(); i != _saveData.end(); i++)
	{
		string key = i->first;
		string value = i->second;

		if (saveData.is_open())    //파일이 열렸는지 확인
		{
			saveData << key;
			saveData << "\n";
			saveData << value;
			saveData << "\n";
		}
	}
	saveData.close();    //파일 닫기
}

void Scene::LoadData()
{
	std::ifstream inputFile("saveData.txt");

	if (!inputFile.is_open()) {
		return;
	}

	std::string key;
	std::string value;
	while (inputFile)
	{
		getline(inputFile, key);
		getline(inputFile, value);

		_saveData.insert(make_pair(key, value));
	}
}
