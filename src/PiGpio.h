//
// Created by phil on 11.12.20.
//

#ifndef SRC_PIGPIO_H
#define SRC_PIGPIO_H

#include <memory>
#ifdef COMPILE_FOR_PI
#include <pigpio.h>
#else
#include <pigpiostub.h>
#endif
namespace robopi {

    using GpioId = unsigned int;

    class PiGpio {
    public:
        static std::shared_ptr<PiGpio> instance();
        void setTimerFuncEx(int frqMs,gpioTimerFuncEx_t f, void *user);
        ~PiGpio();
    private:
        int _timerCtr;
        PiGpio();
        static std::shared_ptr<PiGpio> m_instance;

    };
}

#endif //SRC_PIGPIO_H
