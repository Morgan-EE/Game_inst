#include "pch.h"
#include "DeadScene.h"

#include "SpriteActor.h"
#include "Sprite.h"

// Manager
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

// UI
#include "Button.h"

DeadScene::DeadScene()
{

}

DeadScene::~DeadScene()
{

}

void DeadScene::Init()
{
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"YouDied", L"Sprite\\UI\\YouDied.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"YouDied", GET_SINGLE(ResourceManager)->GetTexture(L"YouDied"));

		GET_SINGLE(SoundManager)->Init();
		GET_SINGLE(SoundManager)->LoadSound(L"Dead", "Sounds\\ETC\\player death.wav", SoundType::SFX);
		GET_SINGLE(SoundManager)->PlaySFXSound(L"Dead", 8);

		Sprite* titleSprite = GET_SINGLE(ResourceManager)->GetSprite(L"YouDied");

		SpriteActor* mainTitle = new SpriteActor();
		mainTitle->SetSprite(titleSprite);
		mainTitle->SetLayer(LAYER_OBJECT);
		//const Vec2Int size = titleSprite->GetSize();

		mainTitle->SetPos(Vec2(0, 0));
		AddActor(mainTitle);
	}

	// 재시작 버튼
	{
		Button* restartButton = new Button();
		restartButton->SetPos({ (GWinSizeX / 2) - 10 , 715 });
		_uis.push_back(restartButton);
		restartButton->SetSize(Vec2Int(130, 50));
		restartButton->AddOnClickDelegate(this, &DeadScene::goToGameScene);
	}
	//메인메뉴로 이동
	{
		Button* goToTitleButton = new Button();
		goToTitleButton->SetPos({ (GWinSizeX / 2) - 10 , 770 });
		_uis.push_back(goToTitleButton);
		goToTitleButton->SetSize(Vec2Int(130, 50));
		goToTitleButton->AddOnClickDelegate(this, &DeadScene::goToTitleScene);
	}
// 	GET_SINGLE(SoundManager)->Init();
// 	GET_SINGLE(SoundManager)->LoadSound(L"Start", "Sound\\BGM.wav", SoundType::BGM);
	//titleImage.SetPos(Vec2{ 500, 500 });
	Super::Init();
}

void DeadScene::Update()
{
	Super::Update();
	
}

void DeadScene::Render(HDC hdc)
{

	Super::Render(hdc);
}

void DeadScene::LateUpdate()
{
	Super::LateUpdate();
}

void DeadScene::ReadIntroText()
{

}

void DeadScene::goToGameScene()
{
	//GET_SINGLE(SoundManager)->Release();

	_sceneType = SceneType::GameScene;

}

void DeadScene::goToTitleScene()
{
	GET_SINGLE(SoundManager)->Release();
	/*GET_SINGLE(SoundManager)->Init();
	GET_SINGLE(SoundManager)->LoadSound(L"Start", "Sounds\\Main\\Title.wav", SoundType::BGM);
	GET_SINGLE(SoundManager)->PlayBackgroundSound(L"Start");*/
	_sceneType = SceneType::TitleScene;
}

