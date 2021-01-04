//
// Created by phil on 21.03.20.
//

#include "Encoder.h"
#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#else
#include <pigpiostub.h>
#endif
#include <thread>
#include <chrono>
#include <iostream>

namespace robopi{

    void tickEx(int gpio,int level, uint32_t tick, void* user)
    {
        auto enc = (Encoder*)user;
        enc->tick();
    }

    void Encoder::tick()
    {
        _direction ? _angle+=TICKS_TO_ANGLE : _angle-TICKS_TO_ANGLE;

        if(_angle > M_2_PI)
        {
            _angle -= M_2_PI;
        }
        else if(_angle < 0)
        {
            _angle += M_2_PI;
        }
    }

    void Encoder::initialize() {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    Encoder::Encoder(GpioId in, std::shared_ptr<PiGpio> piGpio):
    _in(in),
    _piGpio(piGpio),
    _angle(0.0f){
        gpioSetMode(_in, PI_INPUT);

#ifdef COMPILE_FOR_PI
        gpioSetAlertFuncEx(_in, tickEx,this);
#endif
    }


}
