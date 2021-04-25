//
// Created by phil on 21.03.20.
//

#include "SonarHcsr04.h"
#include <thread>
#include <chrono>
#include <iostream>

namespace robopi{


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
        _gpios->write(_trigger, PI_ON);

        _gpios->delay(10); /* 10us trigger pulse */

        _gpios->write(_trigger, PI_OFF);
    }



    Measurement SonarHcsr04::measure()
    {
        return m_measurement;

    }

    void SonarHcsr04::initialize() {
        if (_gpios->initialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
    }

    SonarHcsr04::SonarHcsr04(GpioId trigger, GpioId echo, std::shared_ptr<Gpio> gpios):
    _echo(echo),
    _trigger(trigger),
    _gpios(gpios),
    m_measurement(0,0),
    m_start(0){
        _gpios->setMode(_echo, PI_INPUT);
        _gpios->setMode(_trigger, PI_OUTPUT);

        _gpios->setAlertFuncEx(_echo, echoEx,this);
        _gpios->setTimerFuncEx(50, triggerEx,this);
    }


}
