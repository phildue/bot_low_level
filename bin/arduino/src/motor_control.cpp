#include <Arduino.h>
#include "robopi_drivers/robopi_drivers.h"

using namespace robopi;

/// Pin Layout
constexpr int in1 = 2,in2 = 3,enA = 9;
constexpr int in3 = 4,in4 = 5,enB = 10;
constexpr int encRight = 6,encLeft = 7;

/// Control Parameters
constexpr float kp = 0.03f,ki = 0.0f, kd = 0.0f;
constexpr float f = 10;//[hz]
constexpr float dT = 1.0f/f;//[s]

constexpr float setPoint = 20;//[rad/s]

constexpr float S_TO_MS = 1000.0f;


class SystemArduino : public System
{
public:
    void sleep(int msec) override{ delay(msec);};

    void setMode(int pin,int sig) override{
        switch(sig)
        {
            case PI_OUTPUT:
                pinMode(pin,OUTPUT);
                break;
            case PI_INPUT:
                pinMode(pin,INPUT);
                break;
            default:
                Serial.println("Wrong pin setup.");
        }
    };

    void write(int pin,int sig) override{
        switch (sig)
        {
            case PI_ON:
                digitalWrite(pin,HIGH);
                break;
            case PI_OFF:
                digitalWrite(pin,LOW);
                break;
            default:
                Serial.println("Wrong pin write.");
        }
    };
    void pWM(int pin,char sig) override{

        analogWrite(pin,sig);
    };
    int read(int pin) override{
        switch (digitalRead(pin))
        {
            case HIGH:
                return PI_ON;
            case LOW:
                return PI_OFF;
            default:
                return PI_OFF;
        }
    };

    void setPWMfrequency(int pin,int freq) override{};
    void setPullUpDown(int pin,int upDown) override{
        switch (upDown)
        {
            case PI_PUD_UP:
                pinMode(pin,INPUT_PULLUP);
                break;
            default:
                Serial.println("Wrong pin setup.");
        }
    };
};

System* gpios;
Encoder* encoderLeft;
Encoder* encoderRight;
MotorLn298* motorLeft;
MotorLn298* motorRight;
VelocityEstimator* filterLeft;
VelocityEstimator* filterRight;
MotorVelocityControl* controlLeft;
MotorVelocityControl* controlRight;

void isr_encRight()
{
    encoderRight->tick();
}
void isr_encLeft()
{
    encoderLeft->tick();
}
void setup()
{
    Serial.begin(9600);

    gpios = new SystemArduino();
    motorRight = new MotorLn298(in1,in2,enA,gpios);
    encoderRight = new Encoder(encRight,gpios);

    //auto filterRight = std::make_shared<SlidingAverageFilter>(filterSize);
    filterRight = new LuenbergerObserver(5.0,7.5);

    controlRight = new MotorVelocityControl(motorRight,encoderRight,filterRight,kp,ki,kd);

    motorLeft = new MotorLn298(in4,in3,enB,gpios);
    encoderLeft = new Encoder(encLeft,gpios);

    attachInterrupt(digitalPinToInterrupt(encRight), isr_encRight, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encLeft), isr_encLeft, CHANGE);

    //auto filterLeft = std::make_shared<SlidingAverageFilter>(filterSize);
    filterLeft = new LuenbergerObserver(5.0,7.5);

    controlLeft = new MotorVelocityControl(motorLeft,encoderLeft,filterLeft,kp,ki,kd);

}

void loop()
{
    controlRight->set(setPoint);
    controlLeft->set(setPoint);

    controlRight->update(dT);
    controlLeft->update(dT);

    delay(static_cast<unsigned long>(dT*S_TO_MS));
    Serial.println("Right: ");
    Serial.println((controlRight->velocity()));
    Serial.println("Left: ");
    Serial.println((controlLeft->velocity()));

}