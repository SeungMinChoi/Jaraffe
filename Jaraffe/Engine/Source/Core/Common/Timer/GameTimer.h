#pragma once

namespace JF
{

class JFCGameTimer
{
public:
	JFCGameTimer();
	virtual ~JFCGameTimer();

public:
	float TotalTime()const; // in seconds
	float DeltaTime()const; // in seconds

	void Reset();			// Call before message loop.
	void Start();			// Call when unpaused.
	void Stop();			// Call when paused.
	void Tick();			// Call every frame.

private:
	double m_SecondsPerCount;
	double m_DeltaTime;

	__int64 m_nBaseTime;
	__int64 m_nPausedTime;
	__int64 m_nStopTime;
	__int64 m_nPrevTime;
	__int64 m_nCurrTime;

	bool m_bStopped;
};

}