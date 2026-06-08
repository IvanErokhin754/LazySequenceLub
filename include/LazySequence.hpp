#ifndef LAZY_SEQUENCE_HPP
#define LAZY_SEQUENCE_HPP

#include "MutableArraySequence.hpp"
#include "Generator.hpp"
#include <stdexcept>

template<typename T>
class LazySequence : public Sequence<T> {
private:
    mutable MutableArraySequence<T> cache_;
    Generator<T>* generator_;

    bool is_infinite_;
    size_t length_;

    void MaterializeUpTo(size_t index) const {
        if (!is_infinite_ && index >= length_) 
            throw std::out_of_range("Index out of range");
        
        while (cache_.GetLength() <= index) {
            if (generator_ == nullptr)
                throw std::out_of_range("No generator available");
            
            T next_value = generator_->GetNext(cache_);
            cache_.Append(next_value);
        }
    }

public:
    LazySequence() : cache_(), generator_(nullptr), is_infinite_(false), length_(0) {}
    LazySequence(T* items, size_t count) : cache_(items, static_cast<int>(count)), generator_(nullptr), is_infinite_(false), length_(count) {} 
    LazySequence(T* initial_items, size_t initial_count, Generator<T>* generator) : cache_(initial_items, static_cast<int>(initial_count)), 
                                                                                    generator_(generator), is_infinite_(true), length_(0) {
                                                                                        if (generator_ == nullptr)
                                                                                            throw std::invalid_argument("Generator is null");
                                                                                    }
    LazySequence(const LazySequence<T>& other) : cache_(other.cache_), generator_(other.generator_ ? other.generator_->Clone() : nullptr), is_infinite_(other.is_infinite_),
                                                 length_(other.length_) {}
    
    ~LazySequence() override {
        delete generator_;
    }

    LazySequence<T>& operator=(const LazySequence<T>& other) {
        if (this == &other) 
            return *this;

        Generator<T>* new_generator = other.generator_ ? other.generator_->Clone() : nullptr;

        delete generator_;

        cache_ = other.cache_;
        generator_ = new_generator;
        is_infinite_ = other.is_infinite_;
        length_ = other.length_;

        return *this;
    }

    bool IsInfinite() const {
        return is_infinite_;
    }

    const T& Get(size_t index) const override {
        MaterializeUpTo(index);
        return cache_.Get(index);
    }

    const T& GetFirst() const override {
        return Get(0);
    }

    const T& GetLast() const override {
        if (is_infinite_)
            throw std::logic_error("Infinite sequence has no last element");
        
        if (length_ == 0)
            throw std::out_of_range("Sequence is empty");

        return Get(length_ - 1);
    }

    size_t GetLength() const override {
        if (is_infinite_)
            throw std::logic_error("Infinite sequence has no finite length");
        
        return length_;
    }

    size_t GetMaterializedCount() const {
        return cache_.GetLength();
    }

    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override {
        if (start_index > end_index) {
            throw std::out_of_range("Index out of range");
        }
        if (!is_infinite_ && end_index >= length_) {
            throw std::out_of_range("Index out of range");
        }
        size_t count = end_index - start_index + 1;
        T* items = new T[count];

        try {
            for (size_t i = 0; i < count; ++i) {
                items[i] = Get(start_index + i);
            }

            Sequence<T>* result = new LazySequence<T>(items, count);
            delete[] items;
            return result;
        } catch (...) {
            delete[] items;
            throw;
        }
    }

    Sequence<T>* Concat(const Sequence<T>& other) const override {
        if (is_infinite_) {
            throw std::logic_error("Cannot concatenate after infinite sequence");
        }
        size_t first_length = GetLength();
        size_t second_length = other.GetLength();
        size_t total_length = first_length + second_length;
        T* items = new T[total_length];

        try {
            for (size_t i = 0; i < first_length; ++i) {
                items[i] = Get(i);
            }
            for (size_t i = 0; i < second_length; ++i) {
                items[first_length + i] = other.Get(i);
            }
            Sequence<T>* result = new LazySequence<T>(items, total_length);
            delete[] items;
            return result;
        } catch (...) {
            delete[] items;
            throw;
        }
    }

    Sequence<T>* Clone() const override {
        return new LazySequence<T>(*this);
    }
};

#endif /* LAZY_SEQUENCE_HPP */
