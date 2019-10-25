#pragma once
#include "MyClass.h"
#include "pch.h"

void draw(const MyClass& c, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << "MyClass" << std::endl;
}


//No need to get the value. Better example is a function that uses the data from class to do something. eg draw as above.
int getSomeValue(const MyClass& c)
{
    return c.getSomeValue();
}

template <typename T>
void draw(const T& x, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << x << std::endl;
}

template <typename T>
int getSomeValue(const T& x)
{
    return 0;
}

