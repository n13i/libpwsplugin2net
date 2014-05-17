#pragma once

#include "pwsplugin.h"
#include "SystemFunctions.h"
#include "PluginFunctions.h"
#include "Timer.h"
#include "Menu.h"
#include "IPlugin.h"
#include "IPluginInstance.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	/**
	 * プラグインインスタンス
	 *
	 * 起動しているキャラクタ1つに関連して1つ生成される
	 */
	public ref class PluginHost
	{
	internal:
		TPWPInstance* instance;

	public:
		delegate int SynchronizeProc();

	private:
		System::Reflection::Assembly^ pluginAsm;
		IPluginInstance^ pluginInstance;
		PluginFunctions^ pluginFunctions;
		Dictionary<DWORD, Timer^> timers;
		Dictionary<DWORD, Invoker^> invokers;
		Dictionary<DWORD, SynchronizeProc^> synchronizers;
		Menu^ menu;
		SystemFunctions^ systemFunctions;

	public:
		property SystemFunctions^ SysFunc
		{
			SystemFunctions^ get() { return this->systemFunctions; }
		}
		property PluginFunctions^ PluginFunc
		{
			PluginFunctions^ get() { return this->pluginFunctions; }
		}
		property Menu^ PluginMenu
		{
			Menu^ get() { return this->menu; }
		}

		PluginHost(IPlugin^, TPWPInstance*);

		Timer^ CreateTimer(int, Timer::Mode, Timer::Proc^);
		Invoker^ CreateInvoker();
		int Synchronize(SynchronizeProc^);

		void Callback_PluginFunction(TPWPInstance*, List<RTValue^>^, RTValue^, DWORD);
		void Callback_Timer(TPWPInstance*, TPWPTimerHandle, DWORD);
		void Callback_Invoke(TPWPInstance*, exit_state_t, RTValue^, DWORD);
		void Callback_Menu(TPWPInstance*, String^);
		int Callback_Synchronize(TPWPInstance*, DWORD);

		~PluginHost();
		!PluginHost();

	private:
		void UpdateInstance(TPWPInstance* instance);
	
	internal:
		void ExceptionHandler(Exception^ e);

	};
}
