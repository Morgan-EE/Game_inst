#pragma once
#ifndef _CSOUND_H_
#define _CSOUND_H_
#include <fmod.hpp>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_01 0.1f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

#pragma comment(lib, "fmod_vc.lib")
using namespace FMOD;

class SoundManager
{
	DECLARE_SINGLE(SoundManager);
	//SoundManager();
	~SoundManager();

public:
	//volume
	float fVolume;

	void Init();
	void Release();
	void LoadSound(const wstring& key, const string& path, SoundType soundType);

	// ����
	void PlayBackgroundSound(const wstring& key);
	void PlaySFXSound(const wstring& key, int32 channelIndex);
	void PauseSFXSound(int32 channelIndex);

	void SetVolume(float fVolume);
	void GetVolume(float* sVolume);
	//void PauseMusic();
	//void ResumeMusic();

private:
	// ����
 	FMOD::System*			_system;
	FMOD_SOUND* m_sound;
	//std::shared_ptr<SoundChannel> _backgroundChannel;
	//std::vector<std::shared_ptr<SoundChannel>> _SFXChannels;
 	FMOD::Channel*			_backgroundChannel;
	FMOD::Channel*			_SFXChannels[10];
	// 
 	//vector<FMOD::Channel*>	_SFXChannels;
	FMOD_RESULT s_result; //�߰�
	
	float m_volume;
	FMOD_BOOL m_bool;

	// map���� ���� key �� ����� �� �ְ�
	unordered_map<wstring, FMOD::Sound*>	_backgroundSound;
	unordered_map<wstring, FMOD::Sound*>	_SFXSound;


};


// �ʱ�ȭ
// ���
// �ߴ�
// ���� ����
// 
// ä�� ����
// ��� ����
// ȿ�� ���� [10]

#endif

// 7 : Door