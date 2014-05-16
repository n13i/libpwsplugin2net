/**
* Chararina�{�̂Ƃ̃v���O�C���C���^�[�t�F�[�X
*/
#include "stdafx.h"
#include "pwsplugin.h"
#include "PluginInterface.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

using namespace PWSPlugin2Net;

// �V�X�e���֐��̍\����
TPWPFunctions g_pwpfunc_t;

/**
* ���D����export����֐�(TPWCPluginProc2�^)
* PWPRegisterAyaoriFunc2()�œo�^����
*
* Chararina�{�̂���̃v���O�C���֐��Ăяo���͑S�ċ��ʂ��Ă��̊֐��Ŏ󂯁C
* instance->pdata��param�̑g�ݍ��킹�łǂ̊֐����ĂԂ����߂�
*/
void __stdcall PWCPluginProc2(TPWPInstance* instance, const char* pcArgType, IRTValue** pArgs, int nArg, IRTValue* pRetVal, DWORD param)
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": called");
	PWSPlugin2Net::PluginInterface::CallPluginFunction(instance, pcArgType, pArgs, nArg, pRetVal, param);
}

void PWPInvokeProc(TPWPInstance* instance, exit_state_t state, DWORD style, char* pcType, char* pcFname, IRTValue* pRetval, DWORD param)
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": called");
	PWSPlugin2Net::PluginInterface::CallInvokeCallback(instance, state, style, pcType, pcFname, pRetval, param);
}

void __stdcall PWCTimerProc(TPWPInstance* instance, TPWPTimerHandle handle, DWORD param)
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": called");
	PWSPlugin2Net::PluginInterface::CallTimerProc(instance, handle, param);
}

void __stdcall PWCMenuProc(TPWPInstance* instance, const char* item)
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": called");
	PWSPlugin2Net::PluginInterface::CallMenuProc(instance, item);
}

int __stdcall PWCSynchronizeProc(TPWPInstance *instance, DWORD param)
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + ": called");
	return PWSPlugin2Net::PluginInterface::CallSynchronizeProc(instance, param);
}

/**
* �v���O�C�����{�̂��烍�[�h�����Ƃ�
*
* @param major  Chararina�{�̂̃��W���[�o�[�W����(3.33�� �� 3)
* @param minor  Chararina�{�̂̃}�C�i�[�o�[�W����(3.33�� �� 33)
* @param substr Chararina�{�̂̃o�[�W�����T�u������(3.33�� �� ��)
* @param p      �V�X�e���֐��̍\����
*
* @retval TRUE  �v���O�C����g�ݍ���
* @retval FALSE �v���O�C����g�ݍ��܂Ȃ�
*/
BOOL Initialize(int major, int minor, const char *substr, const struct TPWPFunctions *pfunc)
{
	if (major < 3)
	{
		return FALSE;
	}

	// �V�X�e���֐��\���̂��R�s�[
	unsigned int sz = sizeof(TPWPFunctions);
	memset(&g_pwpfunc_t, 0, sizeof(TPWPFunctions));
	if (pfunc->size < sz)
	{
		sz = pfunc->size;
	}
	memcpy(&g_pwpfunc_t, pfunc, sz);

	return TRUE;
}

/**
* �v���O�C���C���X�^���X����(1�L�����N�^����1��)
*
* @param instance �v���O�C���C���X�^���X
* @param vendor   �L�����N�^�̃x���_�[�R�[�h
* @param type     �L�����N�^�̌^��
*
* @retval 1 ����
* @retval 0 ���s
*/
extern "C" __declspec(dllexport) int __stdcall
PWCNewInstance(TPWPInstance *instance, const char *vendor, const char *type)
{
	if (0 == PWSPlugin2Net::PluginInterface::NewPluginHost(instance, vendor, type))
	{
		return 0;
	}

	return 1;
}


/**
* �v���O�C���C���X�^���X���j�������Ƃ�
*
* @param instance �v���O�C���C���X�^���X
*/
extern "C" __declspec(dllexport) void __stdcall
PWCDestroyInstance(TPWPInstance *instance)
{
	PWSPlugin2Net::PluginInterface::DestroyPluginHost(instance);
}


/**
* �v���O�C�����A�����[�h�����Ƃ�
*/
extern "C" __declspec(dllexport) void __stdcall
PWCDestroy()
{
}

/* ----------------------------------------------------------------------- */

void PluginInterface::SetPluginAssembly(const char* assembly)
{
	PluginInterface::assemblyName = marshal_as<String^>(assembly);
}

/**
 * �v���O�C���C���X�^���X�𐶐�����
 *
 * @retval 1 ����
 * @retval 0 ���s
 *
 * @note �L�����N�^�����������ɋN�������瓯���ɕʃX���b�h����Ăяo�����̂��H
 */
