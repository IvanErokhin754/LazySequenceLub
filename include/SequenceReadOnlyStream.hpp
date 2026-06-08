#ifndef SEQUENCE_READ_ONLY_STREAM_HPP
#define SEQUENCE_READ_ONLY_STREAM_HPP

#include "ReadOnlyStream.hpp"
#include "Sequence.hpp"
#include <stdexcept>

template<typename T>
class SequenceReadOnlyStream : public ReadOnlyStream<T> {
private:
    const Sequence<T>* sequence_;
    size_t position_;
    bool is_open_;

public:
    explicit SequenceReadOnlyStream(const Sequence<T>* sequence) : sequence_(sequence), position_(0), is_open_(false) {
        if (sequence_ == nullptr) 
            throw std::invalid_argument("Sequence is null");
    }

    void Open() override {
        is_open_ = true;
    }
    
    void Close() override {
        is_open_ = false;
    }


    bool IsEndOfStream() const override {
        return position_ >= sequence_->GetLength();
    }

    T Read() override {
        if (!is_open_)
            throw std::logic_error("Stream is not open");
        if (IsEndOfStream())
            throw std::out_of_range("End of stream");
            
        T value = sequence_->Get(position_);
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
        if (index > sequence_->GetLength())
            throw std::out_of_range("Index out of range");
        
        position_ = index;
        return position_;
    }

    bool IsCanGoBack() const override {
        return true;
    }
};

#endif /* SEQUENCE_READ_ONLY_STREAM_HPP */
