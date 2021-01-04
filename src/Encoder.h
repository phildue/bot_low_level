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


    class Encoder
    {
    public:
        Encoder(GpioId in, std::shared_ptr<PiGpio> piGpio = robopi::PiGpio::instance());

        float wheelTicks() const {return _wheelTicks;}

        float position() const;

        float velocity() const;

        void flag(uint32_t tick);
        void vel();
        void reset() {_wheelTicks = 0;};
        void reverseDirection(){_direction = !_direction;}

    protected:
        void initialize();
        GpioId _in;
        std::shared_ptr<PiGpio> _piGpio;
        float _wheelTicksLast,_velocityTicks;
        long long _wheelTicks;
        bool _direction;
        long long _lastTick;
        float _frq;

    };

}
#endif //ENCODER_H
