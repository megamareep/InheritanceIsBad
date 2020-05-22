#pragma once
#include "pch.h"

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

    template<typename ...T>
    friend int getSomeValue(const object_t& x, T...args)
    {
        return x.m_self->getSomeValue_(args...);
    }

private:
    struct concept_t {
        virtual ~concept_t() = default;
        virtual void draw_(std::ostream&, size_t) const = 0;
        virtual int getSomeValue_() const = 0;
        virtual int getSomeValue_(int) const = 0;
        virtual int getSomeValue_(const std::vector<int>& ) const = 0;
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

        int getSomeValue_(int data) const override
        {
            return getSomeValue(m_data, data);
        }

        int getSomeValue_(const std::vector<int>& data) const override
        {
            return getSomeValue(m_data, data);
        }
        T m_data;
    };
    //shared pointer to an immutable type has value semantics.
    //this is why passing cont & works.
    std::shared_ptr<const concept_t> m_self;
};
