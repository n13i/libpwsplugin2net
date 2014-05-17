#include "stdafx.h"
#include "PluginHost.h"

#include "IPluginInstance.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

void __stdcall PWCTimerProc(TPWPInstance* instance, TPWPTimerHandle handle, DWORD param);
int __stdcall PWCSynchronizeProc(TPWPInstance *instance, DWORD param);
extern TPWPFunctions g_pwpfunc_t;

using namespace PWSPlugin2Net;

PluginHost::PluginHost(IPlugin^ plugin, TPWPInstance* instance)
{
	this->systemFunctions = gcnew SystemFunctions();
	this->pluginFunctions = gcnew PluginFunctions();
	this->menu = gcnew Menu();
	this->UpdateInstance(instance);

	try
	{
		this->pluginInstance = plugin->CreateNewInstance();
		this->pluginInstance->Initialize(this);
	}
	catch (Exception^ e)
	{
		this->ExceptionHandler(e);
	}
}

PluginHost::~PluginHost()
{
	try
	{
		this->pluginInstance->Destroy();
	}
	catch (Exception^ e)
	{
		this->ExceptionHandler(e);
	}
	this->!PluginHost();
}

PluginHost::!PluginHost()
{
	for each (Timer^ timer in this->timers.Values)
	{
		timer->Destroy();
	}
}

Timer^ PluginHost::CreateTimer(int interval, Timer::Mode mode, Timer::Proc^ proc)
{
	if (nullptr == this->instance)
	{
		return nullptr;
	}

	DWORD id = 0xffffffff;

	for (DWORD i = 0; i < 0xfffffffe; i++)
	{
		if (!this->timers.ContainsKey(i))
		{
			id = i;
			break;
		}
	}
	if (0xffffffff == id)
	{
		return nullptr;
	}

	TPWPTimerHandle h = g_pwpfunc_t.PWPTimer_Create(instance, interval, (int)(mode), PWCTimerProc, id);
	if (0 == h)
	{
		System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": Timer_Create failed");
		return nullptr;
	}

	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": register timer (handle=" + h + ") id=" + id);

	Timer^ t = gcnew Timer(h, proc);
	this->timers.Add(id, t);

	return t;
}

Invoker^ PluginHost::CreateInvoker()
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": called");

	DWORD id = 0xffffffff;

	for (DWORD i = 0; i < 0xfffffffe; i++)
	{
		if (!this->invokers.ContainsKey(i))
		{
			id = i;
			break;
		}
	}
	if (0xffffffff == id)
	{
		return nullptr;
	}

	Invoker^ invoker = gcnew Invoker(this->instance, id);
	this->invokers.Add(id, invoker);
	return invoker;
}

int PluginHost::Synchronize(SynchronizeProc^ proc)
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": called");

	DWORD id = 0xffffffff;

	for (DWORD i = 0; i < 0xfffffffe; i++)
	{
		if (!this->synchronizers.ContainsKey(i))
		{
			id = i;
			break;
		}
	}
	if (0xffffffff == id)
	{
		return 0xffffffff;
	}

	this->synchronizers.Add(id, proc);

	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": calling PWPSynchronize");
	DWORD inst_id = *((DWORD*)(this->instance->pdata));
	DWORD inst_ptr = (DWORD)this->instance;
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": instance with id = " + id + ", ptr = " + inst_ptr);

	int ret = g_pwpfunc_t.PWPSynchronize(this->instance, PWCSynchronizeProc, id);

	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": done, ret = " + ret);
	return ret;
}

/* ----------------------------------------------------------------------- */
// PluginInterface側からのコールバックメソッド呼び出しリクエスト
void PluginHost::Callback_PluginFunction(TPWPInstance* instance, List<RTValue^>^ args, RTValue^ retVal, DWORD param)
{
	this->UpdateInstance(instance);

	if (!this->pluginFunctions->Exists(param))
	{
		return;
	}

	try
	{
		this->pluginFunctions->Call(param, args, retVal);
	}
	catch (Exception^ e)
	{
		this->ExceptionHandler(e);
	}
}

void PluginHost::Callback_Timer(TPWPInstance* instance, TPWPTimerHandle handle, DWORD param)
{
	this->UpdateInstance(instance);

	if (!this->timers.ContainsKey(param))
	{
		return;
	}

	try
	{
		this->timers[param]->Call();
	}
	catch (Exception^ e)
	{
		this->ExceptionHandler(e);
	}
}

void PluginHost::Callback_Invoke(TPWPInstance* instance, exit_state_t state, RTValue^ retVal, DWORD param)
{
	this->UpdateInstance(instance);

	if (!this->invokers.ContainsKey(param))
	{
		return;
	}

	try
	{
		this->invokers[param]->Callback(state, retVal);
	}
	catch (Exception^ e)
	{
		this->ExceptionHandler(e);
	}
	this->invokers.Remove(param);
}

void PluginHost::Callback_Menu(TPWPInstance* instance, String^ item)
{
	this->UpdateInstance(instance);

	// 2014/05/05
	// itemを"aaa\\bbb"として登録した際，コールバックされるitemが"aaa\nbbb"になっているみたい
	// 登録時に最初から\nにしといたほうがいいかも
	try
	{
		this->menu->Call(item);
	}
	catch (Exception^ e)
	{
		this->ExceptionHandler(e);
	}
}

int PluginHost::Callback_Synchronize(TPWPInstance* instance, DWORD param)
{
	this->UpdateInstance(instance);

	if (!this->synchronizers.ContainsKey(param))
	{
		return 0xffffffff;
	}

	SynchronizeProc^ proc = this->synchronizers[param];
	this->synchronizers.Remove(param);

	int ret;
	try
	{
		ret = proc();
	}
	catch (Exception^ e)
	{
		this->ExceptionHandler(e);
	}

	return ret;
}

// private
void PluginHost::UpdateInstance(TPWPInstance* instance)
{
	DWORD id = *((DWORD*)instance->pdata);
	DWORD inst_ptr = (DWORD)instance;
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": updating instance with id = " + id + ", ptr = " + inst_ptr);

	this->instance = instance;

	this->systemFunctions->UpdateInstance(instance);
	this->pluginFunctions->UpdateInstance(instance);
	this->menu->UpdateInstance(instance);
	for each (Invoker^ invoker in this->invokers.Values)
	{
		invoker->UpdateInstance(instance);
	}
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": updated instance with id = " + id);
}

// internal
void PluginHost::ExceptionHandler(Exception^ e)
{
	System::Windows::Forms::MessageBox::Show(e->ToString(), "LibPWSPlugin2Net");
	throw e;
}
