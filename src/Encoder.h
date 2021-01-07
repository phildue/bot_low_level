//
// Created by phil on 21.03.20.
//

#ifndef ENCODER_H
#define ENCODER_H

#include <chrono>
#include <memory>
#include <cmath>
#include "PiGpio.h"
namespace robopi{

    class TickHandler
    {
    public:
        virtual void handleTick(uint32_t tick, long long wheelTicks, float velocity) = 0;
    };

    class Encoder
    {
    public:
        Encoder(GpioId in, uint32_t timeout = 0, std::shared_ptr<PiGpio> piGpio = robopi::PiGpio::instance());

        long long wheelTicks() const {return _wheelTicks;}

        float position() const;

        float velocity() const;

        const GpioId& gpioIn() const { return _in;}

        void flag(uint32_t tick);
        void vel(uint32_t tick);
        void reset() {_wheelTicks = 0;};
        void setDirection(bool forward){_direction = forward;}

        TickHandler* tickHandler;
    protected:
        void initialize();
        GpioId _in;
        std::shared_ptr<PiGpio> _piGpio;
        long long _wheelTicks;
        bool _direction;
        float _timeout;
        int32_t _deltaWheelTicks,_deltaTicks;
        uint32_t _lastWheelTick,_lastTick;


    };

}
#endif //ENCODER_H
