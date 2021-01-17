#include "MotorVelocityControl.h"
#include <iostream>
#include <numeric>
constexpr float US_TO_S = (1.0f/(1000.0f*1000.0f));
constexpr float COUNT_TO_RAD = M_PI/5.0f;
constexpr float TICKS_US_TO_RAD_S = COUNT_TO_RAD / US_TO_S;
constexpr float RAD_S_TO_TICKS_US = 1.0f/TICKS_US_TO_RAD_S;

namespace robopi
{

    float SlidingAverageFilter::estimate(long long pos, float dT)
    {

        float dPos = static_cast<float>(pos - _posLast);
        _posLast = pos;

        float v = dPos/dT;

        _v -= _vs[_idx] / _size;

        _vs[_idx] = v;

        _v += _vs[_idx] / _size;

        _idx++;
        
        if(_idx >= _vs.size())
        {
            _idx = 0;
        }

        return _v;
    }

    float LuenbergerObserver::estimate(long long pos, float dT)
    {


        float posEst = _posLast + _v * dT;
        float errPos = static_cast<float>(pos - posEst);

        _velIntegr += _ki * errPos * dT;

        _v = _kp * errPos + _velIntegr;

        _posLast = pos;

        return _v;
    }

    void MotorVelocityControl::update(unsigned long t)
    {

        float dT = static_cast<float>(t - _tLast)*US_TO_S;
        if (dT <= 0.0f)
        {
            return;
        }
        _tLast = t;
        const long long pos = _encoder->wheelTicks()*COUNT_TO_RAD;
      
        _velocityActual = _velEstimator->estimate(pos,dT);


        float err = _velocitySet - _velocityActual;


        _errIntegr += err * dT;

        _dutySet = _kp * err + _ki * _errIntegr + _kd * (err - _errLast)/dT;

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

    
    void MotorVelocityControl::handleTick(uint32_t tick, long long wheelTicks)
    {
        
    }


}		