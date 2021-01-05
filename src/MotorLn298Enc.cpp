#include "MotorLn298Enc.h"
#include <iostream>
constexpr float COUNT_TO_RAD = M_PI/10;

namespace robopi
{
    void MotorLn298Enc::set(float velocity) {
        if((velocity < 0 && _velocitySet > 0) ||
                (velocity > 0 && _velocitySet < 0)){
            _encoder.reverseDirection();
        }
        
        _velocitySet = velocity;
    	
    	if(_velocitySet > MAX_VEL_DF_DC)
    	{
    		_velocitySet = MAX_VEL_DF_DC;
    	}else if(_velocitySet < - MAX_VEL_DF_DC)
    	{
    		_velocitySet = -MAX_VEL_DF_DC;
    	}

    	measure();
        
        pid();

        _motor.set(_dutySet);
    }

    void MotorLn298Enc::pid()
    {

    	float err = _velocitySet - _velocityActual;

    	_errIntegr += err * _dT;

    	_dutySet += _kp * err + _ki * _errIntegr + _kd * (err - _errLast)/_dT;

    	_errLast = err;

    } 


    void MotorLn298Enc::measure()
    {

        float velMeasured = _encoder.velocity();

        _velocityActual += 1.0f/10.0f*(velMeasured - _velocityActual);

    } 
}		