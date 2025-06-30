#include "pch.h"
#include <Windows.h>
#include "SelectStage.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "SceneManager.h"

#include "InputManager.h"


#include "CollisionManager.h"
#include "Collider.h"
#include "BoxCollider.h"


void SelectStage::DrawRectangle(HDC hdc, int x, int y, int width, int height)
{
	// �簢�� �׸���
	RECT rect = { 50, 50, 200, 200 }; // �»�� (50, 50), ���ϴ� (200, 200)�� �簢��
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

	// ����̽� ���ؽ�Ʈ ����

}

SelectStage::SelectStage()
{
	//�������� �޾Ƽ� �ʱ�ȭ
	//GET_SINGLE(ResourceManager)->
}

SelectStage::~SelectStage()
{

}

void SelectStage::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();

		// camera���� ����
		GET_SINGLE(SceneManager)->SetBackgroundSize(size);

		background->SetPos(Vec2(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2)));

		// _actors.push_back(background);
		// SelectStage(background);

	}

	Super::Init();
}

void SelectStage::Update()
{
	Super::Update();

	if(GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		isDrawRectangle = !isDrawRectangle;
	}

}

void SelectStage::Render(HDC hdc)
{
	Super::Render(hdc);


	//if (isDrawRectangle)
	//{
	//	// �簢�� �׸���
	//	RECT rect = { 50, 50, 200, 200 }; // �»�� (50, 50), ���ϴ� (200, 200)�� �簢��
	//	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	//}


}

