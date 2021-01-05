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

int main(int argc, char *argv[])
{
   
    Encoder encoder(encLeft,500);
    const int nSamples = 100;
    const int sampleMs = 50;
    std::vector<float> wheelTicks(nSamples);
    std::vector<float> velocity(nSamples);
    
    for(int i = 0; i < nSamples; i++)
    {
        wheelTicks[i] = encoder.wheelTicks();
        velocity[i] = encoder.velocity();

        std::this_thread::sleep_for (std::chrono::milliseconds(sampleMs));
    }

    for(int i = 0; i < nSamples; i++)
    {
        std::cout << "Ticks: " << wheelTicks[i] << " | V = " << velocity[i] << std::endl;

    }

    return 0;
}
