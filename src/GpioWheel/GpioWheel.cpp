//
// Created by phil on 21.03.20.
//

#include "GpioWheel/GpioWheel.h"
#include <pigpio.h>
#include <stdexcept>
constexpr int HIGH = 1;
constexpr int LOW = 0;

unsigned int GpioWheel::_nInstances = 0;

GpioWheel::GpioWheel(GpioId forward, GpioId backward, GpioId enable):
_forward(forward),
_backward(backward),
_enable(enable){

    if (0 == _nInstances)
    {
        if(gpioInitialise() < 0)
        {
            throw std::runtime_error( "pigpio initialisation failed\n");
        }
    }
    _nInstances++;

    gpioSetMode(_forward, PI_OUTPUT);
    gpioSetMode(_backward, PI_OUTPUT);
    gpioSetMode(_enable, PI_OUTPUT);
}

void GpioWheel::set(float torquePerc) {
    if ( torquePerc > 0)
    {
        forward(torquePerc);
    }else{
        backward(std::abs(torquePerc));
    }
}

void GpioWheel::forward(float torquePerc) {
    gpioPWM(_enable, torqueToDutyCycle(torquePerc));

    gpioWrite(_forward,HIGH);
    gpioWrite(_backward,LOW);
}

void GpioWheel::backward(float torquePerc) {
    gpioPWM(_enable, torqueToDutyCycle(torquePerc));

    gpioWrite(_forward, LOW);
    gpioWrite(_backward,HIGH);
}

void GpioWheel::stop() {
    gpioWrite(_forward,LOW);
    gpioWrite(_backward,LOW);
}

uint8_t GpioWheel::torqueToDutyCycle(float torquePerc) {

    auto torquePercClipped = torquePerc > 1.0 ? 1.0 : torquePerc;
    torquePercClipped = torquePercClipped < 0.0 ? 0.0 : torquePercClipped;

    return (uint8_t)(torquePercClipped*255.0f);
}

GpioWheel::~GpioWheel() {

    if(_nInstances <= 1)
    {
        /* Stop DMA, release resources */
        gpioTerminate();
    }
    _nInstances--;
}
