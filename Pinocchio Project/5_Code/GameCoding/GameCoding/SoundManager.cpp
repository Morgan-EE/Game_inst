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

	// ���� �ʱ�ȭ
	
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
	// ����� ����
	for (auto& sound : _backgroundSound)
	{
		sound.second->release();
	}
	_backgroundSound.clear();

	// ȿ���� ����
	for (auto& sound : _SFXSound)
	{
		sound.second->release();
	}
	_SFXSound.clear();

	// ä�ε� ���� �� ����
	/*_backgroundChannel->stop();
	for (auto& channel : _SFXChannels)
	{
		channel->stop();
	}*/

	// FMOD �ý��� ����
	//_system->release();
}

//���带 �ε��ϴ� ����(key, path, type)
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
	//�� �˻�
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
	// ����� ����
	_backgroundChannel->setVolume(sVolume);
	
	// ȿ���� ä�ε� ����
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

	// ����� ����
	_backgroundChannel->getVolume(sVolume);

	// ȿ���� ä�ε� ����
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



