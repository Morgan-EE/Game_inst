#include "pch.h"
#include "TutorialPanel.h"
#include "ResourceManager.h"
#include "Button.h"
#include "UISprite.h"
#include "GameScene.h"

TutorialPanel::TutorialPanel()
{
	{
		UISprite* ui = new UISprite();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"UI_Interaction"), US_Panel);
		//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"), US_Panel);
		ui->SetState(US_Panel);
		ui->SetSize({ 878,829 });
		ui->SetPos({ 960, 540 });
		_uiSprites.push_back(ui);
		//AddChild(ui);
	}
	{
		UISprite* ui = new UISprite();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"UI_Move"), US_Panel);
		//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"), US_Panel);
		ui->SetState(US_Panel);
		ui->SetSize({ 878,829 });
		ui->SetPos({ 960, 540 });
		_uiSprites.push_back(ui);
		//AddChild(ui);
	}
	{
		UISprite* ui = new UISprite();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"UI_StageChange1"), US_Panel);
		//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"), US_Panel);
		ui->SetState(US_Panel);
		ui->SetSize({ 878,829 });
		ui->SetPos({ 960, 540 });
		_uiSprites.push_back(ui);
		//AddChild(ui);
	}
	{
		UISprite* ui = new UISprite();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"UI_StageChange2"), US_Panel);
		//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"), US_Panel);
		ui->SetState(US_Panel);
		ui->SetSize({ 878,829 });
		ui->SetPos({ 960, 540 });
		_uiSprites.push_back(ui);
		//AddChild(ui);
	}
	
	{
		Button* ui = new Button();
		//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
		//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Clicked);
		ui->SetSize({ 878,829 });
		ui->SetPos({ 960, 540 });

		ui->AddOnClickDelegate(this, &TutorialPanel::OnClickNextButton);
		AddChild(ui);

		_button = ui;
	}
	
}

TutorialPanel::~TutorialPanel()
{

}

void TutorialPanel::BeginPlay()
{
	Super::BeginPlay();
	AddChild(_uiSprites[_cursor]);
}

void TutorialPanel::Tick()
{
	Super::Tick();
}

void TutorialPanel::Render(HDC hdc)
{
	Super::Render(hdc);
}

void TutorialPanel::OnClickNextButton()
{
	RemoveChild(_uiSprites[_cursor]);
	_cursor++;

	if (_cursor >= 3)
	{
		if(_button)
			RemoveChild(_button);

		_gameScene->SetText("Player_Start");
		return;
	}

	AddChild(_uiSprites[_cursor]);



	//// TODO : 여기해라!
	//_cursor++;
	//if (_cursor == 4)
	//{
	//	// TODO : 어떻게 없애지?
	//	return;
	//}
	//AddChild(_uiSprites[_cursor]);
	//RemoveChild(_uiSprites[_cursor - 1]);
}
