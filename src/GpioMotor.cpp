//
// Created by phil on 21.03.20.
//

#include "GpioMotor.h"

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

    unsigned int GpioMotor::_nInstances = 0;

    GpioMotor::GpioMotor(GpioId forward, GpioId backward, GpioId enable) :
            _forward(forward),
            _backward(backward),
            _enable(enable) {


        _nInstances++;

        gpioSetMode(_forward, PI_OUTPUT);
        gpioSetMode(_backward, PI_OUTPUT);
        gpioSetMode(_enable, PI_OUTPUT);
    }

    void GpioMotor::set(float torquePerc) {
        initialize();
        if (torquePerc > 0) {
            forward(torquePerc);
        } else {
            backward(std::abs(torquePerc));
        }
    }

    void GpioMotor::forward(float effortPerc) {
        auto pwm = effort2pwm(effortPerc);
        gpioPWM(_enable, pwm);
        gpioWrite(_forward, HIGH);
        gpioWrite(_backward, LOW);
    }

    void GpioMotor::backward(float effortPerc) {
        auto pwm = effort2pwm(effortPerc);
        gpioPWM(_enable, pwm);
        gpioWrite(_forward, LOW);
        gpioWrite(_backward, HIGH);
    }

    void GpioMotor::stop() {
        gpioWrite(_forward, LOW);
        gpioWrite(_backward, LOW);
    }

    int GpioMotor::effort2pwm(float effortPerc) {

        auto torquePercClipped = effortPerc > 1.0 ? 1.0 : effortPerc;
        torquePercClipped = torquePercClipped < 0.0 ? 0.0 : torquePercClipped;

        return (torquePercClipped * 255.0f);
    }

    GpioMotor::~GpioMotor() {

        if (_nInstances <= 1) {
            gpioTerminate();
        }
        _nInstances--;
    }

    float GpioMotor::effort() {
        auto pwm = gpioGetPWMdutycycle(_enable)/255.0f;
        if(HIGH == gpioRead(_forward) && LOW == gpioRead(_backward))
        {
            return pwm;
        }else{
            return -1.0f * pwm;
        }
    }

    void GpioMotor::initialize() {
        if (gpioInitialise() == PI_INITIALISED) {
            std::cout << "Pigpio initalised" << std::endl;
        }else{
            throw std::runtime_error("pigpio initialisation failed\n");

        }
    }
}