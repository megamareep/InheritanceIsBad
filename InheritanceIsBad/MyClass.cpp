#include "pch.h"
#include "MyClass.h"


MyClass::MyClass(int value)
    : someValue(value)
{
}

MyClass::~MyClass()
{
}

int MyClass::getValue() const
{
    return someValue;
}

int MyClass::getValue(int value) const
{
    return value;
}


MyClass2::MyClass2(int value)
    : someValue(value)
{
}

int MyClass2::getValue(int value) const
{
    return value;
}

