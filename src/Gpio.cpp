//
// Created by phil on 11.12.20.
//

#include "Gpio.h"

#include <stdexcept>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
namespace robopi {

    std::shared_ptr<Gpio> Gpio::m_instance = nullptr;
#ifdef TARGET_ARDUINO
#elif COMPILE_FOR_PI
    Gpio::Gpio() {

        if (gpioInitialise() < 0) {
            throw std::runtime_error("pigpio initialisation failed\n");
        }
        _timerCtr = 0;
    }

    Gpio::~Gpio() {
        gpioTerminate();

    }

    std::shared_ptr<Gpio> Gpio::instance()
    {

        if(!m_instance){
            m_instance = std::shared_ptr<Gpio>(new Gpio);
        }

        return m_instance;
    }

    void Gpio::setTimerFuncEx(int frqMs,gpioTimerFuncEx_t f, void* user)
    {
        gpioSetTimerFuncEx(_timerCtr++,frqMs,f,user);
    }


    void Gpio::setMode(int pin, int sig) {
        gpioSetMode(pin,sig);
    }

    void Gpio::setAlertFuncEx(int pin, eventFuncEx_t func, void* params) {
        gpioSetAlertFuncEx(pin,func,params);
    }

    void Gpio::setTimerFuncEx(int pin, int time, gpioTimerFuncEx_t func, void *params) {
        gpioSetTimerFuncEx(pin,time,func,params);
    }

    void Gpio::setISRFuncEx(int pin, int freq, int timeout, gpioIsrFuncExt_t func, void *params) {
        gpioSetISRFuncEx(pin,freq,timeout,func,params);
    }

    void Gpio::write(int pin, int sig) {
        gpioWrite(pin,sig);
    }

    void Gpio::pWM(int pin, float sig) {
        gpioPWM(pin,sig);
    }

    int Gpio::read(int pin) {
        return gpioRead(pin);
    }

    float Gpio::getPWMdutycycle(int pin) {
        return gpioGetPWMdutycycle(pin);
    }

    void Gpio::setPWMfrequency(int pin, int freq) {
        gpioSetPWMfrequency(pin,freq);
    }

    void Gpio::setSignalFunc(int pin, gpioSignal_t signal) {
        gpioSetSignalFunc(pin,signal);
    }

    void Gpio::setPullUpDown(int pin, int upDown) {
        gpioSetPullUpDown(pin,upDown);
    }

    int Gpio::initialise() {
        return gpioInitialise();
    }

    void Gpio::delay(int msec) {
        gpioDelay(msec);
    }
    void Gpio::setSignalFunc(int signal, gpioSignalFunc_t* func) {
        gpioSetSignalFunc(signal,func);
    }

#else
    static float pwmDutyCycle = 0;
    static std::vector<float> pins = std::vector<float>(50);

    Gpio::Gpio() {


        _timerCtr = 0;
    }

    Gpio::~Gpio() {

    }

    std::shared_ptr<Gpio> Gpio::instance()
    {

        if(!m_instance){
            m_instance = std::shared_ptr<Gpio>(new Gpio);
        }

        return m_instance;
    }

    void Gpio::setTimerFuncEx(int frqMs,gpioTimerFuncEx_t f, void* user)
    {
    }


    void Gpio::setMode(int pin, int sig) {
    }

    void Gpio::setAlertFuncEx(int pin, eventFuncEx_t func, void* params) {
    }

    void Gpio::setTimerFuncEx(int pin, int time, gpioTimerFuncEx_t func, void *params) {
    }

    void Gpio::setISRFuncEx(int pin, int upDown, float freq, gpioIsrFuncExt_t func, void *params) {
    }

    void Gpio::write(int pin, int sig) {
        if(sig != pins[pin])
        {
            std::cout << "Setting " << pin << ": " << sig << std::endl;
        }
        pins[pin] = sig;    }

    void Gpio::pWM(int pin, float sig) {
        if(sig != pins[pin])
        {
            std::cout << "Setting " << pin << ": " << sig << std::endl;
        }
        pins[pin] = sig;    }

    int Gpio::read(int pin) {
        return pins[pin];
    }

    float Gpio::getPWMdutycycle(int pin) {
        return pins[pin];
    }

    void Gpio::setPWMfrequency(int pin, int freq) {
    }

    void Gpio::setSignalFunc(int pin, gpioSignal_t signal) {
    }

    void Gpio::setPullUpDown(int pin, int upDown) {
    }

    int Gpio::initialise() {
    }

    void Gpio::delay(int msec) {
        std::this_thread::sleep_for(std::chrono::microseconds(msec));
    }

    void Gpio::setSignalFunc(int signal, gpioSignalFunc_t* func) {

    }

#endif
}