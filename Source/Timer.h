#pragma once
#include <time.h>

class Timer
{
public:
	
	Timer() = default;
	~Timer() = default;

	void beginTimer();
	void finishTimer();

	//Setters
	void setStartInterval();
	void setEndInterval();
	void setInterval();
	void setIntervalReset(bool ir);
	void decrementTime();
	//Getters
	clock_t getStartTimer() const;
	clock_t getEndTimer() const;
	int getInterval() const;
	bool getIntervalReset() const;
	int getTime() const;
private:
	clock_t startTimer;
	clock_t endTimer;
	clock_t startInterval;
	clock_t endInterval;
	int interval;
	int time = 3;
	bool intervalReset = true;
};
