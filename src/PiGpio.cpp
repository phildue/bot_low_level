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
namespace robopi {

    std::shared_ptr<PiGpio> PiGpio::m_instance = nullptr;

    PiGpio::PiGpio() {

        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    PiGpio::~PiGpio() {
        gpioTerminate();

    }

    std::shared_ptr<PiGpio> PiGpio::instance()
    {

        if(!m_instance){
            m_instance = std::shared_ptr<PiGpio>(new PiGpio);
        }

        return m_instance;
    }
}