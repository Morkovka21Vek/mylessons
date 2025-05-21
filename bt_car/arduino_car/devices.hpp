#pragma once

class motor {
    public:
        motor(unsigned int pin1, unsigned int pin2);
        void write(int);
        int getValue() const;
        void init(bool reverse);
    private:
        int _pin1, _pin2;
        int _val;
};

class settings {
    public:
        settings(int baudrate, int logs, int reverse, int servo);
        void updateSettings();
        String getStr() const;
        void init();
        bool getBaudrate() const;
        bool getLogs() const;
        bool getReverse() const;
        bool getServo() const;
        void getBorder(int& lborder, int& rborder);
        void setBorder(int lborder, int rborder);
    private:
        bool _baudrate, _logs, _reverse, _servo;
        int pin_baudrate, pin_logs, pin_reverse, pin_servo;
        int _lborder, _rborder;
};
