//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOWHEEL_H
#define GPIOCPP_GPIOWHEEL_H

#include "types.h"
#include "System.h"
namespace robopi{


    class MotorLn298
{
public:
    MotorLn298(GpioId forward, GpioId backward, GpioId enable, System* system);
    /**
     * Pass set point
     * @param pwm duty cycle -1.0 to 1.0
     */
    void set(double dutyCycle);

    void stop();

protected:
    /**
     * Spin forward
     * @param duty cycle 0.0 -> 1.0
     */
    void forward(double dutyCycle);

    /**
     * Spin backward
     * @param duty cycle 0.0 -> 1.0
     */
    void backward(double dutyCycle);

    /**
     * Convert duty cycle to appropriate range.
     * @param duty cycle 0.0 -> 1.0
     * @return pwm duty in cycle in 0 [0%] -> 255 [100%]
     */
    char convert(double dutyCycle);

    GpioId _forward,_backward,_enable;
    System* _system;
};

}
#endif //GPIOCPP_GPIOWHEEL_H
