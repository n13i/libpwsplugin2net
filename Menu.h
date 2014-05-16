#pragma once

#include "pwsplugin.h"
#include "MenuItem.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	public ref class Menu
	{
	internal:
		TPWPInstance* instance;

	public:

	private:
		Dictionary<String^, MenuItem^> items;

	public:

		enum class Style {
			Default = MS_NORMAL,
			Group = MS_GROUP,
			Separator = MS_SEPARATOR,
		};

		Menu();
		void UpdateInstance(TPWPInstance*);

		MenuItem^ Add(String^, Style, int, MenuItem::Proc^);
		MenuItem^ Insert(String^, String^, Style, int, MenuItem::Proc^);
		MenuItem^ Rename(MenuItem^, String^);
		bool Delete(String^);

		String^ GetSetupMenuName();

		void Call(String^);
	};
}

