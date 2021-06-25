//
// Created by phil on 21.03.20.
//

#include "Encoder.h"
#include "System.h"
#include <math.h>

constexpr double TICK_TO_S = (1/(1000.0));
constexpr double COUNT_TO_RAD = M_PI/10.0f;
constexpr double TICKS_US_TO_RAD_S = COUNT_TO_RAD / TICK_TO_S;

namespace robopi{


    void Encoder::tick()
    {
        _direction ? _wheelTicks++ : _wheelTicks--;

    }

    double Encoder::position() const
    {
        return _wheelTicks * COUNT_TO_RAD;
    }

    Encoder::Encoder(GpioId in, System* system):
    _in(in),
    _system(system),
    _wheelTicks(0U),
    _direction(true){
        system->setMode(_in, PI_INPUT);

        system->setPullUpDown(_in, PI_PUD_UP);


    }


}
