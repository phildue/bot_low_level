#include <iostream>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <cmath>
#include <csignal>
#include <vector>
#include "bot_low_level/bot_low_level.h"
#include "csv.h"

constexpr float US_TO_S = (1.0f/(1000.0f*1000.0f));
constexpr float COUNT_TO_RAD = M_PI/5.0f;
constexpr float TICKS_US_TO_RAD_S = COUNT_TO_RAD / US_TO_S;
constexpr float RAD_S_TO_TICKS_US = 1.0f/TICKS_US_TO_RAD_S;


constexpr int enA = 21;
constexpr int enB = 13;
constexpr int in1 = 20;
constexpr int in2 = 16;
constexpr int in3 = 26;
constexpr int in4 = 19;
constexpr int encmotorLeft = 2;
constexpr int encmotorRight = 5;
using namespace robopi;


int main(int argc, char *argv[])
{
    auto pigpio = Gpio::instance();

    LuenbergerObserver observerLeft(5.0,7.5),observerRight(5.0,7.5);
    SlidingAverageFilter avgFilterLeft(100),avgFilterRight(100);

    std::map<std::string, std::vector<float>> encoderLog = read_csv("data/log_loop.csv");

    const auto& t = encoderLog["t_loop [us]"];
    const auto& posLeft = encoderLog["pos left [ticks]"];
    const auto& posRight = encoderLog["pos right [ticks]"];

    std::vector<float> vLeftObserver,vLeftAvg,vRightObserver,vRightAvg;
    for (std::vector<float> v : { vLeftObserver,vLeftAvg,vRightObserver,vRightAvg })
    {
        v.reserve(t.size());
    }
    for(int i = 1; i < t.size(); i++)
    {
        float dT = (t[i] - t[i-1]) * US_TO_S;

        float vObserverLeft = observerLeft.estimate(posLeft[i]*COUNT_TO_RAD,dT);
        float vAvgLeft = avgFilterLeft.estimate(posLeft[i]*COUNT_TO_RAD,dT);
        float vObserverRight = observerRight.estimate(posRight[i]*COUNT_TO_RAD,dT);
        float vAvgRight = avgFilterRight.estimate(posRight[i]*COUNT_TO_RAD,dT);

        vLeftObserver.push_back(vObserverLeft);
        vLeftAvg.push_back(vAvgLeft);
        vRightObserver.push_back(vObserverRight);
        vRightAvg.push_back(vAvgRight);
    }

    std::ofstream logMotorsFile("log_velocity_filter.csv");
    
    logMotorsFile << "idx, t [us], v avg left [rad/s], v obs left [rad/s],v avg right [rad/s], v obs right [rad/s]\n";
    
    for(int i = 0; i < t.size(); i++)
    {
        logMotorsFile << i << "," << t[i]
        << "," << vLeftAvg[i] << "," << vLeftObserver[i]
        << "," << vRightAvg[i] << "," << vRightObserver[i]
        << "\n";
    }
    std::cout << "Wrote " << t.size() << " lines" << std::endl;
    logMotorsFile.close();


    std::cout << "Done" << std::endl;


    return 0;
}
