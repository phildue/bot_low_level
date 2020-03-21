//
// Created by phil on 21.03.20.
//

#include "GpioWheel.h"
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


}

void GpioWheel::forward() {

}

void GpioWheel::backward() {

}

void GpioWheel::stop() {

}

GpioWheel::~GpioWheel() {


}
