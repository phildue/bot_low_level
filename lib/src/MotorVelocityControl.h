//
// Created by phil on 21.03.20.
//

#ifndef MOTOR_LN298_ENC_H
#define MOTOR_LN298_ENC_H
#include "System.h"
#include "Encoder.h"
#include "MotorLn298.h"

namespace robopi{
    constexpr float MAX_VEL_DF_DC = 16.755;//rad_s


    class VelocityEstimator {
        public:
            virtual float estimate(double pos, double dT) = 0;
    };

    class SlidingAverageFilter : public VelocityEstimator
    {
        public:
            SlidingAverageFilter(unsigned int size):
            _size(size),
            _posLast(0U),
            _v(0.0f),
            _idx(0U){
                _vs = new double[size];
                for(int i = 0; i < _size; i++)
                {
                    _vs[i] = 0.0f;
                }
            }
            ~SlidingAverageFilter(){
                delete _vs;
            }
            float estimate(double pos, double dT) override;
        private:
            const double _size;
            double _posLast;
            double* _vs;
            unsigned int _idx;
            double _v;
    };

    class LuenbergerObserver : public VelocityEstimator
    {
        public:
            
            LuenbergerObserver(double kp,double ki):
            _kp(kp),
            _ki(ki),
            _v(0.0f),
            _velIntegr(0.0f),
            _pos(0U){}

            float estimate(double pos, double dT) override;
        private:

            double _pos;
            double _velIntegr;
            double _v,_kp,_ki;
 
    };


    class MotorVelocityControl
    {
    public:
        MotorVelocityControl(MotorLn298* motor,Encoder* encoder, VelocityEstimator* velEstimator,
            float kp, float ki, float kd,float maxVel = MAX_VEL_DF_DC):
        _motor(motor),
        _velEstimator(velEstimator),
        _encoder(encoder),
        _kp(kp),
        _ki(ki),
        _kd(kd),
        _errLast(0.0),
        _errIntegr(0.0),
        _velocitySet(0.0),
        _velocityActual(0.0),
        _dutySet(0.0){
            
            
        }

        /**
         * Pass set point
         * @param velocity in [rad/s]
         */
        void set(float velocity);

        /**
         * Perform control loop iteration
         * @param dT time difference since last update [s]
         */
        void update(float dT);

        /**
         * Get angular position from encoder
         * @return angle in [rad]
         */
        float position() const {return _encoder->position();}

        /**
         * Get position from encoder
         * @return position in [wheel ticks]
         */
        long long wheelTicks() const {return _encoder->wheelTicks();}


        /**
       * Get filtered angular velocity
       * @return velocity in [rad/s]
       */
        const float& velocity() const {return _velocityActual;}

        /**
       * Get set point angular velocity
       * @return velocity in [rad/s]
       */
        const float& velocitySet() const {return _velocitySet;}

        /**
         * Stop motor
         */
        void stop(){
            _velocitySet = 0.0;
            return _motor->stop();
        }

        /**
       * Get computed error
       * @return error in [rad/s]
       */
        const float& error() { return _errLast;}

        /**
       * Get set point to pwm
       * @return pwm duty cycle in [%]
       */
        float dutySet() { return _dutySet*100.0;}

        const MotorLn298* motor() const {return _motor;}
        const Encoder* encoder() const {return _encoder;}
        const VelocityEstimator* velocityEstimator() const {return _velEstimator;}
    protected:

        float _kp,_ki,_kd;
        float _errLast,_errIntegr;

        MotorLn298* _motor;
        Encoder* _encoder;
        VelocityEstimator* _velEstimator;
        float _velocitySet, _dutySet;
        float _velocityActual;
    
    };

}
#endif //GPIOCPP_GPIOWHEEL_H
