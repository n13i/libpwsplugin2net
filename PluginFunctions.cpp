#include "stdafx.h"
#include "PluginFunctions.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

// Chararina�{�̑�����R�[���o�b�N�����֐��̃v���g�^�C�v�錾(���̂�PluginInterface.cpp�Œ�`)
void __stdcall PWCPluginProc2(TPWPInstance* instance, const char* pcArgType, IRTValue** pArgs, int nArg, IRTValue* pRetVal, DWORD param);

extern TPWPFunctions g_pwpfunc_t;

using namespace PWSPlugin2Net;

PluginFunctions::PluginFunctions()
{
}

void PluginFunctions::Add(TPWPInstance* instance, String^ functionName, PluginFunctions::Proc^ f, String^ descriptor)
{
	DWORD id = 0xffffffff;

	for (DWORD i = 0; i < 0xfffffffe; i++)
	{
		if (!this->functions.ContainsKey(i))
		{
			id = i;
			break;
		}
	}
	if (0xffffffff == id)
	{
		return;
	}

	// TODO String^���琶������const char*�̐������Ԃ͂��̃��\�b�h�𔲂���܂ł���
	// Chararina�{�̑��ŃR�s�[���Ă���Ă���̂��H
	marshal_context ctx;
	g_pwpfunc_t.PWPRegisterAyaoriFunc2(instance, ctx.marshal_as<const char*>(functionName), PWCPluginProc2, ctx.marshal_as<const char*>(descriptor), id);

	System::Diagnostics::Debug::WriteLine("register " + functionName + " id=" + id);

	this->functions.Add(id, f);
}

bool PluginFunctions::Exists(DWORD id)
{
	return functions.ContainsKey(id);
}

void PluginFunctions::Call(SystemFunctions^ sf, DWORD param, List<RTValue^>^ args, RTValue^ retVal)
{
	if (!this->functions.ContainsKey(param))
	{
		return;
	}

	this->functions[param](args, retVal, sf);
}
