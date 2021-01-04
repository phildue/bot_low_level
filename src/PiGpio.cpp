//
// Created by phil on 11.12.20.
//

#include "PiGpio.h"


#include <stdexcept>
#include <iostream>
namespace robopi {

    std::shared_ptr<PiGpio> PiGpio::m_instance = nullptr;

    PiGpio::PiGpio() {

        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
        _timerCtr = 0;
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

    void PiGpio::setTimerFuncEx(int frqMs,gpioTimerFuncEx_t f, void* user)
    {
        gpioSetTimerFuncEx(_timerCtr++,frqMs,f,user);
    }

}