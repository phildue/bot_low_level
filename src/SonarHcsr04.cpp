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
        if (level == PI_ON)
        {
            m_start = tick;
        }
        else if (level == PI_OFF)
        {
            m_measurement = Measurement(m_start,tick);
        }else
	{
	}
    }

    void SonarHcsr04::trigger()
    {
	gpioWrite(_trigger, PI_ON);

        gpioDelay(10); /* 10us trigger pulse */

        gpioWrite(_trigger, PI_OFF);
    }


    void echoEx(int gpio, int level, uint32_t tick, void *user)
    {
        auto sonar = (SonarHcsr04*)user;
        sonar->echo(gpio,level,tick);
    }

    void triggerEx(void* user)
    {
       auto sonar = (SonarHcsr04*)user;
       sonar->trigger();
    }
    Measurement SonarHcsr04::measure()
    {
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
        gpioSetMode(_echo, PI_INPUT);
        gpioSetMode(_trigger, PI_OUTPUT);


        gpioSetAlertFuncEx(_echo, echoEx,this);
        gpioSetTimerFuncEx(0, 50, triggerEx,this);
    }


}
