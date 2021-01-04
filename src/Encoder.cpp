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

constexpr float TICK_TO_S = (1/(1000.0));
constexpr float COUNT_TO_RAD = M_PI/10;
constexpr float MAX_WHEELTICKS = std::numeric_limits<float>::max();
constexpr float TICKS_US_TO_RAD_S = COUNT_TO_RAD / TICK_TO_S;

namespace robopi{

    void flagEx(int gpio,int level, uint32_t tick, void* user)
    {
        Encoder* enc = (Encoder*)user;
        enc->flag(tick);
    }

    void velEx(void* user)
    {
        Encoder* enc = (Encoder*)user;
        enc->vel();
    }

    void Encoder::flag(uint32_t tick)
    {
        _direction ? _wheelTicks++ : _wheelTicks--;
    }

    void Encoder::vel()
    {
        auto position = _wheelTicks;
        float deltaTicks = static_cast<float>(position - _wheelTicksLast);

        if(deltaTicks < 1000)//in case of overflow skip computation for this time
        {
            _velocityTicks = deltaTicks/_frq;
        }

        _wheelTicksLast = position;

    }


    void Encoder::initialize() {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    float Encoder::position() const
    {
        float angle = (float)((int)_wheelTicks % 20) * COUNT_TO_RAD;
        if (angle < 0)
        {
            angle = M_2_PI - angle;
        }
        return angle;
    }

    float Encoder::velocity() const
    {
        return _velocityTicks * TICKS_US_TO_RAD_S;
    }

    Encoder::Encoder(GpioId in, std::shared_ptr<PiGpio> piGpio):
    _in(in),
    _piGpio(piGpio),
    _wheelTicks(0.0f),
    _velocityTicks(0.0f),
    _frq(50),
    _direction(true){
        gpioSetMode(_in, PI_INPUT);

#ifdef COMPILE_FOR_PI
        gpioSetAlertFuncEx(_in, flagEx,this);
        piGpio->setTimerFuncEx(_frq, velEx,this);

#endif
    }


}
