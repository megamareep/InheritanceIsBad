// InheritanceIsBad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "DrawHelper.h"
#include "object_t.h"
#include <unordered_map>
  






//class Booster
//{
//public:
//    Booster()
//        : m_boosters()
//    {
//        m_boosters.emplace(std::make_pair( "D1", Derived1() ));
//        m_boosters.emplace(std::make_pair( "D2", Derived2() ));
//    }
//
//    template<typename ...T>
//    void UseBooster(const std::string& name, T... args) const 
//    {
//        auto found = m_boosters.find(name);
//        if (found != m_boosters.end())
//        {
//            selector::Find(found->second, std::forward<T>(args)...);
//        }
//    }
//
//private:
//    std::unordered_map<std::string, base_t> m_boosters;
//};


using document_t = std::vector<object_t>;
void draw(const document_t& x, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << "<document>" << std::endl;
    for (const auto& e : x)
    {
        draw(e, out, pos + 2);
    }
    out << std::string(pos, ' ') << "</document>" << std::endl;
}

using history_t = std::vector<document_t>;

void commit(history_t& x)
{
    assert(x.size());
    return x.push_back(x.back());
}
void undo(history_t& x)
{
    assert(x.size());
    return x.pop_back();
}
document_t& current(history_t& x)
{
    assert(x.size());
    return x.back();
}

int main()
{
    history_t h(1);

    current(h).emplace_back(0);
    current(h).emplace_back(std::string("Hello!!"));
    current(h).emplace_back(MyClass(60));
    current(h).emplace_back(MyClass2(60));
    current(h).emplace_back(MyClass3());
    current(h).emplace_back(getSomeValue(current(h)[2], 6));
    current(h).emplace_back(getSomeValue(current(h)[2], 65u));
    current(h).emplace_back(getSomeValue(current(h)[3], 55));
    current(h).emplace_back(getSomeValue(current(h)[4], std::vector<int>{2,2,2,2,2}));

    draw(current(h), std::cout, 0);
    std::cout << "--------------------" << std::endl;

    commit(h);
    current(h)[1] = std::string("GAMES");

    auto save = std::async([doc = current(h)]() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "--------SAVE--------" << std::endl;
        draw(doc, std::cout, 0);
    });

    current(h).emplace_back(current(h));
    current(h)[1] = std::string("World");

    draw(current(h), std::cout, 0);
    std::cout << "--------------------" << std::endl;

    undo(h);

    draw(current(h), std::cout, 0);


    //Booster boosters;
    //boosters.UseBooster("D1", std::vector<int>{1, 2, 3});

    //FindB findb;
    //boosters.UseBooster("D2", findb);

    getchar();
}

#include <unordered_map>
#include <memory>




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
