//***************************************************************************************
// GameTimer.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "stdafx.h"
#include "GameTimer.h"

JF::JFCGameTimer::JFCGameTimer()
: m_SecondsPerCount(0.0), m_DeltaTime(-1.0), m_nBaseTime(0),
m_nPausedTime(0), m_nPrevTime(0), m_nCurrTime(0), m_bStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec;
}

JF::JFCGameTimer::~JFCGameTimer()
{
}

// Returns the total time elapsed since Reset() was called, NOT counting any
// time when the clock is stopped.
float JF::JFCGameTimer::TotalTime() const
{
	// If we are stopped, do not count the time that has passed since we stopped.
	// Moreover, if we previously already had a pause, the distance 
	// m_nStopTime - m_nBaseTime includes paused time, which we do not want to count.
	// To correct this, we can subtract the paused time from m_nStopTime:  
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  m_nBaseTime       m_nStopTime        startTime     m_nStopTime    m_nCurrTime

	if (m_bStopped)
	{
		return (float)(((m_nStopTime - m_nPausedTime) - m_nBaseTime)*m_SecondsPerCount);
	}

	// The distance m_nCurrTime - m_nBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from m_nCurrTime:  
	//
	//  (m_nCurrTime - m_nPausedTime) - m_nBaseTime 
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  m_nBaseTime       m_nStopTime        startTime     m_nCurrTime

	else
	{
		return (float)(((m_nCurrTime - m_nPausedTime) - m_nBaseTime)*m_SecondsPerCount);
	}
}

float JF::JFCGameTimer::DeltaTime() const
{
	return (float)m_DeltaTime;
}

void JF::JFCGameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_nBaseTime	= currTime;
	m_nPrevTime	= currTime;
	m_nStopTime	= 0;
	m_bStopped	= false;
}

void JF::JFCGameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  m_nBaseTime       m_nStopTime        startTime     

	if( m_bStopped )
	{
		m_nPausedTime += (startTime - m_nStopTime);	

		m_nPrevTime = startTime;
		m_nStopTime = 0;
		m_bStopped  = false;
	}
}

void JF::JFCGameTimer::Stop()
{
	if( !m_bStopped )
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_nStopTime = currTime;
		m_bStopped  = true;
	}
}

void JF::JFCGameTimer::Tick()
{
	if( m_bStopped )
	{
		m_DeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_nCurrTime = currTime;

	// Time difference between this frame and the previous.
	m_DeltaTime = (m_nCurrTime - m_nPrevTime)*m_SecondsPerCount;

	// Prepare for next frame.
	m_nPrevTime = m_nCurrTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then m_DeltaTime can be negative.
	if(m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}
}
