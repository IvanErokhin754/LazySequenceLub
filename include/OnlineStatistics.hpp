#ifndef ONLINE_STATISTICS_HPP
#define ONLINE_STATISTICS_HPP

#include <stdexcept>
#include <cstddef>

template<typename T>
class OnlineStatistics {
private:
    size_t count_;
    T minimum_;
    T maximum_;
    long double sum_;
    bool has_values_;
    //T mean_; медиана

public:
    OnlineStatistics() : count_(0), minimum_(T()), maximum_(T()), sum_(0), has_values_(false) {}

    void Add(const T& value) {
        if (!has_values_) {
            minimum_ = value;
            maximum_ = value;
            sum_ = value;
            has_values_ = true;
            count_ = 1;
            return;
        }

        if (value < minimum_)
            minimum_ = value;
        if (value > maximum_)
            maximum_ = value;
        
        sum_ += value;
        count_++;

    }

    size_t GetCount() const {
        return count_;
    }

    long double GetSum() const {
        return sum_;
    }

    long double GetMean() const {
        if (!has_values_)
            throw std::logic_error("Statistics is empty");
        
        return sum_ / count_;
    }

    T GetMin() const {
        if (!has_values_)
            throw std::logic_error("Statistics is empty");
        
        return minimum_;
    }

    T GetMax() const {
        if (!has_values_)
            throw std::logic_error("Statistics is empty");

        return maximum_;
    }

    bool IsEmpty() const {
        return !has_values_;
    }

    void Reset() {
        count_ = 0;
        minimum_ = T();
        maximum_ = T();
        sum_ = 0;
        has_values_ = false;
    }

};

#endif /* ONLINE_STATISTICS_HPP */
