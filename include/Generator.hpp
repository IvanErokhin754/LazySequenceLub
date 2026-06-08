#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "Sequence.hpp"

template<typename T>
class Generator {
public:
    virtual T GetNext(const Sequence<T>& previous) = 0;
    virtual Generator<T>* Clone() const = 0;

    virtual ~Generator() = default;
};

#endif /* GENERATOR_HPP */
