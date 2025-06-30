#pragma once

class UI;
class Actor;
class UI;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void LateUpdate();

public:
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddUI(UI* ui);
	void RemoveUI(UI* ui);

	unordered_map<string, string> GetSaveData() { return _saveData; }

	bool isTabToggle = false;

	void SaveData(string key, string value); // 각 데이터 저장
	void SaveData(); // 모든 데이터를 파일에 저장
public:
	vector<Actor*> _actors[LAYER_MAXCOUNT];
	vector<UI*> _uis;

protected:
	std::unordered_map<string, string> _saveData;
	wstring _currentText;

	//void SaveData(); // 모든 데이터를 파일에 저장
	void LoadData();

public:
	SceneType _sceneType;
};

