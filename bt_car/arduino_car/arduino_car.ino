#include <Servo.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#include "devices.hpp"

#define FIRST_START 1

#define MOT_PIN1  6
#define MOT_PIN2  3 
#define SERVO_PIN 5
#define RX_PIN    2
#define TX_PIN    4
#define BAUDRATE_PIN 7
#define LOGS_PIN     8
#define REVERSE_PIN  9
#define SERVO_PIN    10
#define VOLTAGE_PIN 0
#define VREF 5.1      // точное напряжение на пине 5V
#define DIV_R1 10000  // точное значение резистора на VCC
#define DIV_R2 4700   // точное значение резистора на GND

motor mot(MOT_PIN1, MOT_PIN2);
Servo servo;
settings sett(BAUDRATE_PIN, LOGS_PIN, REVERSE_PIN, SERVO_PIN);
SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup() {
    sett.init();
    sett.updateSettings();
    mot.init(sett.getReverse());
    Serial.begin(115200);
    mySerial.begin(sett.getBaudrate()?9600:115200);

    if (sett.getLogs()) {
        float voltage = (float)analogRead(VOLTAGE_PIN) * VREF * ((DIV_R1 + DIV_R2) / DIV_R2) / 1024;
        Serial.println("Bt_cat initialized!\nSettins: "+sett.getStr()+"\nVoltage: "+voltage);
    }
#ifdef FIRST_START
    if (sett.getLogs())
        Serial.println("Установка границ servo и изменение их EEPROM");
    sett.setBorder(0, 180);
    EEPROM.put(0, 0);
    EEPROM.put(2, 180);
#endif
    servo.attach(SERVO_PIN);
}

void loop() {
    if (mySerial.available() > 0) {
        int numberType;
        String textBody;
        int input_len = sscanf((mySerial.readStringUntil(';')+';').c_str(), "&%d)%[^;]", &numberType, &textBody);
        Serial.println("strLen: "+input_len);
        
        switch(numberType) {
            case 0:
                if (input_len < 2) {
                    int speed, rotate;
                    if (sscanf(textBody.c_str(), "%d,%d", &speed, &rotate) < 2)
                        mySerial.print("&3)400;");
                    else {
                        mot.write(speed-255);

                        int lborder, rborder;
                        sett.getBorder(lborder, rborder);
                        servo.write(map(rotate, 0, 99, lborder, rborder));
                    }
                } break;
            case 1:
                mySerial.print("&1)"+sett.getStr()+';');
                break;
            case 2:
                if (sett.getServo()) {
                    if (input_len < 2) {
                        int val;
                        sscanf(textBody.c_str(), "%d", &val);
                        servo.write(val);
                    }
                } break;
            case 3:
                if (sett.getServo()) {
                    if (input_len < 2) {
                        int lborder, rborder;
                        if (sscanf(textBody.c_str(), "%d, %d", &lborder, &rborder) < 2)
                            mySerial.print("&3)400;");
                        else {
                            sett.setBorder(lborder, rborder);
                            mySerial.print("&3)200;");
                        }
                    } else
                        mySerial.print("&3)400;");
                } else
                    mySerial.print("&3)503;");
                break;
            case 4:
                float voltage = (float)analogRead(VOLTAGE_PIN) * VREF * ((DIV_R1 + DIV_R2) / DIV_R2) / 1024;
                mySerial.print("&4)"+String(voltage/7.4*100)+','+String(voltage)+';');
                break;
        }
    }
}
