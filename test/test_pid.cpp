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
    auto pigpio = PiGpio::instance();
    gpioSetSignalFunc(SIGINT,sigHandler);
    float dT = 0.05;
    float kp = 0.01;//0.2;
    float kd = 0.0;
    float ki = 0.00;
    MotorLn298Enc right(in1,in2,enA,encRight,dT,kp,kd,ki);
    MotorLn298Enc left(in4,in3,enB,encLeft,dT,kp,kd,ki);
    float setPoint = M_PI_4;
    const float T = 20.0f;
    const int nIterations = (int)(T/dT);
    const int dT_ms =(int) (dT*1000.0f);

    std::vector<float> dutySet(nIterations);
    std::vector<float> velMeasured(nIterations);
    std::vector<float> position(nIterations);
    std::vector<float> error(nIterations);

    for(int i = 0; i < nIterations && keepRunning; i++)
    {
        right.set(setPoint);
        dutySet[i] = right.dutySet();
        velMeasured[i] = right.velocity();
        position[i] = right.wheelTicks();
        error[i] = right.error();
        std::this_thread::sleep_for (std::chrono::milliseconds(dT_ms));
    }
    std::cout << "Ctrl Loop Finished" << std::endl;

    std::cout << "Stopping Motors" << std::endl;    
    left.stop();
    right.stop();

    for(int i = 0; i < nIterations && keepRunning; i++)
    {
        std::cout << "V* = " << setPoint << " rad/s | pwm = "<< dutySet[i] << " % | V = " << velMeasured[i] << " rad/s | pos = " << position[i] << "ticks | e = " << error[i] << " rad/s" << std::endl;
    }
    std::cout << "Print Loop Finished" << std::endl;



    

    return 0;
}
