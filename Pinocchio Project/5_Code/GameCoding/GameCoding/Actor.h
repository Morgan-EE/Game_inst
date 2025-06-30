#pragma once

class Component;
class Collider;
class Scene;

class Actor
{
public:
	Actor();
	virtual ~Actor();
	
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() { return _layer; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	// 아직 쓰지 말 것
	void RemoveComponentAll();

	// Unity : OnCollisionEnter2D / OnCollisionExit2D
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);
	virtual void OnComponentOverlap(Collider* collider, Collider* other);

	Scene* GetMyScene() { return _myScene; }
	void SetMyScene(Scene* scene) { _myScene = scene; }
	bool isActive = true;
private:
	Scene* _myScene = nullptr;

protected:
	Vec2 _pos = { 0,0 };
	LAYER_TYPE _layer = LAYER_OBJECT;
public:
	vector<Component*> _components;

	//vector<shared_ptr<Component>> _components;

};

