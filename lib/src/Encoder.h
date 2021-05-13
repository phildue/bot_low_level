//
// Created by phil on 21.03.20.
//

#ifndef ENCODER_H
#define ENCODER_H

#include "types.h"
#include "System.h"
namespace robopi{

    class Encoder
    {
    public:
        Encoder(GpioId in, System* system);

        long long wheelTicks() const {return _wheelTicks;}

        float position() const;


        const GpioId& gpioIn() const { return _in;}

        void tick();

        void reset() {_wheelTicks = 0;};

        void setDirection(bool forward){_direction = forward;}

        ~Encoder();


    protected:
        GpioId _in;
        System* _system;
        long long _wheelTicks;
        bool _direction;
        float _timeout;


    };

}
#endif //ENCODER_H
