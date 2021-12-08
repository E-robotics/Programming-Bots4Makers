#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>


double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
void motorFRONT(double motor, double speed);
double ENA;
double IN1;
double OFF;
double IN2;
double ON;
double ENB;
double IN3;
double IN4;
void motorREVERSE(double motor, double speed);
void CONFIG_CONECTORS();
double ECHO;
double TRIG;
double LED_R;
double LED_G;
double LED_B;
double LINE_LEFT;
double LINE_MIDDLE;
double LINE_RIGHT;
void motorSTOP(double motor);
void WAITforSTART();
double DISTANCE;
float getDistance(int trig,int echo){
    pinMode(trig,OUTPUT);
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    pinMode(echo, INPUT);
    return pulseIn(echo,HIGH,30000)/58.0;
}
void CONFIG_CONSTANTS();
void LED(double RED, double GREEN, double BLUE);
double ISlineLEFT;
double ISlineMIDDLE;
double ISlineRIGHT;


void motorFRONT(double motor, double speed)
{
    if(((motor)==(2))){
        analogWrite(ENA,speed);
        digitalWrite(IN1,OFF);
        digitalWrite(IN2,ON);
    }else{
        if(((motor)==(1))){
            analogWrite(ENB,speed);
            digitalWrite(IN3,OFF);
            digitalWrite(IN4,ON);
        }
    }
    
}

void motorREVERSE(double motor, double speed)
{
    if(((motor)==(2))){
        analogWrite(ENA,speed);
        digitalWrite(IN1,ON);
        digitalWrite(IN2,OFF);
    }else{
        if(((motor)==(1))){
            analogWrite(ENB,speed);
            digitalWrite(IN3,ON);
            digitalWrite(IN4,OFF);
        }
    }
    
}

void CONFIG_CONECTORS()
{
    ENA = 6;
    
    IN1 = A0;
    
    IN2 = A1;
    
    ENB = 5;
    
    IN3 = A2;
    
    IN4 = A3;
    
    ECHO = 7;
    
    TRIG = 8;
    
    LED_R = 11;
    
    LED_G = 10;
    
    LED_B = 9;
    
    LINE_LEFT = A4;
    
    LINE_MIDDLE = A5;
    
    LINE_RIGHT = A6;
    
}

void motorSTOP(double motor)
{
    if(((motor)==(2))){
        digitalWrite(IN1,ON);
        digitalWrite(IN2,ON);
    }else{
        if(((motor)==(1))){
            digitalWrite(IN3,ON);
            digitalWrite(IN4,ON);
        }
    }
    
}

void WAITforSTART()
{
    DISTANCE = getDistance(TRIG,ECHO);
    
    DISTANCE = getDistance(TRIG,ECHO);
    
    while(!(((DISTANCE) > (0)) && ((DISTANCE) < (5))))
    {
        _loop();
        DISTANCE = getDistance(TRIG,ECHO);
        _delay(0.1);
        Serial.println(DISTANCE);
    }
    
}

void CONFIG_CONSTANTS()
{
    OFF = 0;
    
    ON = 1;
    
}

void LED(double RED, double GREEN, double BLUE)
{
    digitalWrite(LED_R,RED);
    
    digitalWrite(LED_G,GREEN);
    
    digitalWrite(LED_B,BLUE);
    
}


void setup(){
    Serial.begin(115200);
    CONFIG_CONECTORS();
    CONFIG_CONSTANTS();
    WAITforSTART();
    
    pinMode(ENA,OUTPUT);
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(ENB,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    pinMode(LED_R,OUTPUT);
    pinMode(LED_G,OUTPUT);
    pinMode(LED_B,OUTPUT);
    pinMode(LINE_LEFT,INPUT);
    pinMode(LINE_MIDDLE,INPUT);
    pinMode(LINE_RIGHT,INPUT);
}

void loop(){
    
    ISlineLEFT = 0;
    ISlineMIDDLE = 0;
    ISlineRIGHT = 0;
    _delay(0.1);
    LED(255,0,0);
    _delay(1);
    motorFRONT(1,130);
    motorFRONT(2,130);
    _delay(1);
    motorSTOP(1);
    motorSTOP(2);
    _delay(1);
    LED(0,255,0);
    _delay(0.1);
    motorREVERSE(1,130);
    motorREVERSE(2,130);
    _delay(1);
    motorSTOP(1);
    motorSTOP(2);
    _delay(2);
    LED(0,0,255);
    _delay(0.2);
    motorFRONT(1,130);
    motorFRONT(2,130);
    _delay(1);
    motorSTOP(1);
    motorSTOP(2);
    LED(0,0,0);
    while(!(((((ISlineLEFT)==(1))) && (((ISlineMIDDLE)==(1)))) && (((ISlineRIGHT)==(1)))))
    {
        _loop();
        if(((digitalRead(LINE_LEFT))==(1))){
            ISlineLEFT = 1;
            LED(255,0,0);
            _delay(1);
            LED(0,0,0);
        }else{
        }
        if(((digitalRead(LINE_MIDDLE))==(1))){
            ISlineMIDDLE = 1;
            LED(0,255,0);
            _delay(1);
            LED(0,0,0);
        }else{
        }
        if(((digitalRead(LINE_RIGHT))==(1))){
            ISlineRIGHT = 1;
            LED(0,0,255);
            _delay(1);
            LED(0,0,0);
        }
    }
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}
