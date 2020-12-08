//
// Created by phil on 21.03.20.
//

#include "Sonar.h"
#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#else
#include <pigpiostub.h>
#endif
#include <thread>
#include <chrono>
constexpr int HIGH = 1;
constexpr int LOW = 0;
namespace pi_ln298n{


    Measurement Sonar::measure()
    {
        gpioWrite(_trigger, HIGH)
        std::this_thread::sleep_for(std::chrono<std::microseconds>(10));
        gpioWrite(_trigger, LOW)

        auto t_start = std::chrono::system_clock::now();
        auto t_stop = std::chrono::system_clock::now();

        //TODO timestamp in microseconds, timeout
        while (gpioRead(_echo) == 0)
        {
            t_start = std::chrono::system_clock::now()
        }
        while (gpioRead(_echo) == 1)
        {
            t_stop = std::chrono::system_clock::now()
        }

        return {t_start,t_stop}

    }


}
#endif //GPIOCPP_GPIOSONAR_H
