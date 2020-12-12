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

    void SonarHcsr04::echo(int gpio, int level, uint32_t tick)
    {
        if (level == HIGH)
        {
            m_start = tick;
            std::cout << "Trigger High" << std::endl;
        }
        else if (level == LOW)
        {
            m_measurement = Measurement(m_start,tick);
            std::cout << "Trigger Low" << std::endl;
        }
    }


    void echoEx(int gpio, int level, uint32_t tick, void *user)
    {
        auto sonar = (SonarHcsr04*)user;
        sonar->echo(gpio,level,tick);
    }


    Measurement SonarHcsr04::measure()
    {
        initialize();

        trigger();

        return m_measurement;

    }

    void SonarHcsr04::initialize() {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    SonarHcsr04::SonarHcsr04(GpioId trigger, GpioId echo, std::shared_ptr<PiGpio> piGpio):
    _echo(echo),
    _trigger(trigger),
    _piGpio(piGpio),
    m_measurement(0,0),
    m_start(0){
        gpioSetMode(_echo, PI_OUTPUT);
        gpioSetMode(_trigger, PI_INPUT);


        gpioSetAlertFuncEx(_echo, echoEx,this);

    }


}
