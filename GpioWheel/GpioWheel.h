//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOWHEEL_H
#define GPIOCPP_GPIOWHEEL_H



using GpioId = unsigned int;
class GpioWheel
{
public:
    GpioWheel(GpioId forward,GpioId backward, GpioId enable, float dutyCycle);
    void forward();
    void backward();
    void stop();
    ~GpioWheel();
protected:
    static unsigned int _nInstances;
    GpioId _forward,_backward,_enable;
};
#endif //GPIOCPP_GPIOWHEEL_H
