#pragma once

#include "pwsRTValue.h"

using namespace System;
using namespace System::Collections::Generic;

namespace PWSPlugin2Net
{
	ref class RTValue;

	public ref class RTArray
	{
	internal:
		IRTArray *ar;

	public:
		RTArray(IRTArray*);

		char GetCharAt(int);
		int GetIntAt(int);
		double GetDoubleAt(int);
		String^ GetStringAt(int);
		bool GetBooleanAt(int);

		RTValue^ GetReferenceAt(int);
		RTArray^ GetArrayAt(int);

		void SetAt(int, char);
		void SetAt(int, int);
		void SetAt(int, double);
		void SetAt(int, String^);
		void SetAt(int, bool);

		int GetDimCount();
		int GetElementCount();

		void Clear();
	};
}
