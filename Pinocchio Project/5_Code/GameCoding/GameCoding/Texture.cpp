#include "pch.h"
#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

Texture* Texture::LoadBmp(HWND hwnd, const wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	_hdc = ::CreateCompatibleDC(hdc);
	_bitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (_bitmap == 0)
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);

	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap);
	::DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bit);
	_size.x = bit.bmWidth;
	_size.y = bit.bmHeight;

	return this;
}

HDC Texture::GetDC()
{
	return _hdc;
}

BYTE* Texture::GetBitMapByte()
{
	BITMAP bmpInfo;
	GetObject(_bitmap, sizeof(BITMAP), &bmpInfo);

	BYTE* bitmapData = new BYTE[bmpInfo.bmWidth * bmpInfo.bmHeight * 4]; // 4는 RGBA 채널 개수입니다.
	GetBitmapBits(_bitmap, bmpInfo.bmWidth * bmpInfo.bmHeight * 4, bitmapData);

	return bitmapData;
}
