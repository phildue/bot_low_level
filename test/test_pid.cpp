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
constexpr int encLeft = 2;
constexpr int encRight = 5;
using namespace robopi;

static volatile bool keepRunning = true;

void sigHandler(int signal)
{
    keepRunning = false;
}
const float dT = 0.001;
const float T = 30.0f;
const int nIterations = (int)(T/dT);
const int dT_ms =(int) (dT*1000.0f);
const float setPoint = M_2_PI*8.0f*5.0f;

struct MotorLog
{
    MotorLog(int size)
    {
        dutySet.resize(size);
        velMeasured.resize(size);
        position.resize(size);
        error.resize(size);
        t.resize(size);

    }
    std::vector<float> dutySet;
    std::vector<float> velMeasured;
    std::vector<float> position;
    std::vector<float> error;
    std::vector<unsigned long> t;
};

int main(int argc, char *argv[])
{
    auto pigpio = PiGpio::instance();
    gpioSetSignalFunc(SIGINT,sigHandler);
    float kp = 0.009;//0.2;
    float kd = 0.00;
    float ki = 0.00;
    uint16_t filterSize = 5000;

    auto motorRight = std::make_shared<MotorLn298>(in1,in2,enA);
    auto encoderRight = std::make_shared<Encoder>(encRight);
    //auto filterRight = std::make_shared<SlidingAverageFilter>(filterSize);
    auto filterRight = std::make_shared<LuenbergerObserver>(5.0,7.5);

    auto controlRight = std::make_shared<MotorVelocityControl>(motorRight,encoderRight,filterRight,kp,ki,kd);

    auto motorLeft = std::make_shared<MotorLn298>(in4,in3,enB);
    auto encoderLeft = std::make_shared<Encoder>(encLeft);
    //auto filterLeft = std::make_shared<SlidingAverageFilter>(filterSize);
    auto filterLeft = std::make_shared<LuenbergerObserver>(5.0,7.5);

    auto controlLeft = std::make_shared<MotorVelocityControl>(motorLeft,encoderLeft,filterLeft,kp,ki,kd);
   
    MotorLog logLeft(nIterations),logRight(nIterations); 
    
    controlRight->set(setPoint);
    controlLeft->set(setPoint);



    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < nIterations && keepRunning; i++)
    {
        unsigned long t = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count());
        controlRight->update(t);

        t = static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count());
        controlLeft->update(t);

        logRight.dutySet[i] = controlRight->dutySet();
        logRight.velMeasured[i] = controlRight->velocity();
        logRight.position[i] = controlRight->wheelTicks();
        logRight.error[i] = controlRight->error();
        logRight.t[i] = t;
      
        logLeft.dutySet[i] = controlLeft->dutySet();
        logLeft.velMeasured[i] = controlLeft->velocity();
        logLeft.position[i] = controlLeft->wheelTicks();
        logLeft.error[i] = controlLeft->error();
        logLeft.t[i] = t;
      
        std::this_thread::sleep_for (std::chrono::milliseconds(dT_ms));
    }
    std::cout << "Ctrl Loop Finished" << std::endl;

    std::cout << "Stopping Motors" << std::endl;    
    motorRight->stop();
    motorLeft->stop();
    
    std::ofstream myFile("log.csv");
    
    myFile << "idx, V* [rad/s], Motor Left,pwm left [%],V~ left [rad/s],pos left [ticks],e left [rad/s], Motor Right,pwm right [%],V~ right [rad/s],pos right [ticks],e right [rad/s]\n";
    
    for(int i = 0; i < nIterations && keepRunning; i++)
    {
        myFile << logLeft.t[i] << "," << setPoint 
        << "," << "" << "," << logLeft.dutySet[i] << "," << logLeft.velMeasured[i] << "," << logLeft.position[i] << "," << logLeft.error[i] 
        << "," << "" << "," << logRight.dutySet[i] << "," << logRight.velMeasured[i] << "," << logRight.position[i] << "," << logRight.error[i] 
        << "\n";
    }

    myFile.close();

    std::cout << "Done" << std::endl;

    

    return 0;
}
