//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOWHEEL_H
#define GPIOCPP_GPIOWHEEL_H
#include <inttypes.h>
using GpioId = unsigned int;
class GpioWheel
{
public:
    GpioWheel(GpioId forward,GpioId backward, GpioId enable);
    void forward(float torquePerc);
    void backward(float torquePerc);
    void stop();
    ~GpioWheel();
protected:
    uint8_t torqueToDutyCycle(float torquePerc);
    static unsigned int _nInstances;
    GpioId _forward,_backward,_enable;
};
#endif //GPIOCPP_GPIOWHEEL_H
