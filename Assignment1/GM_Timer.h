#pragma once
#ifndef aTimerFILE
#define aTimerFILE

#include <iostream>
#include <SDL.h>


class GM_Timer
{

private:
	int startTicks; // SDL time when the timer started

public:
	GM_Timer();

	//Variables and functions to be used by SDL Timer
	void resetTicksTimer();
	int getTicks();

};

#endif



