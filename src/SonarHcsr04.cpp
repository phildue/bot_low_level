//
// Created by phil on 21.03.20.
//

#include "SonarHcsr04.h"
#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#else
#include <pigpiostub.h>
#endif
#include <thread>
#include <chrono>
#include <iostream>

constexpr int HIGH = 1;
constexpr int LOW = 0;
namespace robopi{


    Measurement SonarHcsr04::measure()
    {
        initialize();

        gpioWrite(_trigger, HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        gpioWrite(_trigger, LOW);

        using namespace std::chrono;
        Timestamp t_start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count(),t_stop = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

        //Wait for return signal but no longer than 1ms second each to avoid dead lock in case of failures
        for(int i = 0; i < 10000 && gpioRead(_echo) == 0; i++)
        {
            t_start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        }
        for(int i = 0; i < 10000 && gpioRead(_echo) == 1; i++)
        {
            t_stop = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        }
        std::cout << "t_stop: " << t_stop << " t_start: " << t_start;
        return {t_stop,t_start};

    }

    void SonarHcsr04::initialize() {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    SonarHcsr04::SonarHcsr04(GpioId trigger, GpioId echo, std::shared_ptr<PiGpio> piGpio):
    _echo(echo),
    _trigger(trigger),
    _piGpio(piGpio){

    }


}
