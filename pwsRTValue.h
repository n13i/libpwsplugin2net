#ifndef PWSRTValueH
#define PWSRTValueH

#include <windows.h>

typedef unsigned char boolean;

class IRTValue;
class IRTArray;
class IRTVarArray;

class IRTValue {
public:
    virtual DWORD __stdcall Release( void ) = 0;

    virtual boolean __stdcall getBoolean( ) = 0;
    virtual char __stdcall getChar( )       = 0;
    virtual int __stdcall getInt( )         = 0;
    virtual double __stdcall getDouble( )   = 0;
    virtual const char* __stdcall getString( ) = 0;
    virtual IRTValue* __stdcall getReference( ) = 0;
    virtual IRTArray* __stdcall getArray( )     = 0;
    virtual void* __stdcall getValue( int* )   = 0;

    virtual void __stdcall setBoolean( boolean ) = 0;
    virtual void __stdcall setChar( char ) = 0;
    virtual void __stdcall setInt( int ) = 0;
    virtual void __stdcall setDouble( double ) = 0;
    virtual void __stdcall setString( const char* ) = 0;
    virtual void __stdcall setReference( IRTValue* ) = 0;
    virtual void __stdcall setArray( IRTArray* ) = 0;
    virtual void __stdcall setValue( const void* , int ) = 0;

    virtual const char* __stdcall getDescriptor( ) = 0;
};

class IRTArray {
public:
    virtual DWORD __stdcall Release( void ) = 0;

    virtual boolean __stdcall getBooleanAt( int ) = 0;
    virtual char __stdcall getCharAt( int ) = 0;
    virtual int __stdcall getIntAt( int ) = 0;
    virtual double __stdcall getDoubleAt( int ) = 0;
    virtual const char*__stdcall getStringAt( int ) = 0;
    virtual IRTValue* __stdcall getReferenceAt( int ) = 0;
    virtual IRTArray* __stdcall getArrayAt( int ) = 0;

    virtual void __stdcall setBooleanAt( int , boolean ) = 0;
    virtual void __stdcall setCharAt( int , char ) = 0;
    virtual void __stdcall setIntAt( int , int ) = 0;
    virtual void __stdcall setDoubleAt( int , double ) = 0;
    virtual void __stdcall setStringAt( int , const char* ) = 0;
    virtual void __stdcall setReferenceAt( int , IRTValue* ) = 0;
    virtual void __stdcall setArrayAt( int , IRTArray* ) = 0;

    virtual int __stdcall getDimCount( ) = 0;
    virtual int __stdcall getElementCount( ) = 0;
    virtual const char* __stdcall getDescriptor( ) = 0;

    virtual void __stdcall emptyof( ) = 0;
};

class IRTVarArray {
public:
    virtual DWORD __stdcall Release( void ) = 0;

    virtual boolean __stdcall getBooleanAt( int ) = 0;
    virtual char __stdcall getCharAt( int ) = 0;
    virtual int __stdcall getIntAt( int ) = 0;
    virtual double __stdcall getDoubleAt( int ) = 0;
    virtual const char*__stdcall getStringAt( int ) = 0;
    virtual IRTValue* __stdcall getReferenceAt( int ) = 0;
    virtual IRTVarArray* __stdcall getArrayAt( int ) = 0;

    virtual void __stdcall setBooleanAt( int , boolean ) = 0;
    virtual void __stdcall setCharAt( int , char ) = 0;
    virtual void __stdcall setIntAt( int , int ) = 0;
    virtual void __stdcall setDoubleAt( int , double ) = 0;
    virtual void __stdcall setStringAt( int , const char* ) = 0;
    virtual void __stdcall setReferenceAt( int , IRTValue* ) = 0;
    virtual void __stdcall setArrayAt( int , IRTVarArray* ) = 0;

    virtual int __stdcall getDimCount( ) = 0;
    virtual int __stdcall getElementCount( ) = 0;
    virtual const char* __stdcall getDescriptor( ) = 0;

    virtual void __stdcall emptyof( ) = 0;
};

#endif
