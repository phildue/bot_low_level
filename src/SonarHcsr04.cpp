//
// Created by phil on 21.03.20.
//

#include "SonarHcsr04.h"

namespace robopi{


    void SonarHcsr04::echo(int gpio, int level, unsigned int tick)
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
        _system->write(_trigger, PI_ON);

        _system->sleep(10); /* 10us trigger pulse */

        _system->write(_trigger, PI_OFF);
    }



    Measurement SonarHcsr04::measure()
    {
        return m_measurement;

    }

    SonarHcsr04::SonarHcsr04(GpioId trigger, GpioId echo, System* system):
    _echo(echo),
    _trigger(trigger),
    _system(system),
    m_measurement(0,0),
    m_start(0){
        _system->setMode(_echo, PI_INPUT);
        _system->setMode(_trigger, PI_OUTPUT);

    }


}
