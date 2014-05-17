#pragma once

#include "pwsplugin.h"
#include "RTValue.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	public ref class PluginFunctions
	{
	internal:
		TPWPInstance* instance;

	public:
		delegate void Proc(List<RTValue^>^, RTValue^);

	private:
		Dictionary<DWORD, Proc^> functions;

	public:
		PluginFunctions();
		void UpdateInstance(TPWPInstance*);

		void Add(String^, Proc^, String^);
		bool Exists(DWORD);
		void Call(DWORD, List<RTValue^>^, RTValue^);
	};
}

