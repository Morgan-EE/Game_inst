#include "pch.h"
#include "TestPanel.h"
#include "Utils.h"
#include "TestButton.h"
#include "ResourceManager.h"
#include "UISprite.h"

TestPanel::TestPanel()
{
	{
		Button* ui = new Button();
		ui->SetPos({ 400, 200 });
		ui->SetSize({ 650, 300 });
		AddChild(ui);
	}
	{
		Button* ui = new Button();
		ui->SetCurrentSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Box"));
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Clicked);
		ui->SetPos({ 200,200 });

		ui->AddOnClickDelegate(this, &TestPanel::OnClickStartButton);
		AddChild(ui);
	}
	{
		Button* ui = new Button();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Edit_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Edit_On"), BS_Clicked);
		ui->SetPos({ 400,200 });

		ui->AddOnClickDelegate(this, &TestPanel::OnClickStartButton);
		AddChild(ui);
	}
	{
		UISprite* ui = new UISprite();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Inventory"), US_None);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Piece5"), US_PIECE5);
		ui->SetState(US_None);
		//GET_SINGLE(UIManager)->SetPiece(ui, US_None);
		ui->SetSize({ 90,97 });
		ui->SetPos({ 1700, 980 });

		//_uis.push_back(ui);
		AddChild(ui);
	}
}

TestPanel::~TestPanel()
{

}

void TestPanel::BeginPlay()
{
	Super::BeginPlay();
}

void TestPanel::Tick()
{
	Super::Tick();
}

void TestPanel::Render(HDC hdc)
{
	Super::Render(hdc);

	/*wstring str = std::format(L"Count : {0}", _count);
	Utils::DrawTextW(hdc, { 100, 0 }, str);*/
}

void TestPanel::OnClickStartButton()
{
	_count++;
}

void TestPanel::OnClickedEditButton()
{
	_count--;
}

void TestPanel::OnClickedExitButton()
{

}
