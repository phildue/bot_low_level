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

    constexpr float TICKS_TO_ANGLE = M_PI/10;

    class Encoder
    {
    public:
        Encoder(GpioId in, std::shared_ptr<PiGpio> piGpio = robopi::PiGpio::instance());
        const float& position() const {return _angle;}
        void tick();
        void reset() {_angle = 0;};
        void reverseDirection(){_direction = !_direction;}

    protected:
        void initialize();
        GpioId _in;
        std::shared_ptr<PiGpio> _piGpio;
        float _angle;
        bool _direction;

    };

}
#endif //ENCODER_H
