#ifndef CONCAT_GENERATOR_HPP
#define CONCAT_GENERATOR_HPP

#include "Generator.hpp"
#include "Sequence.hpp"

#include <stdexcept>
#include <cstddef>

template<typename T>
class ConcatGenerator : public Generator<T> {
private:
    Sequence<T>* first_;
    Sequence<T>* second_;
    size_t first_length_;

public:
    ConcatGenerator(const Sequence<T>& first, const Sequence<T>& second, size_t first_length) : first_(first.Clone()), second_(second.Clone()), first_length_(first_length) {}
    ConcatGenerator(const ConcatGenerator<T>& other) : first_(other.first_->Clone()), second_(other.second_->Clone()), first_length_(other.first_length_) {}
    ConcatGenerator<T>& operator=(const ConcatGenerator<T>& other) {
        if (this == &other)
            return *this;
        
        Sequence<T>* new_first = other.first_->Clone();
        Sequence<T>* new_second = other.second_->Clone();

        delete first_;
        delete second_;

        first_ = new_first;
        second_ = new_second;
        first_length_ = other.first_length_;

        return *this;
    }

    ~ConcatGenerator() override {
        delete first_;
        delete second_;
    }

    T GetNext(const Sequence<T>& previous) override {
        size_t index = previous.GetLength();

        if (index < first_length_) {
            return first_->Get(index);
        }

        return second_->Get(index - first_length_);
    }

    Generator<T>* Clone() const override {
        return new ConcatGenerator<T>(*this);
    }
};

#endif /* CONCAT_GENERATOR_HPP */
