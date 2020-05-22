#pragma once
#include <iostream>
#include <numeric>
class MyClass
{
public:
    explicit MyClass(int value);
    ~MyClass();

    int getValue() const;
    int getValue(int value) const;
    int operator() (){ return someValue; }
private:
    int someValue;
};

class MyClass3
{
public:
    int getValue(const std::vector<int>& ints) const 
    {
        int sum = std::accumulate(ints.begin(),ints.end(), 0);
        return sum;
    }
    friend std::ostream& operator<<(std::ostream& os, const MyClass3&)
    {
        return os << "MyClass3";
    }
private:
};

class MyClass2
{
public:
    explicit MyClass2(int value);

    //int getValue() const { return someValue; }
    int getValue(int value) const;
    int operator() (){ return someValue; }
    friend std::ostream& operator<<(std::ostream& os, const MyClass2&)
    {
        return os << "MyClass2";
    }
private:
    int someValue;
};

//#include "object_t.h"


//class Derived1
//{
//public:
//    void Find(const std::vector<int>& find) const
//    {
//        //for (const auto& child : m_children)
//        //{
//        //    Find(child, find);
//        //}
//        Filter(find);
//    }
//
//     void addChild(base_t&& child)
//    {
//        m_children.emplace_back(std::move(child));
//    }
//private:
//    void Filter(const std::vector<int>& find) const
//    {
//        std::cout << "Filter : Derived1" << std::endl;
//    }
//    std::vector<base_t> m_children;
//};
//
//class Derived2
//{
//public:
//
//    void Find(const FindB& find) const
//    {
//        //for (auto child : m_children)
//        //{
//        //    Find(child, find);
//        //}
//        //Filter(find);
//    }
//
//private:
//     void Filter(const FindB& find) const
//    {
//        std::cout << "Filter : Derived2" << std::endl;
//    }
//    std::vector<base_t> m_children;
//};