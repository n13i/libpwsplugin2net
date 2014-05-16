#include "stdafx.h"
#include "Menu.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

void __stdcall PWCMenuProc(TPWPInstance* instance, const char* item);
extern TPWPFunctions g_pwpfunc_t;

using namespace PWSPlugin2Net;

Menu::Menu()
{
}

void Menu::UpdateInstance(TPWPInstance* instance)
{
	this->instance = instance;
	for each (MenuItem^ menu in this->items.Values)
	{
		menu->UpdateInstance(instance);
	}
}

MenuItem^ Menu::Add(String^ item, Style style, int groupId, MenuItem::Proc^ proc)
{
	if (this->items.ContainsKey(item))
	{
		return nullptr;
	}

	marshal_context ctx;
	if (1 != g_pwpfunc_t.PWPMenuItem_Add(this->instance, ctx.marshal_as<const char*>(item), (int)style, groupId, PWCMenuProc))
	{
		return nullptr;
	}

	MenuItem^ menu = gcnew MenuItem(item, proc);
	this->items.Add(item, menu);
	return menu;
}

MenuItem^ Menu::Insert(String^ nextitem, String^ item, Style style, int groupId, MenuItem::Proc^ proc)
{
	if (!this->items.ContainsKey(nextitem) || this->items.ContainsKey(item))
	{
		return nullptr;
	}

	marshal_context ctx;
	if (1 != g_pwpfunc_t.PWPMenuItem_Insert(this->instance, ctx.marshal_as<const char*>(nextitem), ctx.marshal_as<const char*>(item), (int)style, groupId, PWCMenuProc))
	{
		return nullptr;
	}

	MenuItem^ menu = gcnew MenuItem(item, proc);
	this->items.Add(item, menu);
	return menu;
}

MenuItem^ Menu::Rename(MenuItem^ item, String^ newname)
{
	if (!this->items.ContainsKey(item->Name) || this->items.ContainsKey(newname))
	{
		return item;
	}

	marshal_context ctx;
	if (1 != g_pwpfunc_t.PWPMenuItem_Rename(this->instance, ctx.marshal_as<const char*>(item->Name), ctx.marshal_as<const char*>(newname)))
	{
		return item;
	}

	this->items.Remove(item->Name);
	item->Name = newname;
	this->items.Add(item->Name, item);
	return item;
}

bool Menu::Delete(String^ item)
{
	if (!this->items.ContainsKey(item))
	{
		return false;
	}

	marshal_context ctx;
	if (1 != g_pwpfunc_t.PWPMenuItem_Delete(this->instance, ctx.marshal_as<const char*>(item)))
	{
		return false;
	}

	this->items.Remove(item);
	return true;
}

String^ Menu::GetSetupMenuName()
{
	marshal_context ctx;
	const char* sel = g_pwpfunc_t.PWPMenuItem_GetSetupMenuName(this->instance);
	if (NULL == sel)
	{
		return nullptr;
	}

	return marshal_as<String^>(sel);
}

void Menu::Call(String^ item)
{
	if (!this->items.ContainsKey(item))
	{
		System::Diagnostics::Debug::WriteLine("{0}: menu item {1} is not in items!", __FUNCTIONW__, item);
		return;
	}

	this->items[item]->Call();
}