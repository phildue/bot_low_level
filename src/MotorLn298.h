//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOWHEEL_H
#define GPIOCPP_GPIOWHEEL_H
#include <memory>
#include "Gpio.h"
namespace robopi{


    class MotorLn298
{
public:
    MotorLn298(GpioId forward, GpioId backward, GpioId enable, std::shared_ptr<Gpio> gpios = robopi::Gpio::instance());
    /**
     * Pass set point
     * @param pwm duty cycle -1.0 to 1.0
     */
    void set(float dutyCycle);

    void stop();

protected:
    /**
     * Initialize gpios
     */
    void initialize();

    /**
     * Spin forward
     * @param duty cycle 0.0 -> 1.0
     */
    void forward(float dutyCycle);

    /**
     * Spin backward
     * @param duty cycle 0.0 -> 1.0
     */
    void backward(float dutyCycle);

    /**
     * Convert duty cycle to appropriate range.
     * @param duty cycle 0.0 -> 1.0
     * @return pwm duty in cycle in 0 [0%] -> 255 [100%]
     */
    int convert(float dutyCycle);

    GpioId _forward,_backward,_enable;
    std::shared_ptr<Gpio> _gpios;
};

}
#endif //GPIOCPP_GPIOWHEEL_H
