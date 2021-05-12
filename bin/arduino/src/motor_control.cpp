#include "robopi_drivers/robopi_drivers.h"
#include <Arduino.h>

using namespace robopi;


GpioId in1,in2,enA;
GpioId in3,in4,enB;
GpioId encRight,encLeft;

float kp,ki,kd;
MotorVelocityControl controlLeft, controlRight;
float setPoint;
int dT;
void setup()
{
    auto motorRight = std::make_shared<MotorLn298>(in1,in2,enA);
    auto encoderRight = std::make_shared<Encoder>(encRight);
    //auto filterRight = std::make_shared<SlidingAverageFilter>(filterSize);
    auto filterRight = std::make_shared<LuenbergerObserver>(5.0,7.5);

    controlRight = std::make_shared<MotorVelocityControl>(motorRight,encoderRight,filterRight,kp,ki,kd);

    auto motorLeft = std::make_shared<MotorLn298>(in4,in3,enB);
    auto encoderLeft = std::make_shared<Encoder>(encLeft);
    //auto filterLeft = std::make_shared<SlidingAverageFilter>(filterSize);
    auto filterLeft = std::make_shared<LuenbergerObserver>(5.0,7.5);

    controlLeft = std::make_shared<MotorVelocityControl>(motorLeft,encoderLeft,filterLeft,kp,ki,kd);

}

void loop()
{
    controlRight->set(setPoint);
    controlLeft->set(setPoint);
    controlLeft->update(dT);
    controlRight->update(dT);
    gpios->delay(dT);

}