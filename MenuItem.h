#pragma once

#include "pwsplugin.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	public ref class MenuItem
	{
	internal:
		TPWPInstance* instance;

	public:
		delegate void Proc(String^);

	private:
		String^ item;
		Proc^ proc;

	public:
		property String^ Name {
			String^ get() { return this->item; }
			void set(String^ value) { this->item = value; }
		}

		MenuItem(String^, Proc^);
		void UpdateInstance(TPWPInstance*);

		bool SetState(bool);
		int GetState();
		String^ GetSelect();
		bool SetEnable(bool);
		int GetEnable();
		bool SetVisible(bool);
		int GetVisible();

		void Call();
	};
}

