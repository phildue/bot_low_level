//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOWHEEL_H
#define GPIOCPP_GPIOWHEEL_H
#include <memory>
#include "PiGpio.h"
namespace robopi{

    constexpr float MAX_VEL_DF_DC = 16.755;//rad_s

    class MotorLn298
{
public:
    MotorLn298(GpioId forward, GpioId backward, GpioId enable, std::shared_ptr<PiGpio> piGpio = robopi::PiGpio::instance(),float maxVel = MAX_VEL_DF_DC);
    /**
     * Set angular velocity
     * @param velocity in rad/s
     */
    void set(float velocity);

    void stop();

    const float& maxVel() const {return _maxVel;}
protected:
    /**
     * Initialize gpios
     */
    void initialize();

    /**
     * Spin forward
     * @param velocity in rad/s
     */
    void forward(float velocity);

    /**
     * Spin backward
     * @param velocity in rad/s
     */
    void backward(float velocity);

    /**
     * Convert angular velocity to pwm duty cycle
     * @param velocity in rad/s
     * @return pwm duty in cycle in 0 [0%] -> 255 [100%]
     */
    int vel2pwm(float velocity);

    GpioId _forward,_backward,_enable;
    std::shared_ptr<PiGpio> _piGpio;
    const float _maxVel;
};

}
#endif //GPIOCPP_GPIOWHEEL_H
