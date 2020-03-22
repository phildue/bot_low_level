//
// Created by phil on 21.03.20.
//

#include "GpioWheel/GpioWheel.h"
#include <stdexcept>
constexpr int HIGH = 1;
constexpr int LOW = 0;

unsigned int GpioWheel::_nInstances = 0;

GpioWheel::GpioWheel(GpioId forward, GpioId backward, GpioId enable):
_forward(forward),
_backward(backward),
_enable(enable){

}

void GpioWheel::forward(float torquePerc) {

}

void GpioWheel::backward(float torquePerc) {

}

void GpioWheel::stop() {

}

GpioWheel::~GpioWheel() {


}

uint8_t GpioWheel::torqueToDutyCycle(float torquePerc) {
    return 0;
}

void GpioWheel::set(float torquePerc) {

}
