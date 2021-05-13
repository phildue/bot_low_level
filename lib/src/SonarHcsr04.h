//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOSONAR_H
#define GPIOCPP_GPIOSONAR_H

#include "types.h"
#include "System.h"
namespace robopi{

    typedef long long int Timestamp;
    constexpr float SPEED_SOUND = 343.0f;
    constexpr float T_TO_M = (1/(1000.0*1000.0)*SPEED_SOUND/2.0f);
    constexpr float MAX_RANGE = 4.0;

    class Measurement{
    public:
        Measurement(Timestamp out, Timestamp in):
                _out(out),
                _in(in),
                _distance(0)
        {
            Timestamp elapsed = _in - _out;
            _distance = static_cast<float>(elapsed)*T_TO_M;
            if(_distance > MAX_RANGE)
            {
                _distance = MAX_RANGE;
            }

        }
        const float& distance() const{
            return _distance;
        }
    private:
        Timestamp _out,_in;
        float _distance;
    };


    class SonarHcsr04
    {
    public:
        SonarHcsr04(GpioId trigger, GpioId echo,System* system);
        Measurement measure();
        void echo(int gpio, int level, unsigned int tick);
        void trigger();
    protected:
        GpioId _trigger,_echo;
        Measurement m_measurement;
        Timestamp m_start;
        System* _system;
    };

}
#endif //GPIOCPP_GPIOSONAR_H