int PluginInterface::NewPluginHost(TPWPInstance* instance, const char* vendor, const char* type)
{
	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + " called");

	if (nullptr == PluginInterface::plugin)
	{
		try
		{
			char dest[MAX_PATH];
			g_pwpfunc_t.PWPGetPluginFolder(instance, dest);

			System::Reflection::Assembly^ assembly = System::Reflection::Assembly::LoadFrom(marshal_as<String^>(dest) + PluginInterface::assemblyName);

			PluginInterface::plugin = safe_cast<PWSPlugin2Net::IPlugin^>(
				assembly->CreateInstance(
					"PWSPlugin.Plugin",
					false,
					System::Reflection::BindingFlags::CreateInstance,
					nullptr,
					nullptr,
					nullptr,
					nullptr
				)
			);
		}
		catch (Exception^ e)
		{
			System::Diagnostics::Debug::WriteLine(e);
			return 0;
		}
	}

	instance->pdata = (void*)new DWORD;
	if (0 == instance->pdata)
	{
		// ���������m�ۂł��Ȃ������H
		System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + " new DWORD failed");
		return 0;
	}

	DWORD id = 0xffffffff;
	for (DWORD i = 0; i < 0xfffffffe; i++)
	{
		if (!PluginInterface::pInsts.ContainsKey(i))
		{
			id = i;
			break;
		}
	}
	if (0xffffffff == id)
	{
		return 0;
	}

	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + " creating new instance with id = " + id);

	*((DWORD*)(instance->pdata)) = id;
	PluginHost^ pinst = gcnew PluginHost(PluginInterface::plugin, instance);

	try
	{
		PluginInterface::pInsts.Add(id, pinst);
	}
	catch (ArgumentException^ e)
	{
		// TODO
		System::Diagnostics::Debug::WriteLine(e);
	}

	return 1;
}

void PluginInterface::DestroyPluginHost(TPWPInstance* instance)
{
	DWORD id = *((DWORD*)(instance->pdata));

	if (PluginInterface::pInsts.ContainsKey(id))
	{
		PluginInterface::pInsts[id]->~PluginHost();
		PluginInterface::pInsts.Remove(id);
	}

	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + " destroying instance with id = " + id);

	// NewPluginHost�Ŋm�ۂ����������̉��
	delete instance->pdata;
}

void PluginInterface::CallPluginFunction(TPWPInstance *instance, const char *pcArgType, IRTValue **pArgs, int nArg, IRTValue *pRetVal, DWORD param)
{
	if (!PluginInterface::PluginHostExists(instance))
	{
		return;
	}

	// �����E�߂�l���}�l�[�W�I�u�W�F�N�g�Ń��b�v����
	List<RTValue^>^ args = gcnew List<RTValue^>;

	for (int i = 0; i < nArg; i++)
	{
		RTValue^ value = gcnew RTValue(pArgs[i]);
		args->Add(value);
	}

	RTValue^ retVal = gcnew RTValue(pRetVal);

	// �Y������PluginHost��CallPluginFunction���Ă�
	PluginInterface::GetPluginHost(instance)->Callback_PluginFunction(instance, args, retVal, param);
}

void PluginInterface::CallTimerProc(TPWPInstance *instance, TPWPTimerHandle handle, DWORD param)
{
	if (!PluginInterface::PluginHostExists(instance))
	{
		return;
	}

	// �Y������PluginHost��CallTimerProc���Ă�
	PluginInterface::GetPluginHost(instance)->Callback_Timer(instance, handle, param);
}

void PluginInterface::CallInvokeCallback(TPWPInstance* instance, exit_state_t state, DWORD style, char* pcType, char* pcFname, IRTValue* pRetval, DWORD param)
{
	if (!PluginInterface::PluginHostExists(instance))
	{
		return;
	}

	RTValue^ retVal = gcnew RTValue(pRetval);

	// �Y������PluginHost��CallTimerProc���Ă�
	PluginInterface::GetPluginHost(instance)->Callback_Invoke(instance, state, retVal, param);
}

void PluginInterface::CallMenuProc(TPWPInstance* instance, const char* item)
{
	if (!PluginInterface::PluginHostExists(instance))
	{
		return;
	}

	marshal_context ctx;

	// �Y������PluginHost��CallTimerProc���Ă�
	PluginInterface::GetPluginHost(instance)->Callback_Menu(instance, ctx.marshal_as<String^>(item));
}

int PWSPlugin2Net::PluginInterface::CallSynchronizeProc(TPWPInstance* instance, DWORD param)
{
	if (!PluginInterface::PluginHostExists(instance))
	{
		return 0xffffffff;
	}

	return PluginInterface::GetPluginHost(instance)->Callback_Synchronize(instance, param);
}

bool PluginInterface::PluginHostExists(TPWPInstance* instance)
{
	DWORD id = *((DWORD*)(instance->pdata));

	if (!PluginInterface::pInsts.ContainsKey(id))
	{
		return false;
	}

	return true;
}

PluginHost^ PluginInterface::GetPluginHost(TPWPInstance* instance)
{
	DWORD id = *((DWORD*)(instance->pdata));

	if (!PluginInterface::pInsts.ContainsKey(id))
	{
		return nullptr;
	}

	System::Diagnostics::Debug::WriteLine(__FUNCTIONW__ + " got plugin host with id = " + id);
	return PluginInterface::pInsts[id];
}
