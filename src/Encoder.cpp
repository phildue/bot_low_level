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
constexpr float COUNT_TO_RAD = M_PI/5;
constexpr float TICKS_US_TO_RAD_S = COUNT_TO_RAD / TICK_TO_S;

namespace robopi{

    void flagEx(int gpio,int level, uint32_t tick, void* user)
    {
        Encoder* enc = (Encoder*)user;

        if(level == 0)
        {
            enc->flag(tick);
        }
        enc->vel(tick);
    }

    void Encoder::flag(uint32_t tick)
    {
        _direction ? _wheelTicks++ : _wheelTicks--;
    }

    void Encoder::vel(uint32_t tick)
    {
        int32_t deltaWheelTicks = int32_t(_wheelTicks - _lastWheelTick);
        int32_t deltaTicks = int32_t(tick - _lastTick);

        if(std::abs(deltaWheelTicks) < 1000 && deltaTicks > 0)//in case of overflow skip computation for this time
        {
            _deltaWheelTicks = deltaWheelTicks;
            _deltaTicks = deltaTicks;
        }

        _lastTick = tick;
        _lastWheelTick = _wheelTicks;

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
        return ((float)_deltaWheelTicks/(float)_deltaTicks) * TICKS_US_TO_RAD_S;
    }

    Encoder::Encoder(GpioId in,uint32_t timeout, std::shared_ptr<PiGpio> piGpio):
    _in(in),
    _piGpio(piGpio),
    _wheelTicks(0.0f),
    _deltaWheelTicks(0),
    _deltaTicks(1),
    _lastTick(0),
    _lastWheelTick(0),
    _timeout(timeout),
    _direction(true){
        gpioSetMode(_in, PI_INPUT);

        gpioSetISRFuncEx(_in,FALLING_EDGE,_timeout,flagEx,this);
        //gpioSetAlertFuncEx(_in, flagEx,this);
        //piGpio->setTimerFuncEx(_frq, velEx,this);

    }


}
