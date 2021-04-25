//
// Created by phil on 21.03.20.
//

#include "MotorLn298.h"

#include <stdexcept>
#include <iostream>
namespace robopi {


    MotorLn298::MotorLn298(GpioId forward, GpioId backward, GpioId enable, std::shared_ptr<Gpio> gpios) :
            _forward(forward),
            _backward(backward),
            _enable(enable),
            _gpios(gpios)
            {


        initialize();
                _gpios->setMode(_forward, PI_OUTPUT);
                _gpios->setMode(_backward, PI_OUTPUT);
                _gpios->setMode(_enable, PI_OUTPUT);
                _gpios->setPWMfrequency(_enable,1000);
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
        _gpios->pWM(_enable, pwm);
        _gpios->write(_forward, PI_ON);
        _gpios->write(_backward, PI_OFF);
    }

    void MotorLn298::backward(float dutyCycle) {
        auto pwm = convert(dutyCycle);
        _gpios->pWM(_enable, pwm);
        _gpios->write(_forward, PI_OFF);
        _gpios->write(_backward, PI_ON);
    }

    void MotorLn298::stop() {
        initialize();
        _gpios->write(_forward, PI_OFF);
        _gpios->write(_backward, PI_OFF);
    }

    int MotorLn298::convert(float dutyCycle) {
        float dutyCycleClipped = dutyCycle > 1.0 ? 1.0 : dutyCycle;
        dutyCycle = dutyCycleClipped < 0.0 ? 0.0 : dutyCycleClipped;

        return static_cast<int>(dutyCycle * 255.0f);
    }

    void MotorLn298::initialize() {
        if (_gpios->initialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }
}