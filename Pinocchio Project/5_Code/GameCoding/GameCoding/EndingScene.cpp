#include "pch.h"
#include "EndingScene.h"

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

EndingScene::EndingScene()
{
	_pageIndex = 0;
	_lastPageIndex = 5;
}

EndingScene::~EndingScene()
{

}

void EndingScene::Init()
{
	ReadIntroText();
	{
		// ÄÆ¾À ºÒ·¯¿À±â
		GET_SINGLE(ResourceManager)->LoadTexture(L"EndingScene1", L"Sprite\\UI\\EndingScene\\1.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"EndingScene2", L"Sprite\\UI\\EndingScene\\2.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"EndingScene3", L"Sprite\\UI\\EndingScene\\3.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"EndingScene4", L"Sprite\\UI\\EndingScene\\4.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"EndingScene5", L"Sprite\\UI\\EndingScene\\5.bmp");
	
		GET_SINGLE(ResourceManager)->CreateSprite(L"EndingScene1", GET_SINGLE(ResourceManager)->GetTexture(L"EndingScene1"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"EndingScene2", GET_SINGLE(ResourceManager)->GetTexture(L"EndingScene2"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"EndingScene3", GET_SINGLE(ResourceManager)->GetTexture(L"EndingScene3"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"EndingScene4", GET_SINGLE(ResourceManager)->GetTexture(L"EndingScene4"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"EndingScene5", GET_SINGLE(ResourceManager)->GetTexture(L"EndingScene5"));

		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"EndingScene1"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"EndingScene2"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"EndingScene3"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"EndingScene4"));
		cutSceneSpriteArray.push_back(GET_SINGLE(ResourceManager)->GetSprite(L"EndingScene5"));

		for (int32 i = 0; i < 5; i++)
		{
			SpriteActor* cutScene = new SpriteActor();
			cutScene->SetSprite(cutSceneSpriteArray[i]);
			cutScene->SetLayer(LAYER_BACKGROUND);
			const Vec2Int size = cutSceneSpriteArray[i]->GetSize();
			//cutScene->SetPos({ 960, 0 });
			//AddActor(cutScene);
			cutSceneActors.push_back(cutScene);
		}
		// 		GET_SINGLE(ResourceManager)->LoadTexture(L"Box", L"Sprite\\Object\\Box.bmp");
		// 		GET_SINGLE(ResourceManager)->CreateSprite(L"Box", GET_SINGLE(ResourceManager)->GetTexture(L"Box"));
		// 		Sprite* titleSprite = GET_SINGLE(ResourceManager)->GetSprite(L"Box");
		// 		SpriteActor* temp = new SpriteActor();
		// 		temp->SetSprite(titleSprite);
		// 		AddActor(temp);

		NextPage(); //Ã¹¹øÂ° »ðÈ­ Ãâ·Â
	}
	// nextPage
	{


		Button* nextPageButton = new Button();

		nextPageButton->SetSize(Vec2Int(150, 60));
		nextPageButton->SetPos({ 1920 - (177 / 2), 1080 - (76 / 2) });
		_uis.push_back(nextPageButton);

		nextPageButton->AddOnClickDelegate(this, &EndingScene::NextPage);
	}
}

void EndingScene::Update()
{
	Super::Update();
}

void EndingScene::Render(HDC hdc)
{
	//::TextOut(hdc, 960, 930, _introText[_pageIndex].c_str(), static_cast<int32>(_introText[_pageIndex].size()));
	Super::Render(hdc);
}

void EndingScene::LateUpdate()
{
	Super::LateUpdate();
}

void EndingScene::ReadIntroText()
{

}

void EndingScene::NextPage()
{
	if (_pageIndex == _lastPageIndex)
	{
		_sceneType = SceneType::TitleScene;
	}
	else if (cutSceneActors[_pageIndex] != nullptr)
	{
		_actors[LAYER_BACKGROUND].clear();
		AddActor(cutSceneActors[_pageIndex]);
	}
	_pageIndex++;
}
