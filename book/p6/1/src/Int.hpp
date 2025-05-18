#pragma once

#include <ostream>

class Int {
    public:
        Int(int val);
        Int();
        bool operator==(int) const;
        bool operator==(const Int&) const;

        bool operator!=(const Int&) const;

        Int& operator=(int val);

        bool operator>(const Int&) const;
        bool operator<(const Int&) const;

        bool operator>=(const Int&) const;
        bool operator<=(const Int&) const;

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
