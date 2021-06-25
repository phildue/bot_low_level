//
// Created by phil on 21.03.20.
//

#ifndef MOTOR_LN298_ENC_H
#define MOTOR_LN298_ENC_H
#include "System.h"
#include "Encoder.h"
#include "MotorLn298.h"

namespace robopi{
    constexpr double MAX_VEL_DF_DC = 16.755;//rad_s


    class VelocityEstimator {
        public:
            virtual double estimate(double pos, double dT) = 0;
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
            double estimate(double pos, double dT) override;
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

            double estimate(double pos, double dT) override;
            double& P() {return _kp;}
            double& I() {return _ki;}
        private:

            double _pos;
            double _velIntegr;
            double _v,_kp,_ki;
 
    };


    class MotorVelocityControl
    {
    public:
        MotorVelocityControl(MotorLn298* motor,Encoder* encoder, VelocityEstimator* velEstimator,
            double kp, double ki, double kd,double errIMax, double vMax = MAX_VEL_DF_DC):
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
        _dutySet(0.0),
        _vMax(vMax),
        _errIntegrMax(errIMax){
            
            
        }

        /**
         * Pass set point
         * @param velocity in [rad/s]
         */
        void set(double velocity);

        /**
         * Perform control loop iteration
         * @param dT time difference since last update [s]
         */
        void update(double dT);

        /**
         * Stop motor. Reset internals as well as encoder ticks.
         */
        void stop();

        /**
         * Get angular position from encoder
         * @return angle in [rad]
         */
        double position() const {return _encoder->position();}

        /**
         * Get position from encoder
         * @return position in [wheel ticks]
         */
        long long wheelTicks() const {return _encoder->wheelTicks();}


        /**
       * Get filtered angular velocity
       * @return velocity in [rad/s]
       */
        const double& velocity() const {return _velocityActual;}

        /**
       * Get set point angular velocity
       * @return velocity in [rad/s]
       */
        const double& velocitySet() const {return _velocitySet;}



        /**
       * Get computed error
       * @return error in [rad/s]
       */
        const double& error() { return _errLast;}

        /**
       * Get set point to pwm
       * @return pwm duty cycle in [%]
       */
        double dutySet() { return _dutySet*100.0;}

        const MotorLn298* motor() const {return _motor;}
        const Encoder* encoder() const {return _encoder;}
        const VelocityEstimator* velocityEstimator() const {return _velEstimator;}

        double& P(){return _kp;}
        double& I(){return _ki;}
        double& D(){return _kd;}
    protected:

        double _kp,_ki,_kd;
        const double _vMax;
        double _errLast,_errIntegr;
        MotorLn298* _motor;
        Encoder* _encoder;
        VelocityEstimator* _velEstimator;
        double _velocitySet, _dutySet;
        double _velocityActual;
        double _errIntegrMax;

        void clamp(double* value, double max, double min);
    };

}
#endif //GPIOCPP_GPIOWHEEL_H
