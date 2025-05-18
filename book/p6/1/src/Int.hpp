#pragma once

#include <ostream>

class Int {
    public:
        Int(int val);
        Int();
        std::strong_ordering operator<=>(int) const;
        std::strong_ordering operator<=>(const Int&) const = default;

        Int& operator=(int val);

        Int operator+(int val) const;
        Int operator+(const Int&) const;

        Int operator-(int val) const;
        Int operator-(const Int&) const;

        Int& operator+=(int val);
        Int& operator+=(const Int& other);

        Int& operator-=(int val);
        Int& operator-=(const Int& other);

        int getValue() const;
        
    private:
        int _num;
};

bool operator>(int, const Int&);
bool operator<(int, const Int&);

bool operator>=(int, const Int&);
bool operator<=(int, const Int&);

std::ostream& operator<<(std::ostream& os, const Int& obj);
