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


    class MotorLn298Enc
    {
    public:
        MotorLn298Enc(GpioId forward, GpioId backward, GpioId enable,GpioId encoderIn,std::shared_ptr<PiGpio> piGpio = robopi::PiGpio::instance(),float maxVel = MAX_VEL_DF_DC):
        _motor(forward,backward,enable,piGpio,maxVel),
        _encoder(encoderIn,piGpio){}

        /**
         * Set angular velocity
         * @param velocity in rad/s
         */
        void set(float velocity) {
            if(sgn<float>(velocity) != sgn<float>(_setPoint)){
                _encoder.reverseDirection();
            }
            _setPoint = velocity;
            _motor.set(velocity);
        }

        /**
         * Get angular position from encoder
         * @return angle in rad
         */
        float position() const {return _encoder.position();}

        void stop(){return _motor.stop();}

        const float& maxVel() const {return _motor.maxVel();}
    protected:

        template <typename T> int sgn(T val) {
            return (T(0) < val) - (val < T(0));
        }

        MotorLn298 _motor;
        Encoder _encoder;
        float _setPoint;
    };

}
#endif //GPIOCPP_GPIOWHEEL_H
