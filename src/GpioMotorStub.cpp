//
// Created by phil on 21.03.20.
//

#include "GpioMotor.h"
#include <stdexcept>
constexpr int HIGH = 1;
constexpr int LOW = 0;
namespace pi_ln298n {

    unsigned int GpioMotor::_nInstances = 0;

    GpioMotor::GpioMotor(GpioId forward, GpioId backward, GpioId enable) :
            _forward(forward),
            _backward(backward),
            _enable(enable) {

    }

    void GpioMotor::forward(float torquePerc) {

    }

    void GpioMotor::backward(float torquePerc) {

    }

    void GpioMotor::stop() {

    }

    GpioMotor::~GpioMotor() {


    }

    uint8_t GpioMotor::torqueToDutyCycle(float torquePerc) {
        return 0;
    }

    void GpioMotor::set(float torquePerc) {

    }
}