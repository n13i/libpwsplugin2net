#pragma once

#include "pwsplugin.h"
#include "Invoker.h"
#include "RTValue.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	public ref class SystemFunctions
	{
	internal:
		TPWPInstance* instance;

	private:
		Dictionary<DWORD, Invoker^> invokers;

	public:
		SystemFunctions();
		void UpdateInstance(TPWPInstance*);

		//int Call();
		bool ExportFunctionExists(String^);

		//int RegisterAyaoriFunc();
		bool IsBasisState();
		//HWND GetWindowHandle(DWORD); // TODO Unimplemented
		String^ GetExecPersonaVendor();
		String^ GetExecPersonaType();
		String^ GetPersonaDataFolder();
		static int IsOnLine();
		String^ GetProperty(String^);
		int PutProperty(String^, String^);
		bool PropertyExists(String^);
		int MakePropertyTree(String^, String^);
		int DelPropertyTree(String^);
		bool PropertyTreeExists(String^);

		void NormalizeTopMosts();
		void RestoreTopMosts();
		void Wait(int);
		String^ GetPluginFolder();

	private:
		void DBG(String^);
	};
}
