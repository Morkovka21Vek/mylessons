#pragma once

#include <ostream>

class Int {
    public:
        Int(int val);
        Int();
        std::strong_ordering operator<=>(int) const;
        std::strong_ordering operator<=>(const Int&) const = default;

        Int& operator=(int val);

        friend Int operator+(const Int&, int val);
        friend Int operator+(int val, const Int&);
        friend Int operator+(const Int&, const Int&);

        friend Int operator-(const Int&, int val);
        friend Int operator-(int val, const Int&);
        friend Int operator-(const Int&, const Int&);

        friend Int& operator+=(Int&, int val);
        friend Int& operator+=(Int&, const Int&);

        friend Int& operator-=(Int&, int val);
        friend Int& operator-=(Int&, const Int&);

        friend std::ostream& operator<<(std::ostream& os, const Int& obj);
        friend bool operator>(int, const Int&);
        friend bool operator<(int, const Int&);

        friend bool operator>=(int, const Int&);
        friend bool operator<=(int, const Int&);
        
    private:
        int _num;
};
