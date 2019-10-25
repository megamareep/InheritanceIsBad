#pragma once
class MyClass
{
public:
    explicit MyClass(int value);
    ~MyClass();

    int getSomeValue() const;

private:
    int someValue;
};
