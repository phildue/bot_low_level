//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOWHEEL_H
#define GPIOCPP_GPIOWHEEL_H
#include <memory>
#include "PiGpio.h"
namespace robopi{

class MotorLn298
{
public:
    MotorLn298(GpioId forward, GpioId backward, GpioId enable, std::shared_ptr<PiGpio> piGpio = robopi::PiGpio::instance());
    void set(float effort);
    void stop();
protected:
    void initialize();
    void forward(float effortPerc);
    void backward(float effortPerc);
    int effort2pwm(float effortPerc);
    GpioId _forward,_backward,_enable;
    std::shared_ptr<PiGpio> _piGpio;
};

}
#endif //GPIOCPP_GPIOWHEEL_H
