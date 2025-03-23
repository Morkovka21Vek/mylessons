#pragma once
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

        int getValue() const;
        
    private:
        int _num;
};

bool operator>(int, const Int&);
bool operator<(int, const Int&);
//puplic:
//    void set_zero()
//        { num = 0; }
//    void set_num(int inp)
//        { num = inp; }
//    //void print_num()
//    //    { std::cout << ""}
//    void sum_nums()
//        {}
