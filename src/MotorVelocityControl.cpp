#include "MotorVelocityControl.h"
#include <iostream>
#include <numeric>
constexpr float US_TO_S = (1.0f/(1000.0f*1000.0f));
constexpr float COUNT_TO_RAD = M_PI/5.0f;
constexpr float TICKS_US_TO_RAD_S = COUNT_TO_RAD / US_TO_S;
constexpr float RAD_S_TO_TICKS_US = 1.0f/TICKS_US_TO_RAD_S;

namespace robopi
{

    void MotorVelocityControl::update(unsigned long t)
    {
        float dT = static_cast<float>(t - _tLast);
        if (dT <= 0.0f)
        {
            return;
        }
        _tLast = t;
        auto wheelTicks = _encoder->wheelTicks();
        
        float dTicks = static_cast<float>(wheelTicks - _wheelTicksLast);
        _wheelTicksLast = wheelTicks;

        float v = dTicks/dT;

        v *= TICKS_US_TO_RAD_S;


        _velocityActual -= _vs[_filterIdx] / _filterSize;

        _vs[_filterIdx] = v;

        _velocityActual += _vs[_filterIdx] / _filterSize;

        _filterIdx++;
        
        if(_filterIdx >= _vs.size())
        {
            _filterIdx = 0;
        }


        float err = _velocitySet - _velocityActual;

        _errIntegr += err * dT;

        _dutySet += _kp * err + _ki * _errIntegr + _kd * (err - _errLast)/dT;

        _errLast = err;

        _encoder->setDirection(_dutySet > 0);
        _motor->set(_dutySet);
    }

    
    void MotorVelocityControl::set(float velocity) {
        
        
        _velocitySet = velocity;
    	/*
    	if(_velocitySet > MAX_VEL_DF_DC)
    	{
    		_velocitySet = MAX_VEL_DF_DC;
    	}else if(_velocitySet < - MAX_VEL_DF_DC)
    	{
    		_velocitySet = -MAX_VEL_DF_DC;
    	}*/
        //_velocitySet *= RAD_S_TO_TICKS_US;
       
    }

    
    void MotorVelocityControl::handleTick(uint32_t tick, long long wheelTicks, float velocity)
    {
        
    }


}		