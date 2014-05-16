#pragma once

#include "SystemFunctions.h"
#include "RTValue.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	public ref class PluginFunctions
	{
	public:
		delegate void Proc(List<RTValue^>^, RTValue^, SystemFunctions^);

	private:
		Dictionary<DWORD, Proc^> functions;

	public:
		PluginFunctions();

		void Add(TPWPInstance*, String^, Proc^, String^);
		bool Exists(DWORD);
		void Call(SystemFunctions^, DWORD, List<RTValue^>^, RTValue^);
	};
}

