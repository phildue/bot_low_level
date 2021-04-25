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

    class TickHandler
    {
    public:
        virtual void handleTick(uint32_t tick, long long wheelTicks) = 0;
    };

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

        void subscribe(std::shared_ptr<TickHandler> observer)
        {
            _observers.push_back(observer);
        }
        ~Encoder();


    protected:
        std::vector<std::shared_ptr<TickHandler>> _observers;
        void initialize();
        GpioId _in;
        std::shared_ptr<Gpio> _gpios;
        long long _wheelTicks;
        bool _direction;
        float _timeout;


    };

}
#endif //ENCODER_H
