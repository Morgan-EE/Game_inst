#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "Collider.h"
#include "Scene.h"
#include "SceneManager.h"
Actor::Actor()
{

}

Actor::~Actor()
{

}

void Actor::BeginPlay()
{
	_myScene = GET_SINGLE(SceneManager)->GetCurrentScene();
	for (Component* component : _components)
	{
		component->BeginPlay();
	}
}
void Actor::Tick()
{
	for (Component* component : _components)
	{
		component->TickComponent();
	}
}
void Actor::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void Actor::AddComponent(Component* component)
{
	if (component == nullptr)
		return;
	component->SetOwner(this);
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto findIt = std::find(_components.begin(), _components.end(), component);
	if (findIt == _components.end())
		return;
	//SAFE_DELETE(component);
	_components.erase(findIt);
}


void Actor::RemoveComponentAll()
{
 	for (Component* component : _components)
	{
		RemoveComponent(component);
		//SAFE_DELETE(component);
	}

	_components.clear();
}

void Actor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

}

void Actor::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}

void Actor::OnComponentOverlap(Collider* collider, Collider* other)
{

}
