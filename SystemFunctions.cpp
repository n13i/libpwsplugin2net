#include "stdafx.h"
#include "SystemFunctions.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

void PWPInvokeProc(TPWPInstance* instance, exit_state_t state, DWORD style, char* pcType, char* pcFname, IRTValue* pRetval, DWORD param);

using namespace PWSPlugin2Net;

// from PluginInterface.cpp
extern TPWPFunctions g_pwpfunc_t;

SystemFunctions::SystemFunctions()
{
}

void SystemFunctions::UpdateInstance(TPWPInstance* inst)
{
	this->instance = inst;
}

bool SystemFunctions::ExportFunctionExists(String^ funcname)
{
	marshal_context ctx;
	bool exists = (FALSE != g_pwpfunc_t.PWPExportFunctionExists(this->instance, ctx.marshal_as<const char*>(funcname)));
	if (!exists)
	{
		DBG("function " + funcname + " is not exported");
	}
	return exists;
}

bool SystemFunctions::IsBasisState()
{
	return (1 == g_pwpfunc_t.PWPIsBasisState(this->instance));
}

String^ SystemFunctions::GetExecPersonaVendor()
{
	int sz = g_pwpfunc_t.PWPGetExecPersonaVendorSize(this->instance);
	char* str = new char[sz];
	g_pwpfunc_t.PWPGetExecPersonaVendor(this->instance, str);
	String^ ret = marshal_as<String^>(str);
	delete[] str;

	return ret;
}

String^ SystemFunctions::GetExecPersonaType()
{
	int sz = g_pwpfunc_t.PWPGetExecPersonaTypeSize(this->instance);
	char* str = new char[sz];
	g_pwpfunc_t.PWPGetExecPersonaType(this->instance, str);
	String^ ret = marshal_as<String^>(str);
	delete[] str;

	return ret;
}

String^ SystemFunctions::GetPersonaDataFolder()
{
	char dest[MAX_PATH];
	g_pwpfunc_t.PWPGetPersonaDataFolder(this->instance, dest);
	return marshal_as<String^>(dest);
}

int SystemFunctions::IsOnLine()
{
	return g_pwpfunc_t.PWPIsOnLine();
}

String^ SystemFunctions::GetProperty(String^ key)
{
	marshal_context ctx;

	const char* pKey = ctx.marshal_as<const char*>(key);
	int sz = g_pwpfunc_t.PWPGetPropertySize(this->instance, pKey);
	if (sz < 0) { return nullptr; }

	String^ ret = nullptr;
	char* dest = new char[sz];
	if (1 == g_pwpfunc_t.PWPGetProperty(this->instance, pKey, dest, sz))
	{
		ret = marshal_as<String^>(dest);
	}
	delete[] dest;

	return ret;
}

int SystemFunctions::PutProperty(String^ key, String^ value)
{
	marshal_context ctx;
	return g_pwpfunc_t.PWPPutProperty(this->instance, ctx.marshal_as<const char*>(key), ctx.marshal_as<const char*>(value));
}

bool SystemFunctions::PropertyExists(String^ key)
{
	marshal_context ctx;
	return (FALSE != g_pwpfunc_t.PWPPropertyExists(this->instance, ctx.marshal_as<const char*>(key)));
}

int SystemFunctions::MakePropertyTree(String^ key, String^ tree)
{
	marshal_context ctx;
	return g_pwpfunc_t.PWPMakePropertyTree(this->instance, ctx.marshal_as<const char*>(key), ctx.marshal_as<const char*>(tree));
}

int SystemFunctions::DelPropertyTree(String^ tree)
{
	marshal_context ctx;
	return g_pwpfunc_t.PWPDelPropertyTree(this->instance, ctx.marshal_as<const char*>(tree));
}

bool SystemFunctions::PropertyTreeExists(String^ tree)
{
	marshal_context ctx;
	return (FALSE != g_pwpfunc_t.PWPPropertyTreeExists(this->instance, ctx.marshal_as<const char*>(tree)));
}

void SystemFunctions::NormalizeTopMosts()
{
	g_pwpfunc_t.PWPNormalizeTopMosts(this->instance);
}

void SystemFunctions::RestoreTopMosts()
{
	g_pwpfunc_t.PWPRestoreTopMosts(this->instance);
}

void SystemFunctions::Wait(int time)
{
	g_pwpfunc_t.PWPWait(this->instance, time);
}

String^ SystemFunctions::GetPluginFolder()
{
	char dest[MAX_PATH];
	g_pwpfunc_t.PWPGetPluginFolder(this->instance, dest);
	return marshal_as<String^>(dest);
}

void SystemFunctions::DBG(String^ msg)
{
	System::Diagnostics::Debug::WriteLine("PWSPlugin.SystemFunctions: " + msg);
}