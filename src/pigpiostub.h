//
// Created by phil on 29.03.20.
//

#ifndef PIGPIOSTUB_H
#define PIGPIOSTUB_H

#define PI_OUTPUT 1
#define PI_INPUT 0
#define PI_INITIALISED 0
#define FALLING_EDGE 0
#define PI_PUD_UP 1
#define PI_ON 1
#define PI_OFF 0

typedef void (*gpioTimerFunc_t) (void);
typedef void (*gpioTimerFuncEx_t) (void *userdata);
typedef void (*gpioIsrFuncExt_t) (int,int,unsigned int, void *userdata);
typedef void (*gpioSignal_t) (int);

int gpioInitialise();
void gpioSetMode(int pin,int sig);

void gpioDelay(int i);
void gpioSetAlertFuncEx(int,void*,void*);
void gpioSetTimerFuncEx(int,int,gpioTimerFuncEx_t,void*);
void gpioSetISRFuncEx(int,int,int,gpioIsrFuncExt_t,void*);
void gpioWrite(int pin,int sig);
void gpioPWM(int pin,float sig);
int gpioRead(int pin);

void gpioTerminate();

float gpioGetPWMdutycycle(int pin);

void gpioSetPWMfrequency(int pin,int freq);
void gpioSetSignalFunc(int, gpioSignal_t);
void gpioSetPullUpDown(int,int);
#endif //PIGPIOSTUB_H
