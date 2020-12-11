//
// Created by phil on 11.12.20.
//

#include "PiGpio.h"

#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#else
#include <pigpiostub.h>
#endif
#include <stdexcept>
#include <iostream>
namespace pi_ln298n {

    PiGpio::PiGpio() {

        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    PiGpio::~PiGpio() {
        gpioTerminate();

    }
}