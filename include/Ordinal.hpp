#ifndef ORDINAL_HPP
#define ORDINAL_HPP

#include <cstddef>

class Ordinal {
private:
    size_t omega_part_;
    size_t finite_part_;

public:
    Ordinal() : omega_part_(0), finite_part_(0) {}
    Ordinal(size_t finite_part) : omega_part_(0), finite_part_(finite_part) {}
    Ordinal(size_t omega_part, size_t finite_part) : omega_part_(omega_part), finite_part_(finite_part) {}
    
    size_t GetOmegaPart() const {
        return omega_part_;
    }

    size_t GetFinitePart() const {
        return finite_part_;
    }

    bool IsInfinite() const {
        return omega_part_ > 0;
    }

    bool IsFinite() const {
        return omega_part_ == 0;
    }
    bool IsZero() const {
        return omega_part_ == 0 && finite_part_ == 0;
    }

    bool operator==(const Ordinal& other) const {
        return omega_part_ == other.omega_part_ && finite_part_ == other.finite_part_;
    }

    bool operator!=(const Ordinal& other) const {
        return !(*this == other);
    }

    bool operator<(const Ordinal& other) const {
        if (omega_part_ < other.omega_part_) 
            return true;
        
        if (omega_part_ > other.omega_part_)
            return false;
        
        if (finite_part_ < other.finite_part_)
            return true;
        
        if (finite_part_ >= other.finite_part_)
            return false;
    }

    bool operator>(const Ordinal& other) const {
        return other < *this;
    }

    bool operator<=(const Ordinal& other) const {
        return !(*this > other);
    }

    bool operator>=(const Ordinal& other) const {
        return !(*this < other);
    }

    Ordinal operator+(size_t value) const {
        return Ordinal(omega_part_, finite_part_ + value);
    }

};

#endif /* ORDINAL_HPP */
