#pragma once
#include "MyClass.h"
#include "pch.h"

void draw(const MyClass& c, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << "MyClass" << std::endl;
}

template<typename T,  typename ...Tu>
struct has_getValue_function
{
private:
	typedef std::true_type yes;
	typedef std::false_type no;
 
	template<typename U> static auto test(int, Tu...args) -> decltype(std::declval<U>().getValue(args...) == 1, yes());
	template<typename> static no test(...);

    static constexpr bool test2Val = std::is_same<decltype(test<T>(0)), yes>::value;
    static constexpr bool test1Val = std::is_same<decltype(test<T>(0, 0)),yes>::value;
    static constexpr bool test3Val = std::is_same<decltype(test<T>(0, std::vector<int>{0})), yes > ::value;
public:
    static constexpr bool value = test1Val || test2Val || test3Val;
};


template<typename T, typename ...Tu>
typename std::enable_if<has_getValue_function<T, Tu...>::value, int>::type
getSomeValue(const T& x, Tu... args) 
{
    return x.getValue(args...);
}

template <typename T>
void draw(const T& x, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << x << std::endl;
}


int getSomeValue(...) 
{
    return 0;
}

