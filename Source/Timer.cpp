#include "Timer.h"

void Timer::beginTimer()
{
	startTimer = clock();
}

void Timer::finishTimer()
{
	endTimer = clock();
}

void Timer::setStartInterval()
{
	startInterval = clock();
}

void Timer::setEndInterval()
{
	endInterval = clock();
}

void Timer::setInterval()
{
	interval = (endInterval - startInterval) / CLOCKS_PER_SEC;
}

void Timer::setIntervalReset(bool ir)
{
	intervalReset = ir;
}

void Timer::decrementTime()
{
	if (time != 1)
	{
		--time;
	}
}
clock_t Timer::getStartTimer() const
{
	return startTimer;
}

clock_t Timer::getEndTimer() const
{
	return endTimer;
}

int Timer::getInterval() const
{
	return interval;
}

bool Timer::getIntervalReset() const
{
	return intervalReset;
}

int Timer::getTime() const
{
	return time;
}