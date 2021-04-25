//
// Created by phil on 11.12.20.
//

#ifndef SRC_PIGPIO_H
#define SRC_PIGPIO_H

#include <memory>
#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#else

#define PI_OUTPUT 1
#define PI_INPUT 0
#define PI_INITIALISED 0
#define FALLING_EDGE 0
#define PI_PUD_UP 1
#define PI_ON 1
#define PI_OFF 0

typedef void (*eventFuncEx_t)(int event, int level, uint32_t tick, void *userdata);
typedef void (*gpioTimerFunc_t) (void);
typedef void (*gpioTimerFuncEx_t) (void *userdata);
typedef void (*gpioIsrFuncExt_t) (int,int,unsigned int, void *userdata);
typedef void (*gpioSignal_t) (int);
typedef void (*gpioSignalFunc_t) (int signum);

#endif
namespace robopi {


    using GpioId = unsigned int;

    class Gpio {
    public:
        static std::shared_ptr<Gpio> instance();
        int initialise();
        void delay(int msec);
        void setTimerFuncEx(int frqMs,gpioTimerFuncEx_t f, void *user);

        void setMode(int pin,int sig);

        void setAlertFuncEx(int pin,eventFuncEx_t func,void* params);
        void setTimerFuncEx(int pin,int time,gpioTimerFuncEx_t func,void* params);
        void setISRFuncEx(int pin, int upDown, float freq, gpioIsrFuncExt_t func, void *params);
        void write(int pin,int sig);
        void pWM(int pin,float sig);
        int read(int pin);
        void setSignalFunc(int signal, gpioSignalFunc_t* func);

        float getPWMdutycycle(int pin);

        void setPWMfrequency(int pin,int freq);
        void setSignalFunc(int, gpioSignal_t);
        void setPullUpDown(int,int);
        ~Gpio();
    private:
        int _timerCtr;
        Gpio();
        static std::shared_ptr<Gpio> m_instance;

    };
}

#endif //SRC_PIGPIO_H
