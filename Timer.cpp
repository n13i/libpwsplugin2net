#include "stdafx.h"
#include "Timer.h"

extern TPWPFunctions g_pwpfunc_t;

using namespace PWSPlugin2Net;

Timer::Timer(TPWPTimerHandle h, Proc^ tp)
{
	this->handle = h;
	this->timerProc = tp;
}

void Timer::Call(SystemFunctions^ sf)
{
	this->timerProc(sf);
}

int Timer::Destroy()
{
	return g_pwpfunc_t.PWPTimer_Destroy(this->handle);
}

int Timer::Start()
{
	return g_pwpfunc_t.PWPTimer_Start(this->handle);
}

int Timer::Stop()
{
	return g_pwpfunc_t.PWPTimer_Stop(this->handle);
}

int Timer::ResetInterval(int interval)
{
	return g_pwpfunc_t.PWPTimer_ResetInterval(this->handle, interval);
}
