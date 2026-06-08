#ifndef ARITHMETIC_PROGRESSION_GENERATOR_HPP
#define ARITHMETIC_PROGRESSION_GENERATOR_HPP

#include "Sequence.hpp"
#include "Generator.hpp"
#include <stdexcept>

class ArithmeticProgressionGenerator : public Generator<int> {
private:
    int step_;

public:
    explicit ArithmeticProgressionGenerator(int step) : step_(step) {}
    
    int GetNext(const Sequence<int>& previous) override {
        size_t length = previous.GetLength();

        if (!length)
            throw std::logic_error("Arithmetic progression generator needs at least one initial value");
        
        return previous.Get(length - 1) + step_;
    }

    Generator<int>* Clone() const override {
        return new ArithmeticProgressionGenerator(*this);
    }

};

#endif /* ARITHMETIC_PROGRESSION_GENERATOR_HPP */
