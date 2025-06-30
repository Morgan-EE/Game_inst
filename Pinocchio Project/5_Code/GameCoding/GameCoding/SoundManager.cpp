#include "pch.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include <locale>
#include <codecvt>

SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	FMOD::System_Create(&_system);
	_system->init(11, FMOD_INIT_NORMAL, NULL);

	// 변수 초기화
	
	_backgroundChannel = nullptr;
	_SFXChannels[0] = nullptr;
	_SFXChannels[1] = nullptr;
	_SFXChannels[2] = nullptr;
	_SFXChannels[3] = nullptr;
	_SFXChannels[4] = nullptr;
	_SFXChannels[5] = nullptr;
	_SFXChannels[6] = nullptr;
	_SFXChannels[7] = nullptr;
	_SFXChannels[8] = nullptr;
	_SFXChannels[9] = nullptr;
}

void SoundManager::Release()
{
	// 배경음 해제
	for (auto& sound : _backgroundSound)
	{
		sound.second->release();
	}
	_backgroundSound.clear();

	// 효과음 해제
	for (auto& sound : _SFXSound)
	{
		sound.second->release();
	}
	_SFXSound.clear();

	// 채널들 정지 및 해제
	/*_backgroundChannel->stop();
	for (auto& channel : _SFXChannels)
	{
		channel->stop();
	}*/

	// FMOD 시스템 해제
	//_system->release();
}

//사운드를 로드하는 역할(key, path, type)
void SoundManager::LoadSound(const std::wstring& key, const string& path, SoundType soundType)
{
	FMOD::Sound* sound; //*

 	//std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
 	//std::string pathString = converter.to_bytes(path);
	string fullPath = GET_SINGLE(ResourceManager)->GetResourcePath().string() + "\\" + path;

	_system->createSound(fullPath.c_str(), FMOD_LOOP_OFF, 0, &sound);

	if (soundType == SoundType::BGM)
	{

		_backgroundSound.insert({ key, sound });
	}
	else if (soundType == SoundType::SFX)
	{
		_SFXSound.insert({ key, sound });
	}
}

void SoundManager::PlayBackgroundSound(const wstring& key)
{
	//값 검색
	auto it = _backgroundSound.find(key);
	_system->playSound(it->second, 0, false, &_backgroundChannel);
}

/// <summary>
/// 
/// </summary>
/// <param name="key"></param>
/// <param name="channelIndex">range is 0 ~ 9</param>
void SoundManager::PlaySFXSound(const wstring& key, int32 channelIndex)
{
	auto it = _SFXSound.find(key);
	_system->playSound(it->second, 0, false, &_SFXChannels[channelIndex]);
}

void SoundManager::PauseSFXSound(int32 channelIndex)
{
	if (channelIndex >= 0 && channelIndex < 10)
	{
		_SFXChannels[channelIndex]->setPaused(true);
	}
}


void SoundManager::SetVolume(float sVolume)
{
	float volume = GET_SINGLE(SoundManager)->fVolume;
	fVolume = sVolume;
	// 배경음 설정
	_backgroundChannel->setVolume(sVolume);
	
	// 효과음 채널들 설정
	for (auto& channel : _SFXChannels)
	{
		channel->setVolume(sVolume);
	}

}

void SoundManager::GetVolume(float *sVolume)
{
	float volume = GET_SINGLE(SoundManager)->fVolume;
	fVolume = 0.1f;
	*sVolume = fVolume;

	// 배경음 설정
	_backgroundChannel->getVolume(sVolume);

	// 효과음 채널들 설정
	for (auto& channel : _SFXChannels)
	{
		channel->getVolume(sVolume);
	}
}

//void SoundManager::PauseMusic()
//{
//	_backgroundChannel->pause();
//}

//void SoundManager::PauseMusic()
//{
//	//_backgroundChannel->
//}



