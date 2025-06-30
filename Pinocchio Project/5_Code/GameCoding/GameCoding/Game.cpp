#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "UIManager.h"


Game::Game()
{

}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	//_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	hdc = ::GetDC(hwnd);

	{
		// Double Buffering
		::GetClientRect(hwnd, &_rect);
		hdcBack = ::CreateCompatibleDC(hdc);
		_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom);
		HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);
		::DeleteObject(prev);
	}

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, fs::path(L"D:\\SVN1Q\\Pinocchio\\5_Project\\GameCoding\\Resources"));
	GET_SINGLE(SoundManager)->Init();
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DeadScene);

	GET_SINGLE(UIManager)->Init(hwnd);

	SetBkColor(hdcBack, RGB(0, 0, 0)); // ������(RGB ��: 0, 0, 0)
	SetTextColor(hdcBack, RGB(255, 255, 255)); // ���(RGB ��: 255, 255, 255)
	SetTextAlign(hdcBack, TA_CENTER);

	// TTF ���� ���
	const string& path = "Font\\don.ttf";
	string fullPath = GET_SINGLE(ResourceManager)->GetResourcePath().string() + "\\" + path;

	std::wstring stemp = std::wstring(fullPath.begin(), fullPath.end());

	// ��Ʈ�� �ý��ۿ� �߰�
	AddFontResource(stemp.c_str());

	// ���ϴ� ��Ʈ ���� ����
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 24; // ��Ʈ ����
	lf.lfWeight = FW_NORMAL; // ��Ʈ �β�
	lf.lfCharSet = DEFAULT_CHARSET; // ���� ����
	wcscpy_s(lf.lfFaceName, LF_FACESIZE, L"�ձٸ��"); // ��Ʈ �̸�

	// ��Ʈ ����
	HFONT hFont = CreateFontIndirect(&lf);

	// ��Ʈ ����
	HFONT hOldFont = (HFONT)SelectObject(hdcBack, hFont);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();

	GET_SINGLE(UIManager)->Update();
}

void Game::Render()
{
	GET_SINGLE(SceneManager)->Render(hdcBack);
	GET_SINGLE(UIManager)->Render(hdcBack);
	
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"MousePos({0},{1})", mousePos.x, mousePos.y);
		::TextOut(hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Double Buffering
	::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY);
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, BLACKNESS);
}

void Game::LateUpdate()
{
	GET_SINGLE(SceneManager)->LateUpdate();
}
