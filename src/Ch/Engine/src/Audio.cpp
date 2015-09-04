
#include "Audio.h"
#include <string.h>

#ifdef UNICODE
#include <windows.h>
#endif

namespace Advanced2D
{
#if FMOD == 3
Audio::AudioSample::AudioSample() : mSample(NULL), mChannel(-1)
#else
Audio::AudioSample::AudioSample() : mSample(NULL), mChannel(NULL)
#endif
{
	memset(mName, '\0', FILENAME_MAX * sizeof(_TCHAR));
}
#if FMOD == 3
Audio::AudioSample::AudioSample(const _TCHAR* aName) : mSample(NULL),
	mChannel(-1)
#else
Audio::AudioSample::AudioSample(const _TCHAR* aName) : mSample(NULL),
	mChannel(NULL)
#endif
{
	this->setName(aName);
}

void Audio::AudioSample::setName(const _TCHAR* aName)
{
#if _MSC_VER > 1310
	_tcsncpy_s(mName, FILENAME_MAX, aName,
	           sizeof(mName) / sizeof(*mName));
#else
	_tcsncpy(mName, aName, sizeof(mName) / sizeof(*mName));
#endif
}

Audio::AudioSample::~AudioSample()
{
	if (mSample)
	{
#if FMOD == 3
		FSOUND_Sample_Free(mSample);
#else
		FMOD_Sound_Release(mSample);
#endif
	}

	mSample = NULL;
}

#if FMOD == 3
Audio::Audio()
#else
Audio::Audio() : mSystem(NULL)
#endif
{
}

Audio::~Audio()
{
	for (IterFAS i = mSamples.begin(); i != mSamples.end(); ++i)
	{
		delete (*i);
		(*i) = NULL;
	}

#if FMOD == 3
	FSOUND_Close();
#else

	if (mSystem)
	{
		FMOD_System_Close(mSystem);
		FMOD_System_Release(mSystem);
	}

	mSystem = NULL;
#endif
}

bool Audio::init()
{
#if FMOD == 3

	if (!FSOUND_Init(44100, 32, FSOUND_INIT_USEDEFAULTMIDISYNTH))
	{
		return false;
	}

#else

	if (FMOD_OK != FMOD_System_Create(&mSystem))
	{
		return false;
	}

	if (FMOD_OK != FMOD_System_Init(mSystem, 100, FMOD_INIT_NORMAL, NULL))
	{
		return false;
	}

#endif
	return true;
}

void Audio::update()
{
#if FMOD == 3
	FSOUND_Update();
#else
	FMOD_System_Update(mSystem);
#endif
}

bool Audio::load(const _TCHAR* aFileName, const _TCHAR* aCallingName)
{
	if (!aFileName || !aCallingName)
	{
		return false;
	}

	if (0 == aFileName[0] || 0 == aCallingName[0])
	{
		return false;
	}

	AudioSample* sample = load(aFileName);

	if (!sample)
	{
		return false;
	}

	sample->setName(aCallingName);
	mSamples.push_back(sample);
	return true;
}

Audio::AudioSample* Audio::load(const _TCHAR* aFileName)
{
	if (!aFileName || (0 == aFileName[0]))
	{
		return NULL;
	}

	AudioSample* sample = new AudioSample();
#ifndef UNICODE
#if FMOD == 3

	if (NULL == (sample->mSample = FSOUND_Sample_Load(FSOUND_UNMANAGED, aFileName,
	                               FSOUND_NORMAL, 0, 0)))
#else
	if (FMOD_OK != FMOD_System_CreateSound(mSystem, aFileName, FMOD_DEFAULT, NULL,
	                                       &sample->mSample))
#endif
	{
		return NULL;
	}

#else
	size_t iPathLength = wcslen(aFileName);
	char* szFileNameA = new char[iPathLength + 1];
	WideCharToMultiByte(CP_ACP, 0, aFileName, static_cast<int>(iPathLength),
	                    szFileNameA,
	                    static_cast<int>(iPathLength), NULL, NULL);
	szFileNameA[iPathLength] = '\0';
#if FMOD == 3

	if (NULL == (sample->mSample = FSOUND_Sample_Load(FSOUND_UNMANAGED, szFileNameA,
	                               FSOUND_NORMAL, 0, 0)))
#else
	if (FMOD_OK != FMOD_System_CreateSound(mSystem, szFileNameA, FMOD_DEFAULT, NULL,
	                                       &sample->mSample))
#endif
	{
		delete [] szFileNameA;
		szFileNameA = NULL;
		return NULL;
	}

	delete [] szFileNameA;
	szFileNameA = NULL;
#endif
	return sample;
}

bool Audio::play(const _TCHAR* aCallingName)
{
	AudioSample* sample = find(aCallingName);

	if (!sample)
	{
		return false;
	}

	return play(sample);
}

bool Audio::play(AudioSample* aSample)
{
	if (!aSample)
	{
		return false;
	}

#if FMOD == 3

	if (-1 == (aSample->mChannel = FSOUND_PlaySoundEx(FSOUND_FREE, aSample->mSample,
	                               NULL, true)))
#else
	if (FMOD_OK != FMOD_System_PlaySound(mSystem, FMOD_CHANNEL_FREE,
	                                     aSample->mSample,
	                                     true, &aSample->mChannel))
#endif
	{
		return false;
	}

#if FMOD == 3
	//?FSOUND_SetLoopMode
	FSOUND_SetPaused(aSample->mChannel, false);
#else
	FMOD_Channel_SetLoopCount(aSample->mChannel, -1);
	FMOD_Channel_SetPaused(aSample->mChannel, false);
#endif
	return true;
}

void Audio::stop(const _TCHAR* aCallingName)
{
	if (!isPlaying(aCallingName))
	{
		return;
	}

	AudioSample* sample = find(aCallingName);

	if (!sample)
	{
		return;
	}

#if FMOD == 3
	FSOUND_StopSound(sample->mChannel);
#else
	FMOD_Channel_Stop(sample->mChannel);
#endif
}

void Audio::stopAll()
{
	for (IterFAS i = mSamples.begin(); i != mSamples.end(); ++i)
	{
#if FMOD == 3
		FSOUND_StopSound((*i)->mChannel);
#else
		FMOD_Channel_Stop((*i)->mChannel);
#endif
	}
}

void Audio::stopAllExcept(const _TCHAR* aCallingName)
{
	for (IterFAS i = mSamples.begin(); i != mSamples.end(); ++i)
	{
		if (0 != _tcscmp((*i)->mName, aCallingName))
		{
#if FMOD == 3
			FSOUND_StopSound((*i)->mChannel);
#else
			FMOD_Channel_Stop((*i)->mChannel);
#endif
		}
	}
}

bool Audio::isPlaying(const _TCHAR* aCallingName)
{
	AudioSample* sample = find(aCallingName);

	if (!sample)
	{
		return false;
	}

#if FMOD == 3
	return (FSOUND_IsPlaying(sample->mChannel) > 0);
#else
	int index = 0;
	FMOD_Channel_GetIndex(sample->mChannel, &index);
	return (index > 0);
#endif
}

bool Audio::isExists(const _TCHAR* aCallingName)
{
	return NULL != find(aCallingName);
}

Audio::AudioSample* Audio::find(const _TCHAR* aCallingName)
{
	for (IterFAS i = mSamples.begin(); i != mSamples.end(); ++i)
	{
		if (0 == _tcscmp((*i)->mName, aCallingName))
		{
			return (*i);
		}
	}

	return NULL;
}

}
