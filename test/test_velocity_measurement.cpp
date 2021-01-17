#include <iostream>
#include <fstream>
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
constexpr int encmotorLeft = 2;
constexpr int encmotorRight = 5;
using namespace robopi;

static volatile bool keepRunning = true;

void sigHandler(int signal)
{
    keepRunning = false;
}
const float dT = 0.001;
const float T = 20.0f;
const int nIterations = (int)(T/dT);
const int dT_ms =(int) (dT*1000.0f);
const float setPoint = 0.5f;

struct MotorLog : public TickHandler
{
    MotorLog(int size)
    {
        position.reserve(size);
        gpioTick.reserve(size);
        chronoUs.reserve(size);

        start = std::chrono::high_resolution_clock::now();
    }
    std::vector<float> position;
    std::vector<float> gpioTick;
    std::vector<float> chronoUs;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    void handleTick(uint32_t tick, long long wheelTicks) override
    {
        position.push_back(wheelTicks);
        gpioTick.push_back(tick);
        chronoUs.push_back(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count());

    }

};



int main(int argc, char *argv[])
{
    auto pigpio = PiGpio::instance();
    gpioSetSignalFunc(SIGINT,sigHandler);

    MotorLn298 motorRight(in1,in2,enA);
    MotorLn298 motorLeft(in4,in3,enB);
    Encoder encRight(encmotorRight,0);
    Encoder encLeft(encmotorLeft,0);
    
    auto logMotorRight = std::make_shared<MotorLog>(nIterations*10);
    auto logMotorLeft = std::make_shared<MotorLog>(nIterations*10); 

    encRight.subscribe(logMotorRight);
    encLeft.subscribe(logMotorLeft);

    std::vector<float> t;
    std::vector<float> ticksLeft,ticksRight;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < nIterations && keepRunning; i++)
    {
        motorRight.set(setPoint);
        motorLeft.set(setPoint);
        t.push_back(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count());
        ticksLeft.push_back(encLeft.wheelTicks());
        ticksRight.push_back(encRight.wheelTicks());
        std::this_thread::sleep_for (std::chrono::milliseconds(dT_ms));
    }
    std::cout << "Ctrl Loop Finished" << std::endl;

    std::cout << "Stopping Motors" << std::endl;    
    motorLeft.stop();
    motorRight.stop();
    
    std::ofstream logMotorsFile("log_motors.csv");
    
    logMotorsFile << "idx, pwm* [%],t_chrono left [us], t_gpio left [us],pos left [ticks],t_chrono right [us], t_gpio right [us],pos right [ticks]\n";
    
    for(int i = 0; i < logMotorLeft->position.size() && keepRunning; i++)
    {
        logMotorsFile << i << "," << setPoint  
        << "," << logMotorLeft->chronoUs[i] << "," << logMotorLeft->gpioTick[i] << "," << logMotorLeft->position[i]
        << "," << logMotorRight->chronoUs[i] << "," << logMotorRight->gpioTick[i] << "," << logMotorRight->position[i]
        << "\n";
    }

    logMotorsFile.close();


    std::ofstream logLoop("log_loop.csv");
    
    logLoop << "idx, pwm* [%],t_loop [us], pos left [ticks],pos right [ticks]\n";
    
    for(int i = 0; i < t.size() && keepRunning; i++)
    {
        logLoop << i << "," << setPoint  
        << "," << t[i] << "," << ticksLeft[i] << "," << ticksRight[i]
        << "\n";
    }

    logLoop.close();

    std::cout << "Done" << std::endl;

    

    return 0;
}
