//
// Created by phil on 21.03.20.
//

#include "MotorLn298.h"

namespace robopi {


    MotorLn298::MotorLn298(GpioId forward, GpioId backward, GpioId enable, System* system) :
            _forward(forward),
            _backward(backward),
            _enable(enable),
            _system(system)
            {
                _system->setMode(_forward, PI_OUTPUT);
                _system->setMode(_backward, PI_OUTPUT);
                _system->setMode(_enable, PI_OUTPUT);
                _system->setPWMfrequency(_enable,1000);
    }

    void MotorLn298::set(double dutyCycle) {
        if (dutyCycle > 0) {
            forward(dutyCycle);
        } else {
            backward(-1.0 * dutyCycle);
        }
    }

    void MotorLn298::forward(double dutyCycle) {
        auto pwm = convert(dutyCycle);
        _system->pWM(_enable, pwm);
        _system->write(_forward, PI_ON);
        _system->write(_backward, PI_OFF);
    }

    void MotorLn298::backward(double dutyCycle) {
        auto pwm = convert(dutyCycle);
        _system->pWM(_enable, pwm);
        _system->write(_forward, PI_OFF);
        _system->write(_backward, PI_ON);
    }

    void MotorLn298::stop() {
        _system->write(_forward, PI_OFF);
        _system->write(_backward, PI_OFF);
    }

    char MotorLn298::convert(double dutyCycle) {
        double dutyCycleClipped = dutyCycle > 1.0 ? 1.0 : dutyCycle;
        dutyCycle = dutyCycleClipped < 0.0 ? 0.0 : dutyCycleClipped;

        return static_cast<char>(dutyCycle * 255.0f);
    }


}