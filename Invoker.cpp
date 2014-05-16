#include "stdafx.h"
#include "Invoker.h"

#include <string.h>

#include <msclr/marshal.h>
using namespace msclr::interop;

void PWPInvokeProc(TPWPInstance* instance, exit_state_t state, DWORD style, char* pcType, char* pcFname, IRTValue* pRetval, DWORD param);
extern TPWPFunctions g_pwpfunc_t;

using namespace System::IO;
using namespace System::Runtime::InteropServices;
using namespace PWSPlugin2Net;

Invoker::Invoker(TPWPInstance* instance, DWORD id)
{
	this->instance = instance;
	this->id = id;
}

/**
 * 制限事項
 *   引数は10個まで
 *   char型，double型，固定長配列，可変長配列には未対応
 */
int Invoker::Invoke(Style style, String^ type, String^ funcname, InvokeCallback^ cb, ...array<Object^>^ args)
{
	System::Diagnostics::Debug::WriteLine("{0}: called", __FUNCTIONW__);

	const int MAX_ARGS = 10;
	UInt32 m[MAX_ARGS];

	marshal_context ctx;

	for (int i = 0; i < MAX_ARGS; i++)
	{
		if (i >= args->Length)
		{
			m[i] = 0;
		}
		else if (args[i]->GetType() == String::typeid)
		{
			m[i] = (UInt32)ctx.marshal_as<const char*>(safe_cast<String^>(args[i]));
		}
		else if (args[i]->GetType() == int::typeid)
		{
			m[i] = safe_cast<int>(args[i]);
		}
		else if (args[i]->GetType() == bool::typeid)
		{
			m[i] = safe_cast<bool>(args[i]);
		}
		else
		{
			System::Diagnostics::Debug::WriteLine("{0}: unsupported type: {1}", __FUNCTIONW__, args[i]->GetType());
			m[i] = 0;
		}
		//System::Diagnostics::Debug::WriteLine("{0}: m[{1}] = {2}", __FUNCTIONW__, i, m[i]);
	}

	System::Diagnostics::Debug::WriteLine("{0}: argument prepared", __FUNCTIONW__);

	const char* pcType = ctx.marshal_as<const char*>(type);
	const char* pcFname = ctx.marshal_as<const char*>(funcname);

	const int MAX_NAME = 1024;
	char pType[MAX_NAME], pFname[MAX_NAME];

	memset(pType, 0, sizeof(char) * MAX_NAME);
	memcpy_s(pType, sizeof(char) * MAX_NAME, pcType, strlen(pcType));
	//for (unsigned int i = 0; i < strlen(pcType); i++)
	//{
	//	System::Diagnostics::Debug::WriteLine("[{0}] pcType={1:x} pType={2:x}", i, pcType[i], pType[i]);
	//}

	memset(pFname, 0, sizeof(char) * MAX_NAME);
	memcpy_s(pFname, sizeof(char)* MAX_NAME, pcFname, strlen(pcFname));
	//for (unsigned int i = 0; i < strlen(pcFname); i++)
	//{
	//	System::Diagnostics::Debug::WriteLine("[{0}] pcFname={1:x} pFname={2:x}", i, pcFname[i], pFname[i]);
	//}

	System::Diagnostics::Debug::WriteLine("{0}: PWPInvoke {1} {2}", __FUNCTIONW__, type, funcname);

	// 2014/05/03
	// Chararina側からコールバックされる際に本体側で読み込み違反になる
	// プラグイン関数呼び出しの中でInvokeするのはNG?
	// タイマコールバック内で呼んだらOKだった
	//int ret = g_pwpfunc_t.PWPInvoke(this->instance, style, "eV(S)", "NH_TESTPLUGIN_cTest2", PWPInvokeProc, 0, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9]);
	//int ret = g_pwpfunc_t.PWPInvoke(this->instance, style, "eV(SS)", "NH_TESTPLUGIN_cTest3", PWPInvokeProc, 0, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9]);
	//int ret = g_pwpfunc_t.PWPInvoke(this->instance, (DWORD)style, "eV(ISB)", "NH_TESTPLUGIN_cTest4", PWPInvokeProc, 0, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9]);

	int ret = g_pwpfunc_t.PWPInvoke(
		this->instance,
		(DWORD)style,
		pType,
		pFname,
		PWPInvokeProc,
		this->id,
		m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9]);

	System::Diagnostics::Debug::WriteLine("{0}: ret = {1}", __FUNCTIONW__, ret);

	if (1 == ret)
	{
		this->callback = cb;
	}

	return ret;
}

void Invoker::Callback(exit_state_t state, RTValue^ retVal)
{
	ExitState st = ExitState::None;
	if (AYAF_SUCCEED == state) { st = ExitState::Succeed; }
	else if (AYAF_CANCEL == state) { st = ExitState::Cancel; }
	else if (AYAF_FATAL_ERROR == state) { st = ExitState::FatalError; }

	if (nullptr != this->callback)
	{
		this->callback(st, retVal);
	}
}

void Invoker::UpdateInstance(TPWPInstance* instance)
{
	this->instance = instance;
}
