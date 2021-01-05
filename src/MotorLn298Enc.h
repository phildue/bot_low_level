//
// Created by phil on 21.03.20.
//

#ifndef MOTOR_LN298_ENC_H
#define MOTOR_LN298_ENC_H
#include <memory>
#include "PiGpio.h"
#include "Encoder.h"
#include "MotorLn298.h"

namespace robopi{
    constexpr float MAX_VEL_DF_DC = 16.755;//rad_s


    class MotorLn298Enc
    {
    public:
        MotorLn298Enc(GpioId forward, GpioId backward, GpioId enable,GpioId encoderIn,float dT, float kp, float ki, float kd,std::shared_ptr<PiGpio> piGpio = robopi::PiGpio::instance(),float maxVel = MAX_VEL_DF_DC):
        _motor(forward,backward,enable,piGpio),
        _dT(dT),
        _kp(kp),
        _ki(ki),
        _kd(kd),
        _errLast(0.0),
        _errIntegr(0.0),
        _velocitySet(0.0),
        _velocityActual(0.0),
        _dutySet(0.0),
        _encoder(encoderIn,500,piGpio){}

        /**
         * Pass set point
         * @param velocity in rad/s
         */
        void set(float velocity);

        /**
         * Get angular position from encoder
         * @return angle in rad
         */
        float position() const {return _encoder.position();}

        /**
         * Get position from encoder
         * @return position in wheel ticks
         */
        long long wheelTicks() const {return _encoder.wheelTicks();}


        /**
       * Get filtered angular velocity
       * @return velocity in rad/s
       */
        float velocity() const {return _velocityActual;}

        void stop(){return _motor.stop();}

        const float& error() { return _errLast;}
        const float& dutySet() { return _dutySet;}

        
    protected:

        void pid();
        void measure();
        
        float _kp,_ki,_kd;
        float _dT;
        float _errLast,_errIntegr;

        MotorLn298 _motor;
        Encoder _encoder;
        float _velocitySet, _dutySet;
        float _velocityActual;
    };

}
#endif //GPIOCPP_GPIOWHEEL_H
