//
// Created by phil on 21.03.20.
//

#include "Encoder.h"
#include "System.h"
#include <math.h>


namespace robopi{


    void Encoder::tick()
    {
        _direction ? _wheelTicks++ : _wheelTicks--;

    }

    void Encoder::tickForward(){
        _wheelTicks++;
    }
        
    void Encoder::tickBackward(){
        _wheelTicks--;

    }


    double Encoder::position() const
    {
        return _wheelTicks * _ticksToRad;
    }

    double Encoder::ticks() const
    {
        return _wheelTicks;
    }
    Encoder::Encoder(double ticksPerRad)
    :     _wheelTicks(0U)
    ,    _direction(true)
    ,    _ticksToRad(2.0 * M_PI / ticksPerRad){


    }


}
