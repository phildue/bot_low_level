//
// Created by phil on 21.03.20.
//

#include "GpioWheel/GpioWheel.h"
#include <pigpio.h>
#include <stdexcept>
constexpr int HIGH = 1;
constexpr int LOW = 0;

unsigned int GpioWheel::_nInstances = 0;

GpioWheel::GpioWheel(GpioId forward, GpioId backward, GpioId enable, float dutyCycle = 0.5f):
_forward(forward),
_backward(backward),
_enable(enable){


    if( !(0 < dutyCycle && dutyCycle < 1.0))
    {
        throw std::runtime_error( "Duty cycle has to be between 0 and 1");

    }

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

    int dutyCycleBit = (int)(dutyCycle*255.0f);

    gpioPWM(_enable, dutyCycleBit);

}

void GpioWheel::forward() {
    gpioWrite(_forward,HIGH);
    gpioWrite(_backward,LOW);
}

void GpioWheel::backward() {
    gpioWrite(_forward, LOW);
    gpioWrite(_backward,HIGH);
}

void GpioWheel::stop() {
    gpioWrite(_forward,LOW);
    gpioWrite(_backward,LOW);
}

GpioWheel::~GpioWheel() {

    if(_nInstances <= 1)
    {
        /* Stop DMA, release resources */
        gpioTerminate();
    }
    _nInstances--;
}
