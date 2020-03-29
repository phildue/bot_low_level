//
// Created by phil on 29.03.20.
//

#ifndef PIGPIOSTUB_H
#define PIGPIOSTUB_H

#define PI_OUTPUT 1
#define PI_INITIALISED 0
#include <vector>
static float pwmDutyCycle = 0;
static std::vector<float> pwms = std::vector<float>(50);
int gpioInitialise(){
    return PI_INITIALISED;
}
void gpioSetMode(int pin,int sig)
{

}


void gpioWrite(int pin,int sig)
{

}
void gpioPWM(int pin,float sig)
{
    pwms[pin] = sig;
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
    return pwms[pin];
}

void gpioSetPWMfrequency(int pin,int freq)
{
}
#endif //PIGPIOSTUB_H
