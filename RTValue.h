#pragma once

#include "pwsRTValue.h"

#include "RTArray.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	public ref class RTValue
	{
	internal:
		IRTValue *value;

	public:
		RTValue(IRTValue*);
		char GetChar();
		int GetInt();
		double GetDouble();
		String^ GetString();
		bool GetBoolean();

		RTValue^ GetReference();
		RTArray^ GetArray();

		void Set(char);
		void Set(int);
		void Set(double);
		void Set(String^);
		void Set(bool);
	};
}
