//
// Created by phil on 11.12.20.
//

#ifndef SRC_PIGPIO_H
#define SRC_PIGPIO_H
namespace pi_ln298n {

    using GpioId = unsigned int;

    class PiGpio {
    public:
        PiGpio();

        ~PiGpio();
    };
}

#endif //SRC_PIGPIO_H
