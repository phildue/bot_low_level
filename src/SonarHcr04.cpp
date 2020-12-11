//
// Created by phil on 21.03.20.
//

#include "SonarHcr04.h"
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


    Measurement SonarHcr04::measure()
    {
        initialize();

        gpioWrite(_trigger, HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        gpioWrite(_trigger, LOW);

        using namespace std::chrono;
        Timestamp t_start = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count(),t_stop = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();

        //Wait for return signal but no longer than 1 second each to avoid dead lock in case of failures
        for(int i = 0; i < 1000000000 && gpioRead(_echo) == 0; i++)
        {
            t_start += 1;
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
        for(int i = 0; i < 1000000000 && gpioRead(_echo) == 1; i++)
        {
            t_stop += 1;
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }

        return {t_start,t_stop};

    }

    void SonarHcr04::initialize() {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    SonarHcr04::SonarHcr04(GpioId trigger, GpioId echo, std::shared_ptr<PiGpio> piGpio):
    _echo(echo),
    _trigger(trigger),
    _piGpio(piGpio){

    }


}
