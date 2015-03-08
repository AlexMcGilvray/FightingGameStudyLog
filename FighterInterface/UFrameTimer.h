#pragma once
//
// A timer that works in frames and not standard time units. 
//
//
class UFrameTimer
{
public:
	UFrameTimer(int duration);
	~UFrameTimer(void);
	void Start();
	void Stop();
	void Reset();
	void Update();
	bool Complete();

private:
	int targetTime;
	int currentTime;
	bool running;

};

