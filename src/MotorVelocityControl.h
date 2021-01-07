//
// Created by phil on 21.03.20.
//

#ifndef MOTOR_LN298_ENC_H
#define MOTOR_LN298_ENC_H
#include <memory>
#include <vector>
#include "PiGpio.h"
#include "Encoder.h"
#include "MotorLn298.h"

namespace robopi{
    constexpr float MAX_VEL_DF_DC = 16.755;//rad_s


    class MotorVelocityControl : public TickHandler
    {
    public:
        MotorVelocityControl(std::shared_ptr<MotorLn298> motor,std::shared_ptr<Encoder> encoder, float kp, float ki, float kd,uint16_t filterSize,float maxVel = MAX_VEL_DF_DC):
        _motor(motor),
        _kp(kp),
        _ki(ki),
        _kd(kd),
        _errLast(0.0),
        _errIntegr(0.0),
        _tLast(0),
        _velocitySet(0.0),
        _velocityActual(0.0),
        _dutySet(0.0),
        _filterIdx(0),
        _wheelTicksLast(0),
        _vs(filterSize),
        _filterSize(static_cast<float>(filterSize)),
          _encoder(encoder){
            _encoder->tickHandler = this;
            
            for(int i = 0; i < filterSize; i++)
            {
                _vs[i] = 0;
            }
        }

        /**
         * Pass set point
         * @param velocity in rad/s
         */
        void set(float velocity);

        /**
         * Perform control loop iteration
         */
        void update(unsigned long t);

        /**
         * Get angular position from encoder
         * @return angle in rad
         */
        float position() const {return _encoder->position();}

        /**
         * Get position from encoder
         * @return position in wheel ticks
         */
        long long wheelTicks() const {return _encoder->wheelTicks();}


        /**
       * Get filtered angular velocity
       * @return velocity in rad/s
       */
        float velocity() const {return _velocityActual;}

        void stop(){return _motor->stop();}

        const float& error() { return _errLast;}
        const float& dutySet() { return _dutySet;}

        void handleTick(uint32_t tick, long long wheelTicks, float velocity);
    protected:

        float _kp,_ki,_kd,_filterSize;
        float _errLast,_errIntegr;
        unsigned long _tLast;

        std::shared_ptr<MotorLn298> _motor;
        std::shared_ptr<Encoder> _encoder;
        float _velocitySet, _dutySet;
        float _velocityActual;
        long long _wheelTicksLast;
        std::vector<float> _vs;
        unsigned int _filterIdx;
    };

}
#endif //GPIOCPP_GPIOWHEEL_H
