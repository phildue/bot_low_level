#include <iostream>

#include <stdio.h>
#include "GpioWheel/GpioWheel.h"


constexpr int enA = 21;
constexpr int enB = 13;
constexpr int in1 = 20;
constexpr int in2 = 16;
constexpr int in3 = 26;
constexpr int in4 = 19;

#include <chrono>

int main(int argc, char *argv[])
{
    GpioWheel left(in1,in2,enA,0.5);
    GpioWheel right(in4,in3,enB,0.5);

    auto start = std::chrono::system_clock::now();

    while (std::chrono::duration_cast<std::chrono::seconds>((std::chrono::system_clock::now() - start)).count() < 5.0)
    {
        left.forward();
        right.backward();
    }
    left.stop();
    right.stop();


    return 0;
}