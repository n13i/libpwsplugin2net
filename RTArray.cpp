#include "stdafx.h"
#include "RTValue.h"
#include "RTArray.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

using namespace PWSPlugin2Net;

RTArray::RTArray(IRTArray* ar)
{
	this->ar = ar;
}

char RTArray::GetCharAt(int idx)
{
	return this->ar->getCharAt(idx);
}

int RTArray::GetIntAt(int idx)
{
	return this->ar->getIntAt(idx);
}

double RTArray::GetDoubleAt(int idx)
{
	return this->ar->getDoubleAt(idx);
}

String^ RTArray::GetStringAt(int idx)
{
	return marshal_as<String^>(this->ar->getStringAt(idx));
}

bool RTArray::GetBooleanAt(int idx)
{
	return (FALSE != this->ar->getBooleanAt(idx));
}

RTValue^ RTArray::GetReferenceAt(int idx)
{
	return gcnew RTValue(this->ar->getReferenceAt(idx));
}

RTArray^ RTArray::GetArrayAt(int idx)
{
	return gcnew RTArray(this->ar->getArrayAt(idx));
}


void RTArray::SetAt(int idx, char c)
{
	this->ar->setCharAt(idx, c);
}

void RTArray::SetAt(int idx, int i)
{
	this->ar->setIntAt(idx, i);
}

void RTArray::SetAt(int idx, double d)
{
	this->ar->setDoubleAt(idx, d);
}

void RTArray::SetAt(int idx, String^ s)
{
	marshal_context ctx;
	this->ar->setStringAt(idx, ctx.marshal_as<const char*>(s));
}

void RTArray::SetAt(int idx, bool b)
{
	this->ar->setBooleanAt(idx, (b ? TRUE : FALSE));
}

int RTArray::GetDimCount()
{
	return this->ar->getDimCount();
}

int RTArray::GetElementCount()
{
	return this->ar->getElementCount();
}

void RTArray::Clear()
{
	this->ar->emptyof();
}
