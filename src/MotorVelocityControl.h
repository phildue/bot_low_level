//
// Created by phil on 21.03.20.
//

#ifndef MOTOR_LN298_ENC_H
#define MOTOR_LN298_ENC_H
#include <memory>
#include <vector>
#include "Gpio.h"
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
            SlidingAverageFilter(uint16_t size):
            _size(size),
            _posLast(0U),
            _v(0.0f),
            _idx(0U){
                _vs.resize(_size);
                for(int i = 0; i < _size; i++)
                {
                    _vs[i] = 0.0f;
                }
            }
            float estimate(double pos, double dT) override;
        private:
            const double _size;
            double _posLast;
            std::vector<double> _vs;
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


    class MotorVelocityControl : public TickHandler
    {
    public:
        MotorVelocityControl(std::shared_ptr<MotorLn298> motor,std::shared_ptr<Encoder> encoder, std::shared_ptr<VelocityEstimator> velEstimator,
            float kp, float ki, float kd,float maxVel = MAX_VEL_DF_DC):
        _motor(motor),
        _velEstimator(velEstimator),
        _encoder(encoder),
        _kp(kp),
        _ki(ki),
        _kd(kd),
        _errLast(0.0),
        _errIntegr(0.0),
        _tLast(0),
        _velocitySet(0.0),
        _velocityActual(0.0),
        _dutySet(0.0){
            
            
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

        void handleTick(uint32_t tick, long long wheelTicks);
    protected:

        float _kp,_ki,_kd;
        float _errLast,_errIntegr;
        unsigned long _tLast;

        std::shared_ptr<MotorLn298> _motor;
        std::shared_ptr<Encoder> _encoder;
        std::shared_ptr<VelocityEstimator> _velEstimator;
        float _velocitySet, _dutySet;
        float _velocityActual;
    
    };

}
#endif //GPIOCPP_GPIOWHEEL_H
