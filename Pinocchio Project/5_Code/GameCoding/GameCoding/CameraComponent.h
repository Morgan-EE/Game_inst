#pragma once
#include "Component.h"
class CameraComponent : public Component
{
public:
	void BeginPlay() override;
	void TickComponent() override;
	void Render(HDC hdc) override;

	void SetCameraPosition(Vec2 pos) { _cameraPos = pos; }

private:
	Vec2 _cameraPos = {};
	float _cameraSpeed = 2.f;
};

