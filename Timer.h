#pragma once

#include "pwsplugin.h"
#include "SystemFunctions.h"

namespace PWSPlugin2Net
{
	public ref class Timer
	{
	public:
		delegate void Proc(SystemFunctions^);

	private:
		TPWPTimerHandle handle;
		Proc^ timerProc;

	public:
		enum class Mode {
			Oneshot = TM_ONESHOT,
			Interval = TM_INTERVAL,
		};
		Timer(TPWPTimerHandle, Proc^);
		void Call(SystemFunctions^);
		int Destroy();
		int Start();
		int Stop();
		int ResetInterval(int);
	};
}
