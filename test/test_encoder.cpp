#include <iostream>

#include <stdio.h>
#include <thread>
#include <chrono>
#include <cmath>
#include <csignal>
#include <vector>
#include "robopi_drivers/robopi_drivers.h"

constexpr int enA = 21;
constexpr int enB = 13;
constexpr int in1 = 20;
constexpr int in2 = 16;
constexpr int in3 = 26;
constexpr int in4 = 19;
constexpr int encLeft = 2;
constexpr int encRight = 5;
using namespace robopi;

static volatile bool keepRunning = true;

void sigHandler(int signal)
{
    keepRunning = false;
}
int main(int argc, char *argv[])
{

    Encoder encoderLeft(encLeft,0);
    Encoder encoderRight(encRight,0);

    Gpio::instance()->setSignalFunc(SIGINT,sigHandler);
    const int nSamples = 20*5;
    const int sampleMs = 50;
    std::vector<float> ticksLeft(nSamples),ticksRight(nSamples);
    
    for(int i = 0; i < nSamples; i++)
    {
        ticksLeft[i] = encoderLeft.wheelTicks();
        ticksRight[i] = encoderRight.wheelTicks();

        std::this_thread::sleep_for (std::chrono::milliseconds(sampleMs));
    }

    for(int i = 0; i < nSamples; i++)
    {
        std::cout << "Ticks: " << ticksLeft[i] << " | " << ticksRight[i] << std::endl;

    }

    return 0;
}
