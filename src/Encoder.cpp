//
// Created by phil on 21.03.20.
//

#include "Encoder.h"
#include <thread>
#include <chrono>
#include <iostream>

constexpr float TICK_TO_S = (1/(1000.0));
constexpr float COUNT_TO_RAD = M_PI/5.0f;
constexpr float TICKS_US_TO_RAD_S = COUNT_TO_RAD / TICK_TO_S;

namespace robopi{

    void interruptEx(int gpio,int level, uint32_t tick, void* user)
    {
        if(level == FALLING_EDGE)
        {
             Encoder* enc = (Encoder*)user;

             enc->interrupt(gpio,level,tick);
            
        }
        
    }

    void Encoder::interrupt(int gpio,int level, uint32_t tick)
    {
        _direction ? _wheelTicks++ : _wheelTicks--;
        for(const auto& tickHandler : _observers)
        {
            tickHandler->handleTick(tick,wheelTicks());
        }
        
    }


    void Encoder::initialize() {
        if (_gpios->initialise() < 0) {
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

    Encoder::Encoder(GpioId in,uint32_t timeout, std::shared_ptr<Gpio> gpios):
    _in(in),
    _gpios(gpios),
    _wheelTicks(0U),
    _timeout(timeout),
    _direction(true){
        gpios->setMode(_in, PI_INPUT);

        gpios->setPullUpDown(_in, PI_PUD_UP);
        //gpioSetAlertFuncEx(_in,interruptEx,this);
        gpios->setISRFuncEx(_in,FALLING_EDGE,_timeout,interruptEx,this);


    }
    Encoder::~Encoder()
    {
        //gpioSetAlertFunc(_in,NULL);
        _gpios->setISRFuncEx(_in,FALLING_EDGE,_timeout,NULL,this);


    }


}
