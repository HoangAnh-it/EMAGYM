#pragma once
#include<SDL.h>

class LTime
{
private:
	Uint32 startTick;
	Uint32 pauseTick;
	bool started;
	bool paused;
public:
	LTime();
	~LTime();
	void start();
	void stop();
	void pause();
	void unPause();
	bool isStarted();
	bool isPaused();
	Uint32 getTime();
};
