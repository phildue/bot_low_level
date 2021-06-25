//
// Created by phil on 11.12.20.
//

#ifndef SRC_PIGPIO_H
#define SRC_PIGPIO_H

#include "types.h"
#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#elif defined(COMPILE_FOR_ARDUINO)

#define PI_OUTPUT 1
#define PI_INPUT 0
#define PI_INITIALISED 0
#define FALLING_EDGE 0
#define PI_PUD_UP 1
#define PI_ON 1
#define PI_OFF 0

typedef void (*gpioAlertFuncEx_t)();
typedef void (*gpioTimerFunc_t) (void);
typedef void (*gpioTimerFuncEx_t) (void *userdata);
typedef void (*gpioISRFuncEx_t) (int,int,unsigned int, void *userdata);
typedef void (*gpioSignalFunc_t) (int signum);


#else

#define PI_OUTPUT 1
#define PI_INPUT 0
#define PI_INITIALISED 0
#define FALLING_EDGE 0
#define PI_PUD_UP 1
#define PI_ON 1
#define PI_OFF 0

typedef void (*gpioAlertFuncEx_t)(int event, int level, unsigned int tick, void *userdata);
typedef void (*gpioTimerFunc_t) (void);
typedef void (*gpioTimerFuncEx_t) (void *userdata);
typedef void (*gpioISRFuncEx_t) (int,int,unsigned int, void *userdata);
typedef void (*gpioSignalFunc_t) (int signum);

#endif
namespace robopi {


    class System {
    public:
        virtual void sleep(int msec){};

        virtual void setMode(int pin,int sig){};

        virtual void write(int pin,int sig){};
        virtual void pWM(int pin,int sig){};
        virtual int read(int pin){return 0;};

        virtual double getPWMdutycycle(int pin){return 0.0f;};

        virtual void setPWMfrequency(int pin,int freq){};
        virtual void setPullUpDown(int,int){};
    private:

    };
}

#endif //SRC_PIGPIO_H
