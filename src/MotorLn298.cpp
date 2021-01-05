//
// Created by phil on 21.03.20.
//

#include "MotorLn298.h"

#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#else
#include <pigpiostub.h>
#endif
#include <stdexcept>
#include <iostream>
namespace robopi {


    MotorLn298::MotorLn298(GpioId forward, GpioId backward, GpioId enable, std::shared_ptr<PiGpio> piGpio) :
            _forward(forward),
            _backward(backward),
            _enable(enable),
            _piGpio(piGpio)
            {


        initialize();
        gpioSetMode(_forward, PI_OUTPUT);
        gpioSetMode(_backward, PI_OUTPUT);
        gpioSetMode(_enable, PI_OUTPUT);
        gpioSetPWMfrequency(_enable,1000);
    }

    void MotorLn298::set(float dutyCycle) {
        initialize();
        if (dutyCycle > 0) {
            forward(dutyCycle);
        } else {
            backward(std::abs(dutyCycle));
        }
    }

    void MotorLn298::forward(float dutyCycle) {
        auto pwm = convert(dutyCycle);
        gpioPWM(_enable, pwm);
        gpioWrite(_forward, PI_ON);
        gpioWrite(_backward, PI_OFF);
    }

    void MotorLn298::backward(float dutyCycle) {
        auto pwm = convert(dutyCycle);
        gpioPWM(_enable, pwm);
        gpioWrite(_forward, PI_OFF);
        gpioWrite(_backward, PI_ON);
    }

    void MotorLn298::stop() {
        initialize();
        gpioWrite(_forward, PI_OFF);
        gpioWrite(_backward, PI_OFF);
    }

    int MotorLn298::convert(float dutyCycle) {
        float dutyCycleClipped = dutyCycle > 1.0 ? 1.0 : dutyCycle;
        dutyCycle = dutyCycleClipped < 0.0 ? 0.0 : dutyCycleClipped;

        return static_cast<int>(dutyCycle * 255.0f);
    }

    void MotorLn298::initialize() {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }
}