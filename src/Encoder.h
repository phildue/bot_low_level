//
// Created by phil on 21.03.20.
//

#ifndef ENCODER_H
#define ENCODER_H

#include <chrono>
#include <memory>
#include <cmath>
#include <vector>

#include "Gpio.h"
namespace robopi{

    class Encoder
    {
    public:
        Encoder(GpioId in, uint32_t timeout = 0, std::shared_ptr<Gpio> gpios = robopi::Gpio::instance());

        long long wheelTicks() const {return _wheelTicks;}

        float position() const;


        const GpioId& gpioIn() const { return _in;}

        void interrupt(int gpio,int level, uint32_t tick);

        void reset() {_wheelTicks = 0;};

        void setDirection(bool forward){_direction = forward;}

        ~Encoder();


    protected:
        void initialize();
        GpioId _in;
        std::shared_ptr<Gpio> _gpios;
        long long _wheelTicks;
        bool _direction;
        float _timeout;


    };

}
#endif //ENCODER_H
