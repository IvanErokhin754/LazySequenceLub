#ifndef FIBONACCI_GENERATOR_HPP
#define FIBONACCI_GENERATOR_HPP

#include "Generator.hpp"
#include <stdexcept>

class FibonacciGenerator : public Generator<int> {
public:
    int GetNext(const Sequence<int>& previous) override {
        size_t length = previous.GetLength();

        if (length < 2)
            throw std::logic_error("Fibonacci generator needs at least two initial values");
        
        return previous.Get(length - 1) + previous.Get(length - 2);
    }

    Generator<int>* Clone() const override {
        return new FibonacciGenerator(*this);
    }
};


#endif /* FIBONACCI_GENERATOR_HPP */
