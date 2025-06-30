#include "pch.h"
#include "CutScene.h"

// Texture
#include "SpriteActor.h"
#include "Sprite.h"

// Manager
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"

#include <locale>
#include <codecvt>

// UI
#include "Button.h"

#pragma warning(disable : 4996)

CutScene::CutScene()
{
	_pageIndex = 0;
	_lastPageIndex = 9;
}

CutScene::~CutScene()
{

}

void CutScene::Init()
{
	ReadIntroText();
	{
		// 컷씬 불러오기
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene1", L"Sprite\\UI\\CutScene\\1.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene2", L"Sprite\\UI\\CutScene\\2.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene3", L"Sprite\\UI\\CutScene\\3.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene4", L"Sprite\\UI\\CutScene\\4.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene5", L"Sprite\\UI\\CutScene\\5.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene6", L"Sprite\\UI\\CutScene\\6.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene7", L"Sprite\\UI\\CutScene\\7.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene8", L"Sprite\\UI\\CutScene\\8.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"CutScene9", L"Sprite\\UI\\CutScene\\9.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene1", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene1"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene2", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene2"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene3", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene3"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene4", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene4"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene5", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene5"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene6", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene6"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene7", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene7"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene8", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene8"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"CutScene9", GET_SINGLE(ResourceManager)->GetTexture(L"CutScene9"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene1"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene2"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene3"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene4"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene5"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene6"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene7"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene8"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"CutScene9"));

		for (int32 i = 0; i < 9; i++)
		{
			SpriteActor* cutScene = new SpriteActor();
			cutScene->SetSprite(cutSceneSpriteArray[i]);
			cutScene->SetLayer(LAYER_BACKGROUND);
			const Vec2Int size = cutSceneSpriteArray[i]->GetSize();
			cutScene->SetPos({ 0, 0 });
			//AddActor(cutScene);
			cutSceneActors.push_back(cutScene);
		}
// 		GET_SINGLE(ResourceManager)->LoadTexture(L"Box", L"Sprite\\Object\\Box.bmp");
// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Box", GET_SINGLE(ResourceManager)->GetTexture(L"Box"));
// 		Sprite* titleSprite = GET_SINGLE(ResourceManager)->GetSprite(L"Box");
// 		SpriteActor* temp = new SpriteActor();
// 		temp->SetSprite(titleSprite);
// 		AddActor(temp);
		
		NextPage(); //첫번째 삽화 출력
	}
	// nextPage
	{


		Button* nextPageButton = new Button();

		nextPageButton->SetSize(Vec2Int(150, 60));
		nextPageButton->SetPos({ 1920-(177/2), 1080 - (76 / 2)});
		_uis.push_back(nextPageButton);

		nextPageButton->AddOnClickDelegate(this, &CutScene::NextPage);
	}
}

void CutScene::Update()
{
	Super::Update();
}

void CutScene::Render(HDC hdc)
{
	::TextOut(hdc, 960, 930, _introText[_pageIndex].c_str(), static_cast<int32>(_introText[_pageIndex].size()));
	Super::Render(hdc);
}

void CutScene::LateUpdate()
{
	Super::LateUpdate();
}

void CutScene::ReadIntroText()
{
	std::wifstream inputFile("Intro.txt");

	if (!inputFile.is_open()) {
		return;
	}

	// UTF-8 인코딩을 사용하는 로케일 설정
	std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>);
	inputFile.imbue(utf8_locale);

	std::wstring line;
	while (inputFile)
	{
		getline(inputFile, line);
		_introText.push_back(line);
	}
}

void CutScene::NextPage()
{
	if (_pageIndex == _lastPageIndex)
	{
		_sceneType = SceneType::GameScene;
	}
	else if (cutSceneActors[_pageIndex] != nullptr)
	{
		_actors[LAYER_BACKGROUND].clear();
		AddActor(cutSceneActors[_pageIndex]);
	}
	_pageIndex++;
}
