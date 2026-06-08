#ifndef FACTORIAL_GENERATOR_HPP
#define FACTORIAL_GENERATOR_HPP

#include "Sequence.hpp"
#include "Generator.hpp"
#include <stdexcept>

class FactorialGenerator : public Generator<unsigned long long> {
public:
    unsigned long long GetNext(const Sequence<unsigned long long>& previous) override {
        size_t length = previous.GetLength();
        if (!length)
            throw std::logic_error("Factorial progression generator needs at least one initial value");
        
        unsigned long long next_number = static_cast<unsigned long long>(length + 1);
        return previous.Get(length - 1) * next_number;
    }   

    Generator<unsigned long long>* Clone() const override {
        return new FactorialGenerator(*this);
    }
};
#endif /* FACTORIAL_GENERATOR_HPP */
