#include "pch.h"
#include "MyClass.h"


MyClass::MyClass(int value)
    : someValue(value)
{
}

MyClass::~MyClass()
{
}

int MyClass::getSomeValue() const
{
    return someValue;
}

