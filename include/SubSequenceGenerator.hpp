#ifndef SUBSEQUENCE_GENERATOR_HPP
#define SUBSEQUENCE_GENERATOR_HPP

#include "Generator.hpp"
#include "Sequence.hpp"

#include <stdexcept>
#include <cstddef>

template<typename T>
class SubsequenceGenerator : public Generator<T> {
private:
    Sequence<T>* source_;
    size_t start_index_;

public:
    SubsequenceGenerator(const Sequence<T>& source, size_t start_index) : source_(source.Clone()), start_index_(start_index) {}
    SubsequenceGenerator(const SubsequenceGenerator<T>& other) : source_(other.source_->Clone()), start_index_(other.start_index_) {}
    SubsequenceGenerator<T>& operator=(const SubsequenceGenerator<T>& other) {
        if (this == &other) {
            return *this;
        }

        Sequence<T>* new_source = other.source_->Clone();

        delete source_;

        source_ = new_source;
        start_index_ = other.start_index_;

        return *this;
    }

    ~SubsequenceGenerator() override {
        delete source_;
    }
    
    T GetNext(const Sequence<T>& previous) override {
        size_t offset = previous.GetLength();
        return source_->Get(start_index_ + offset);
    }

    Generator<T>* Clone() const override {
        return new SubsequenceGenerator<T>(*this);
    }
};

#endif /* SUBSEQUENCE_GENERATOR_HPP */
