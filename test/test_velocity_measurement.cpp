#include <iostream>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <cmath>
#include <csignal>
#include <vector>
#include "bot_low_level/bot_low_level.h"
#include "pin_layout.h"


using namespace robopi;


constexpr double US_TO_S = (1.0f/(1000.0f*1000.0f));
constexpr double COUNT_TO_RAD = M_PI/5.0f;
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

struct MotorLog //: public TickHandler
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

    void handleTick(uint32_t tick, long long wheelTicks) //override
    {
        position.push_back(wheelTicks);
        gpioTick.push_back(tick);
        chronoUs.push_back(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count());

    }

};



int main(int argc, char *argv[])
{
    auto pigpio = Gpio::instance();
    pigpio->setSignalFunc(SIGINT,sigHandler);

    MotorLn298 motorRight(pins::in1,pins::in2,pins::enA);
    MotorLn298 motorLeft(pins::in4,pins::in3,pins::enB);
    Encoder encRight(pins::encRight,0);
    Encoder encLeft(pins::encLeft,0);
    LuenbergerObserver observerLeft(5.0,7.5),observerRight(5.0,7.5);
    SlidingAverageFilter avgFilterLeft(100),avgFilterRight(100);


    auto logMotorRight = std::make_shared<MotorLog>(nIterations*10);
    auto logMotorLeft = std::make_shared<MotorLog>(nIterations*10); 

//    encRight.subscribe(logMotorRight);
//    encLeft.subscribe(logMotorLeft);

    std::vector<float> t(nIterations);
    std::vector<float> ticksLeft(nIterations),ticksRight(nIterations);
    std::vector<float> vMeanLeft(nIterations),vMeanRight(nIterations);
    std::vector<float> vObsLeft(nIterations),vObsRight(nIterations);

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < nIterations && keepRunning; i++)
    {
        //motorRight.set(setPoint);
        motorLeft.set(setPoint);
        t[i]  = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count();
        ticksLeft[i] = encLeft.wheelTicks();
        ticksRight[i] = encRight.wheelTicks();
        if(i > 0)
        {
            double dt = static_cast<double>((t[i] - t[i-1])) * US_TO_S;
            double dPosLeft = static_cast<double>(ticksLeft[i]) * COUNT_TO_RAD;
            double dPosRight = static_cast<double>(ticksRight[i]) * COUNT_TO_RAD;

            vObsLeft[i] = observerLeft.estimate(dPosLeft,dt);
            vObsRight[i] = observerRight.estimate(dPosRight,dt);
            vMeanLeft[i] = avgFilterLeft.estimate(dPosLeft,dt);
            vMeanRight[i] = avgFilterRight.estimate(dPosRight,dt);
            
        }else{
             vObsLeft[i] = 0;
             vObsRight[i] = 0;
             vMeanLeft[i] = 0;
             vMeanRight[i] = 0;;
            
        }
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
    
    logLoop << "idx, pwm* [%],t_loop [us],pos left [ticks],pos right [ticks],v left obs [rad/s],v left mean [rad/s],v right obs [rad/s],v right mean [rad/s]\n";
    
    for(int i = 0; i < nIterations && keepRunning; i++)
    {
        logLoop << i << "," << setPoint  
        << "," << t[i] << "," << ticksLeft[i] << "," << ticksRight[i] << "," << vMeanLeft[i] << "," << vObsLeft[i] << "," << vMeanRight[i] << "," << vObsRight[i]
        << "\n";
    }

    logLoop.close();

    std::cout << "Done" << std::endl;

    

    return 0;
}
