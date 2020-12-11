//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOSONAR_H
#define GPIOCPP_GPIOSONAR_H

#include <chrono>
#include <memory>
#include "PiGpio.h"
namespace pi_ln298n{

    typedef long long int Timestamp;
    constexpr float SPEED_SOUND = 343.0f;
    constexpr float T_TO_M = (1000.0*1000.0*1000.0*SPEED_SOUND/2.0f);


    class Measurement{
    public:
        Measurement(Timestamp out, Timestamp in):
                _out(out),
                _in(in),
                _distance(0)
        {
            Timestamp elapsed = _in - _out;
            _distance = static_cast<float>(elapsed)*T_TO_M;

        }
        const float& distance() const{
            return _distance;
        }
    private:
        Timestamp _out,_in;
        float _distance;
    };


    class SonarHcr04
    {
    public:
        SonarHcr04(GpioId trigger, GpioId echo,std::shared_ptr<PiGpio> piGpio);
        Measurement measure();
    protected:
        void initialize();

        GpioId _trigger,_echo;
        std::shared_ptr<PiGpio> _piGpio;
    };

}
#endif //GPIOCPP_GPIOSONAR_H
