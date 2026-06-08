#ifndef LAZY_SEQUENCE_READ_ONLY_STREAM_HPP
#define LAZY_SEQUENCE_READ_ONLY_STREAM_HPP

#include "ReadOnlyStream.hpp"
#include "LazySequence.hpp"
#include <stdexcept>
#include <cstddef>

template<typename T>
class LazySequenceReadOnlyStream : public ReadOnlyStream<T>{
private:
    const LazySequence<T>* lazy_sequence_;
    size_t position_;
    bool is_open_;

public:
    explicit LazySequenceReadOnlyStream(const LazySequence<T>* lazy_sequence) : lazy_sequence_(lazy_sequence), position_(0), is_open_(false) {
        if (lazy_sequence_ == nullptr)
            throw std::invalid_argument("LazySequence is null");
    }

    void Open() override {
        is_open_ = true;
    }

    void Close() override {
        is_open_ = false;
    }

    bool IsEndOfStream() const override {
        if (lazy_sequence_->IsInfinite())
            return false;
    
       return position_ >= lazy_sequence_->GetLength();
    }

    T Read() override {
        if (!is_open_)
            throw std::logic_error("Stream is not open");
        if (IsEndOfStream())
            throw std::out_of_range("End of stream");
        
        T value = lazy_sequence_->Get(position_);
        position_++;

        return value;
    }

    size_t GetPosition() const override {
        return position_;
    }

    bool IsCanSeek() const override {
        return true;
    }

    size_t Seek(size_t index) override {
        if (!lazy_sequence_->IsInfinite() && index > lazy_sequence_->GetLength())
            throw std::out_of_range("Index out of range");
        
        position_ = index;
        return position_;
    }

    bool IsCanGoBack() const override {
        return true;
    }

};

#endif /* LAZY_SEQUENCE_READ_ONLY_STREAM_HPP */
