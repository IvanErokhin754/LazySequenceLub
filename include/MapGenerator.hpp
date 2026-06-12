#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "Generator.hpp"
#include "Sequence.hpp"

#include <stdexcept>
#include <cstddef>

template <typename T>
class MapGenerator : public Generator<T> {
private:
    Sequence<T>* source_;
    T (*func_)(const T&);

public:
    MapGenerator(const Sequence<T>& source, T (*func)(const T&)) : source_(source.Clone()), func_(func) {
        if (func_ == nullptr) {
            delete source_;
            throw std::invalid_argument("Map function is null");
        }
    } 

    MapGenerator(const MapGenerator<T>& other) : source_(other.source_->Clone()), func_(other.func_) {}

    MapGenerator<T>& operator=(const MapGenerator<T>& other) {
        if (this == &other)
            return *this;
        
        Sequence<T>* new_source = other.source_->Clone();

        delete source_;

        source_ = new_source;
        func_ = other.func_;

        return *this;
    }

    ~MapGenerator() override {
        delete source_;
    }

    T GetNext(const Sequence<T>& previous) override {
        size_t index = previous.GetLength();
        return func_(source_->Get(index));
    } 

    Generator<T>* Clone() const override {
        return new MapGenerator<T>(*this);
    }
};

#endif /* MAP_GENERATOR_HPP */
