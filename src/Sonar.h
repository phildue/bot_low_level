//
// Created by phil on 21.03.20.
//

#ifndef GPIOCPP_GPIOSONAR_H
#define GPIOCPP_GPIOSONAR_H
namespace pi_ln298n{

    using GpioId = unsigned int;
    using Timestamp = unsigned long int;
    constexpr int SPEED_SOUND = 343;
    constexpr int SECONDS_TO_MICROSECONDS = 1000*1000;
    constexpr float MICROSECONDS_TO_SECONDS = 1/1000*1000;
    constexpr float T_TO_M = MICROSECONDS_TO_SECONDS*SPEED_SOUND/2;
    class Sonar
    {
        class Measurement{
            Timestamp out,in;
            float distance(float egoVel){
                return static_cast<float>(t_stop - t_start)*T_TO_M;
            }
        };

    public:
        Sonar(GpioId trigger, GpioId echo);
        Measurement measure();
        ~Sonar();
    protected:
        GpioId _trigger,_echo;
    };

}
#endif //GPIOCPP_GPIOSONAR_H
