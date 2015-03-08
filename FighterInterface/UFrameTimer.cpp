#include "UFrameTimer.h"


UFrameTimer::UFrameTimer(int duration):
	targetTime(duration)
{
}


UFrameTimer::~UFrameTimer(void)
{
}
//last place was implementing this timer
bool UFrameTimer::Complete()
{
	 return  (currentTime >= targetTime);
}

void UFrameTimer::Start()
{
	running = true;
}

void UFrameTimer::Stop()
{
	running = false;
}

void UFrameTimer::Reset()
{
	currentTime = 0;
}

void UFrameTimer::Update()
{
	if (running)
		currentTime++;
}
