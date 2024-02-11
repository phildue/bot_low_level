#include <iostream>

#include <stdio.h>
#include <thread>
#include <chrono>
#include <cmath>
#include <csignal>
#include <vector>
#include "bot_low_level/bot_low_level.h"

#include "pin_layout.h"
using namespace robopi;

static volatile bool keepRunning = true;

void sigHandler(int signal)
{
    keepRunning = false;
}
int main(int argc, char *argv[])
{
   
    Encoder encoderLeft(pins::encLeft,0);
    Encoder encoderRight(pins::encRight,0);

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
