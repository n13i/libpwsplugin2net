#include "stdafx.h"
#include "MenuItem.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

void __stdcall PWCMenuProc(TPWPInstance* instance, const char* item);
extern TPWPFunctions g_pwpfunc_t;

using namespace PWSPlugin2Net;

MenuItem::MenuItem(String^ item, Proc^ proc)
{
	this->item = item;
	this->proc = proc;
}

void MenuItem::UpdateInstance(TPWPInstance* instance)
{
	this->instance = instance;
}

bool MenuItem::SetState(bool check)
{
	marshal_context ctx;
	if (1 != g_pwpfunc_t.PWPMenuItem_SetState(this->instance, ctx.marshal_as<const char*>(this->item), check))
	{
		return false;
	}

	return true;
}

int MenuItem::GetState()
{
	marshal_context ctx;
	return g_pwpfunc_t.PWPMenuItem_GetState(this->instance, ctx.marshal_as<const char*>(this->item));
}

String^ MenuItem::GetSelect()
{
	marshal_context ctx;
	const char* sel = g_pwpfunc_t.PWPMenuItem_GetSelect(this->instance, ctx.marshal_as<const char*>(this->item));
	if (NULL == sel)
	{
		return nullptr;
	}

	return marshal_as<String^>(sel);
}

bool MenuItem::SetEnable(bool enable)
{
	marshal_context ctx;
	if (1 != g_pwpfunc_t.PWPMenuItem_SetEnable(this->instance, ctx.marshal_as<const char*>(this->item), enable))
	{
		return false;
	}

	return true;
}

int MenuItem::GetEnable()
{
	marshal_context ctx;
	return g_pwpfunc_t.PWPMenuItem_GetEnable(this->instance, ctx.marshal_as<const char*>(this->item));
}

bool MenuItem::SetVisible(bool visible)
{
	marshal_context ctx;
	if (1 != g_pwpfunc_t.PWPMenuItem_SetVisible(this->instance, ctx.marshal_as<const char*>(this->item), visible))
	{
		return false;
	}

	return true;
}

int MenuItem::GetVisible()
{
	marshal_context ctx;
	return g_pwpfunc_t.PWPMenuItem_GetVisible(this->instance, ctx.marshal_as<const char*>(this->item));
}

void MenuItem::Call()
{
	this->proc(this->item);
}