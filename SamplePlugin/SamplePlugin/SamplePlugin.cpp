// SamplePlugin.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "../../PluginInterface.h"
#include "property.h"

extern "C" __declspec(dllexport) BOOL __stdcall
PWCInitialize(int major, int minor, const char *substr, const struct TPWPFunctions *pfunc)
{
	PWSPlugin2Net::PluginInterface::SetPluginAssembly(PLUGIN_ASSEMBLY);
	return Initialize(major, minor, substr, pfunc);
}
