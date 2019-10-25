// InheritanceIsBad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "MyClass.h"
#include "DrawHelper.h"


class object_t {
public:
    template <typename T>
    object_t(T x)
        : m_self(std::make_shared<model<T>>(std::move(x)))
    {}

    friend void draw(const object_t& x, std::ostream& out, size_t pos)
    {
        x.m_self->draw_(out, pos);
    }

    friend int getSomeValue(const object_t& x)
    {
        return x.m_self->getSomeValue_();
    }

private:
    struct concept_t {
        virtual ~concept_t() = default;
        virtual void draw_(std::ostream&, size_t) const = 0;
        virtual int getSomeValue_() const = 0;
    };
    template<typename T>
    struct model : concept_t {
        model(T x) : m_data(std::move(x)) {}
        void draw_(std::ostream& out, size_t position) const override
        {
            draw(m_data, out, position);
        }

        int getSomeValue_() const override
        {
            return getSomeValue(m_data);
        }
        T m_data;
    };
    //shared pointer to an immutable type has value semantics.
    //this is why passing cont & works.
    std::shared_ptr<const concept_t> m_self;
};

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
    current(h).emplace_back(getSomeValue(current(h)[2]));

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

    getchar();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
