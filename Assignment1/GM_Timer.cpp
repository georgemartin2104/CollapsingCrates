#include "GM_Timer.h"


GM_Timer::GM_Timer()
{
	startTicks = 0;
}

void GM_Timer::resetTicksTimer()
{
	startTicks = SDL_GetTicks(); // number of milliseconds since start of SDL program
}

int GM_Timer::getTicks()
{
	return (SDL_GetTicks() - startTicks); // Return the current time minus the start time
}