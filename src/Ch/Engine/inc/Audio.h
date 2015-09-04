#ifndef __FMOD_AUDIO_H_
#define __FMOD_AUDIO_H_

#include "fmod.h"
#include <tchar.h>
#include <stdio.h>
#include <vector>

#if defined(_FMOD_H_)
#define FMOD 3
#elif defined(_FMOD_H)
#define FMOD 4
#endif

namespace Advanced2D
{
class Audio
{
public:
	struct AudioSample
	{
		_TCHAR mName[FILENAME_MAX];
#if FMOD == 3
		FSOUND_SAMPLE* mSample;
		int mChannel;
#else
		FMOD_SOUND* mSample;
		FMOD_CHANNEL* mChannel;
#endif
		AudioSample();
		AudioSample(const _TCHAR* aName);
		void setName(const _TCHAR* aName);
		~AudioSample();
	};
private:
#if FMOD == 4
	FMOD_SYSTEM* mSystem;
#endif
	typedef std::vector<AudioSample*> AudioSamples;
	typedef std::vector<AudioSample*>::iterator IterFAS;
	AudioSamples mSamples;
public:
	Audio();
	bool init();
	void update();
	bool load(const _TCHAR* aFileName, const _TCHAR* aCallingName);
	AudioSample* load(const _TCHAR* aFileName);
	bool play(const _TCHAR* aCallingName);
	bool play(AudioSample* aSample);
	void stop(const _TCHAR* aCallingName);
	void stopAll();
	void stopAllExcept(const _TCHAR* aCallingName);
	bool isPlaying(const _TCHAR* aCallingName);
	bool isExists(const _TCHAR* aCallingName);
	AudioSample* find(const _TCHAR* aCallingName);
	virtual ~Audio();
};
}

#endif
