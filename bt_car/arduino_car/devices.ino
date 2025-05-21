#include <EEPROM.h>
#include "devices.hpp"

motor::motor(unsigned int pin1, unsigned int pin2): _pin1(pin1), _pin2(pin2)
{}

void motor::init(bool reverse) {
    pinMode(this->_pin1, OUTPUT);
    pinMode(this->_pin2, OUTPUT);

    if(reverse) {
        int temp = this->_pin1;
        this->_pin1 = this->_pin2;
        this->_pin2 = temp;
    }
}

void motor::write(int val) {
    this->_val = val;
    if (this->_val > 0)
    {
      analogWrite(this->_pin1, this->_val);
      analogWrite(this->_pin2, LOW);
    }
    else if (this->_val < 0)
    {
      analogWrite(this->_pin1, LOW);
      analogWrite(this->_pin2, this->_val);
    }
    else
    {
      analogWrite(this->_pin1, LOW);
      analogWrite(this->_pin2, LOW);
    }
}

int motor::getValue() const {
    return this->_val;
}


settings::settings(int baudrate, int logs, int reverse, int servo): pin_baudrate(baudrate), pin_logs(logs), pin_reverse(reverse), pin_servo(servo)
{}

void settings::init() {
    int lborder, rborder;
    EEPROM.get(0, lborder);
    EEPROM.get(2, rborder);
    this->_lborder = lborder;
    this->_rborder = rborder;

    pinMode(pin_baudrate, INPUT_PULLUP);
    pinMode(pin_logs,     INPUT_PULLUP);
    pinMode(pin_reverse,  INPUT_PULLUP);
    pinMode(pin_servo,    INPUT_PULLUP);
}

void settings::updateSettings() {
    EEPROM.get(0, this->_lborder);
    EEPROM.get(2, this->_rborder);

    _baudrate = !digitalRead(pin_baudrate);
    _logs =     !digitalRead(pin_logs);
    _reverse =  !digitalRead(pin_reverse);
    _servo =    !digitalRead(pin_servo);
}

String settings::getStr() const {
    return String(_baudrate)+','+String(_logs)+','+String(_reverse)+','+String(_servo);
}

bool settings::getBaudrate() const {
    return _baudrate;
}

bool settings::getLogs() const {
    return _logs;
}

bool settings::getReverse() const {
    return _reverse;
}

bool settings::getServo() const {
    return _servo;
}

void settings::setBorder(int lborder, int rborder) {
    EEPROM.put(0, lborder);
    EEPROM.put(2, rborder);
    this->_lborder = lborder;
    this->_rborder = rborder;
}

void settings::getBorder(int& lborder, int& rborder) {
    lborder = this->_lborder;
    rborder = this->_rborder;
}
