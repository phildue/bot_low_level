#include <iostream>

#include <stdio.h>
#include "robopi_drivers/robopi_drivers.h"
#include <thread>

constexpr int enA = 21;
constexpr int enB = 13;
constexpr int in1 = 20;
constexpr int in2 = 16;
constexpr int in3 = 26;
constexpr int in4 = 19;

#include <chrono>
#include <cmath>
#include <vector>
#include <numeric>
using namespace robopi;
constexpr float COUNT_TO_RAD = M_PI/10;

float mean(const std::vector<float>& sample, int idxFrom, int idxTo)
{
    return std::accumulate(sample.begin() + idxFrom,sample.begin()+idxTo,0)/ static_cast<float>(idxTo-idxFrom);
}

int main(int argc, char *argv[])
{
/*    MotorLn298Enc right(in1,in2,enA,2);
    MotorLn298Enc left(in4,in3,enB,5);
    MotorLn298Enc& motor = left;
    try {
        const int nSteps = 100;
        std::vector<float> meanVel(nSteps);
        for (int n = 0; n < nSteps; n++)
        {
            float nSecondsWindow = 5;
            float sampleTime = 0.05;
            int nSamples = (int)(nSecondsWindow/sampleTime);
            std::vector<float> vel(nSamples);
            float setVelocity = (float)n/(float)nSteps * MAX_VEL_DF_DC;
            motor.set(setVelocity);

            long long ticksLast = 0;
            for(int i = 0; i < nSamples; i++)
            {
                std::this_thread::sleep_for (std::chrono::milliseconds((int)(sampleTime*1000)));
                auto ticks = motor.wheelTicks();
                float deltaTicks = static_cast<float>(ticks - ticksLast);

                if(deltaTicks < 1000)//in case of overflow skip computation for this time
                {
                    vel[i] = (deltaTicks*COUNT_TO_RAD)/sampleTime;
                }else{
                    vel[i] = vel[i-1];
                }

                ticksLast = ticks;
            }
            meanVel[n] = mean(vel,0,nSamples);
            std::cout << "Set Velocity: " << setVelocity << " rad/s";

            std::cout << "Average Velocity: " << meanVel[n] << " rad/s" << std::endl;

        }

        left.stop();
        right.stop();

        return 0;

    }catch(...)
    {
        left.stop();
        right.stop();
        return 1;
    }

*/
    return 0;
}
