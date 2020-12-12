//
// Created by phil on 11.12.20.
//

#ifndef SRC_PIGPIO_H
#define SRC_PIGPIO_H

#include <memory>

namespace robopi {

    using GpioId = unsigned int;

    class PiGpio {
    public:
        static std::shared_ptr<PiGpio> instance();
        ~PiGpio();
    private:
        PiGpio();
        static std::shared_ptr<PiGpio> m_instance;

    };
}

#endif //SRC_PIGPIO_H
