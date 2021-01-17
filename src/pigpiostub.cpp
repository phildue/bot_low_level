//
// Created by phil on 29.03.20.
//


#define PI_OUTPUT 1
#define PI_INITIALISED 0
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "pigpiostub.h"


static float pwmDutyCycle = 0;
static std::vector<float> pins = std::vector<float>(50);

int gpioInitialise(){
    return PI_INITIALISED;
}
void gpioSetMode(int pin,int sig)
{

}


void gpioWrite(int pin,int sig)
{
    if(sig != pins[pin])
    {
        std::cout << "Setting " << pin << ": " << sig << std::endl;
    }
    pins[pin] = sig;
}
void gpioPWM(int pin,float sig)
{
    if(sig != pins[pin])
    {
        std::cout << "Setting " << pin << ": " << sig << std::endl;
    }
    pins[pin] = sig;
}
int gpioRead(int pin)
{
    return 0;
}

void gpioTerminate()
{

}

float gpioGetPWMdutycycle(int pin)
{
    return pins[pin];
}

void gpioSetPWMfrequency(int pin,int freq)
{
}

void gpioDelay(int i) {
    std::this_thread::sleep_for(std::chrono::microseconds(i));
}
void gpioSetAlertFuncEx(int,void*,void*){}
void gpioSetTimerFuncEx(int,int,gpioTimerFuncEx_t,void*){}
void gpioSetISRFuncEx(int,int,int,gpioIsrFuncExt_t,void*){}



void gpioSetSignalFunc(int, gpioSignal_t){}
void gpioSetPullUpDown(int,int){}
