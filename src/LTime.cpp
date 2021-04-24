#include"Function.hpp"

LTime::LTime()
{
	startTick = 0;
	pauseTick = 0;
	started = false;
	paused = false;
}

LTime::~LTime()
{
	stop();
	std::cout << "Destroyed Time" << std::endl;
}

void LTime::stop()
{
	if (started)
	{
		startTick = 0;
		pauseTick = 0;
		started = false;
		paused = false;
	}
}

void LTime::start()
{
	started = true;
	paused = false;
	startTick = SDL_GetTicks();
	pauseTick = 0;
}

void LTime::pause()
{
	if (started && !paused)
	{
		paused = true;
		pauseTick = SDL_GetTicks() - startTick;
		startTick = 0;
	}
}

void LTime::unPause()
{
	if (started && paused)
	{
		paused = false;
		startTick = SDL_GetTicks() - pauseTick;
		pauseTick = 0;
	}
}

Uint32 LTime::getTime()
{
	Uint32 time = 0;
	if (started)
	{
		if (paused)
		{
			time = pauseTick;
		}
		else
		{
			time = SDL_GetTicks() - startTick;
		}
	}
	return time;
}

bool LTime::isPaused()
{
	return paused;
}

bool LTime::isStarted()
{
	return started;
}
