//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOWHEEL_H
#define GPIOCPP_GPIOWHEEL_H
#include <inttypes.h>
namespace pi_ln298n{

using GpioId = unsigned int;
class GpioMotor
{
public:
    GpioMotor(GpioId forward, GpioId backward, GpioId enable);
    void set(float torquePerc);
    float torque() {return _torque;}
    void stop();
    ~GpioMotor();
protected:
    float _torque;
    void forward(float torquePerc);
    void backward(float torquePerc);
    uint8_t torqueToDutyCycle(float torquePerc);
    static unsigned int _nInstances;
    GpioId _forward,_backward,_enable;
};

}
#endif //GPIOCPP_GPIOWHEEL_H
