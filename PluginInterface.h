#pragma once

#include "pwsplugin.h"
#include "PluginHost.h"
#include "IPlugin.h"

using namespace System;
using namespace System::Collections::Generic;

BOOL Initialize(int major, int minor, const char *substr, const struct TPWPFunctions *pfunc);

namespace PWSPlugin2Net
{
	public ref class PluginInterface
	{
	private:
		static Dictionary<DWORD, PluginHost^> pInsts;
		static PluginHost^ GetPluginHost(TPWPInstance*);
		static bool PluginHostExists(TPWPInstance*);
		static IPlugin^ plugin;
		static String^ assemblyName;

	public:
		static void SetPluginAssembly(const char*);
		static int NewPluginHost(TPWPInstance*, const char*, const char*);
		static void DestroyPluginHost(TPWPInstance*);

		static void CallPluginFunction(TPWPInstance*, const char*, IRTValue**, int, IRTValue*, DWORD);
		static void CallTimerProc(TPWPInstance*, TPWPTimerHandle, DWORD);
		static void CallInvokeCallback(TPWPInstance* instance, exit_state_t state, DWORD style, char* pcType, char* pcFname, IRTValue* pRetval, DWORD param);
		static void CallMenuProc(TPWPInstance*, const char*);
		static int CallSynchronizeProc(TPWPInstance*, DWORD);
	};
}
