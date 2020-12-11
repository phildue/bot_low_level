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
constexpr int HIGH = 1;
constexpr int LOW = 0;
namespace pi_ln298n {


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

    void MotorLn298::set(float torquePerc) {
        initialize();
        if (torquePerc > 0) {
            forward(torquePerc);
        } else {
            backward(std::abs(torquePerc));
        }
    }

    void MotorLn298::forward(float effortPerc) {
        auto pwm = effort2pwm(effortPerc);
        gpioPWM(_enable, pwm);
        gpioWrite(_forward, HIGH);
        gpioWrite(_backward, LOW);
    }

    void MotorLn298::backward(float effortPerc) {
        auto pwm = effort2pwm(effortPerc);
        gpioPWM(_enable, pwm);
        gpioWrite(_forward, LOW);
        gpioWrite(_backward, HIGH);
    }

    void MotorLn298::stop() {
        initialize();
        gpioWrite(_forward, LOW);
        gpioWrite(_backward, LOW);
    }

    int MotorLn298::effort2pwm(float effortPerc) {

        auto torquePercClipped = effortPerc > 1.0 ? 1.0 : effortPerc;
        torquePercClipped = torquePercClipped < 0.0 ? 0.0 : torquePercClipped;

        return static_cast<int>(torquePercClipped * 255.0f);
    }

    void MotorLn298::initialize() {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }
}