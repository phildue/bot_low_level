//
// Created by phil on 21.03.20.
//

#include "Encoder.h"
#include "System.h"
#include <math.h>

constexpr float TICK_TO_S = (1/(1000.0));
constexpr float COUNT_TO_RAD = M_PI/10.0f;
constexpr float TICKS_US_TO_RAD_S = COUNT_TO_RAD / TICK_TO_S;

namespace robopi{


    void Encoder::tick()
    {
        _direction ? _wheelTicks++ : _wheelTicks--;

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

    Encoder::Encoder(GpioId in, System* system):
    _in(in),
    _system(system),
    _wheelTicks(0U),
    _direction(true){
        system->setMode(_in, PI_INPUT);

        system->setPullUpDown(_in, PI_PUD_UP);


    }
    Encoder::~Encoder()
    {


    }


}
