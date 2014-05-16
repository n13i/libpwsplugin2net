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

		//PluginMenuItem^ SystemFunctions::CreateMenuItem();
			
		//int Call();
		bool ExportFunctionExists(String^);

		//int RegisterAyaoriFunc();
		bool IsBasisState();
		//HWND GetWindowHandle(DWORD);
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
/*
		int MenuItem_Add();
		int Menuitem_Insert();
		int MenuItem_Rename();
		int MenuItem_Delete();
		int MenuItem_SetState();
		int MenuItem_GetState();
		int MenuItem_SetEnable();
		int MenuItem_GetEnable();
		int MenuItem_SetVisible();
		int MenuItem_GetVisible();
		String^ MenuItem_GetSelect();
		String^ MenuItem_GetSetupMenuName();
		TPWPTimerHandle Timer_Create(int);
		int Timer_Destroy();
		int Timer_Start();
		int Timer_Stop();
		int Timer_ResetInterval();
		int Synchronize();
		*/
		void NormalizeTopMosts();
		void RestoreTopMosts();
		void Wait(int);
		String^ GetPluginFolder();

	private:
		void DBG(String^);
	};
}
