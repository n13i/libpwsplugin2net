#pragma once

#include "pwsplugin.h"
#include "RTValue.h"
#include "RTArray.h"

using namespace System;

namespace PWSPlugin2Net
{
	public ref class Invoker
	{
	public:
		enum class Style {
			Invoke = CS_INVOKE,
			Interrupt = CS_INTERRUPT,
		};

		enum class ExitState {
			Succeed = AYAF_SUCCEED,
			Cancel = AYAF_CANCEL,
			FatalError = AYAF_FATAL_ERROR,
			None = AYAF_NONE,
		};

		delegate void Proc(ExitState, RTValue^);

	private:
		TPWPInstance* instance;
		DWORD id;
		Proc^ callback;

	public:
		Invoker(TPWPInstance*, DWORD);
		int Invoke(Style, String^, String^, Proc^, ...array<Object^>^);
		void Callback(exit_state_t, RTValue^);
		void UpdateInstance(TPWPInstance*);
	};
}
