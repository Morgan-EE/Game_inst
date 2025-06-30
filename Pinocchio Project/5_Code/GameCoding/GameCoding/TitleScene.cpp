#include "pch.h"
#include "TitleScene.h"

#include "SpriteActor.h"
#include "Sprite.h"

// Manager
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

// UI
#include "Button.h"

//FMOD_SYSTEM _system;

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Init()
{
	//GET_SINGLE(SoundManager)->SetVolume(1.0f);
	//float *sVolume = fVolume;
	GET_SINGLE(SoundManager)->Init();
	GET_SINGLE(SoundManager)->LoadSound(L"Start", "Sounds\\Main\\Title.wav", SoundType::BGM);

	//result = _system->createSound("ddd.wav", FMOD_LOOP_NORMAL,0, &sound);
	//GET_SINGLE(SoundManager)->GetVolume(&volume);
	GET_SINGLE(SoundManager)->PlayBackgroundSound(L"Start");


	{
		float fVolume;
		GET_SINGLE(SoundManager)->SetVolume(0.1f);
		GET_SINGLE(SoundManager)->GetVolume(&fVolume);

		GET_SINGLE(ResourceManager)->LoadTexture(L"MainTitle", L"Sprite\\UI\\MainTitle_final.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"MainTitle", GET_SINGLE(ResourceManager)->GetTexture(L"MainTitle"));

		Sprite* titleSprite = GET_SINGLE(ResourceManager)->GetSprite(L"MainTitle");

		SpriteActor* mainTitle = new SpriteActor();
		mainTitle->SetSprite(titleSprite);
		mainTitle->SetLayer(LAYER_OBJECT);
		//const Vec2Int size = titleSprite->GetSize();

		mainTitle->SetPos(Vec2(0, 0));
		AddActor(mainTitle);
	}
	
	// 게임 시작 버튼
	{
//  	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
// // 
// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 300);
// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);

		Button* startButton = new Button();
// 		startButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"),BS_Default);
// 		startButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"),BS_Clicked);

		startButton->SetPos({ (GWinSizeX / 2) - 20, 700 });
		_uis.push_back(startButton);
		startButton->SetSize(Vec2Int(150,50));
		startButton->AddOnClickDelegate(this, &TitleScene::ChangeCutScene);
	}

	// 제작진
	{
// 		GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
// 
// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 300);
// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);

		Button* CreditButton = new Button();
// 		CrewButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
// 		CrewButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Clicked);

		CreditButton->SetPos({ (GWinSizeX / 2) - 20, 790 });
		CreditButton->SetSize(Vec2Int(220, 50));
		_uis.push_back(CreditButton);


	}

	// 게임 종료 버튼
	{
// 		GET_SINGLE(ResourceManager)->LoadTexture(L"QUIT", L"Sprite\\UI\\QUIT.bmp");
// 
// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"QUIT"), 0, 0, 150, 150);
// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"QUIT"), 150, 0, 150, 150);

		Button* QuitButton = new Button();
// 		QuitButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
// 		QuitButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Clicked);

		QuitButton->SetPos({ (GWinSizeX / 2) - 20, 895 });
		QuitButton->SetSize(Vec2Int(150, 50));

		_uis.push_back(QuitButton);

		QuitButton->AddOnClickDelegate(this, &TitleScene::ExitGame);

	}


	//titleImage.SetPos(Vec2{ 500, 500 });
}

void TitleScene::Update()
{
	Super::Update();



	
	if ((GET_SINGLE(InputManager)->GetButtonDown(KeyType::P)))
	{
		GET_SINGLE(SoundManager)->Release();
		//channel->SetPaused(true);

	}
	else if ((GET_SINGLE(InputManager)->GetButtonDown(KeyType::O)))
	{

	}
}

void TitleScene::Render(HDC hdc)
{
	
	Super::Render(hdc);
}

void TitleScene::LateUpdate()
{
	Super::LateUpdate();
}

void TitleScene::ChangeCutScene()
{
	_sceneType = SceneType::CutScene;
}

void TitleScene::ExitGame()
{
	PostQuitMessage(0);
}