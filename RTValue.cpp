#include "stdafx.h"
#include "RTValue.h"

#include <msclr/marshal.h>
using namespace msclr::interop;

using namespace PWSPlugin2Net;

RTValue::RTValue(IRTValue* value)
{
	this->value = value;
}

char RTValue::GetChar()
{
	return this->value->getChar();
}

int RTValue::GetInt()
{
	return this->value->getInt();
}

double RTValue::GetDouble()
{
	return this->value->getDouble();
}

String^ RTValue::GetString()
{
	return marshal_as<String^>(this->value->getString());
}

bool RTValue::GetBoolean()
{
	return (FALSE != this->value->getBoolean());
}

RTValue^ RTValue::GetReference()
{
	return gcnew RTValue(this->value->getReference());
}

RTArray^ RTValue::GetArray()
{
	return gcnew RTArray(this->value->getArray());
}

void RTValue::Set(char c)
{
	this->value->setChar(c);
}

void RTValue::Set(int i)
{
	this->value->setInt(i);
}

void RTValue::Set(double d)
{
	this->value->setDouble(d);
}

void RTValue::Set(String^ s)
{
	marshal_context ctx;
	this->value->setString(ctx.marshal_as<const char*>(s));
}

void RTValue::Set(bool b)
{
	this->value->setBoolean((b ? TRUE : FALSE));
}
