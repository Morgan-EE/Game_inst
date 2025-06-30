#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;


	GetResourceDirectory();
	

}

void ResourceManager::GetResourceDirectory()
{
	wchar_t testResourcePath[255];
	GetCurrentDirectory(255, testResourcePath);

	int32 index = 0;
	while (testResourcePath[index] != '\0')
	{
		index++;
	}
	/*while (testResourcePath[index] != '\\')
	{
		index--;
	}*/
	//index++;

	wchar_t path[] = L"\\Resources";
	for (int32 i = 0; i < 12; i++)
	{
		testResourcePath[index] = path[i];
		index++;
	}
	_resourcePath = testResourcePath;
}

void ResourceManager::Clear()
{
	for (auto& item : _textures)
		SAFE_DELETE(item.second);
	_textures.clear();

	for (auto& item : _sprites)
		SAFE_DELETE(item.second);
	_sprites.clear();

	for (auto& item : _flipbooks)
		SAFE_DELETE(item.second);
	_flipbooks.clear();

	for (auto& item : _tilemaps)
		SAFE_DELETE(item.second);
	_tilemaps.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent /*= RGB(255, 0, 255)*/)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];

	fs::path fullPath = _resourcePath / path;
	Texture* texture = new Texture();
	texture->LoadBmp(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = texture;
	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x /*= 0*/, int32 y /*= 0*/, int32 cx /*= 0*/, int32 cy /*= 0*/)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	// default 값일 경우 텍스트에서 로딩했던 사이즈 사용
	if (cx == 0)
		cx = texture->GetSize().x;
	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;

	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
	{
		return _flipbooks[key];
	}

	Flipbook* fb = new Flipbook();
	_flipbooks[key] = fb;
	return fb;
}

Tilemap* ResourceManager::CreateTilemap(const wstring& key)
{
	if (_tilemaps.find(key) != _tilemaps.end())
		return _tilemaps[key];

	Tilemap* tm = new Tilemap();
	_tilemaps[key] = tm;

	return tm;
}

void ResourceManager::SaveTilemap(const wstring& key, const wstring& path)
{
	Tilemap* tm = GetTilemap(key);

	fs::path fullPath = _resourcePath / path;
	tm->SaveFile(fullPath);
}

Tilemap* ResourceManager::LoadTilemap(const wstring& key, const wstring& path)
{
	Tilemap* tm = nullptr;

	if (_tilemaps.find(key) == _tilemaps.end())
	{
		_tilemaps[key] = new Tilemap();
	}

	tm = _tilemaps[key];

	fs::path fullPath = _resourcePath / path;
	tm->LoadFile(fullPath);

	return tm;
}
