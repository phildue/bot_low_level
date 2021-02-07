#include <iostream>

#include <stdio.h>
#include "robopi_drivers/robopi_drivers.h"
#include <thread>

#include "robopi_drivers/pin_layout.h"

#include <chrono>
#include <cmath>
#include <vector>
#include <numeric>
using namespace robopi;

float mean(const std::vector<float>& sample, int idxFrom, int idxTo)
{
    return std::accumulate(sample.begin() + idxFrom,sample.begin()+idxTo,0)/ static_cast<float>(idxTo-idxFrom);
}

int main(int argc, char *argv[])
{
    float dT = 0.050;
    float kp = 0.001;
    float kd = 0.0;
    float ki = 0.0;
    MotorLn298Enc right(pins::in1,pins::in2,pins::enA,pins::encRight,dT,kp,kd,ki);
    MotorLn298Enc left(pins::in4,pins::in3,pins::enB,pins::encLeft,dT,kp,kd,ki);

    try {

        std::vector<float> velLeft,velRight;
        float steps = 15;
        velLeft.reserve(steps*2);
        velRight.reserve(steps*2);
        left.set(M_PI);
        right.set(M_PI);
       // left.set(0);
       // right.set(0);

        for(int i = 0; i < steps*2; i++)
        {
            std::this_thread::sleep_for (std::chrono::milliseconds(500));
            velLeft.push_back(left.velocity());
            velRight.push_back(right.velocity());
            std::cout << "Position: " << left.wheelTicks() << " | " << right.wheelTicks() << " ticks | ";
            std::cout << "Position: " << left.position() << " | " << right.position() << " rad | ";
            std::cout << "Velocity: " << velLeft[i] << " | " << velRight[i] << " rad/s | ";
            std::cout << "VelocityFiltered: " << mean(velLeft,0,i+1) << " | " << mean(velRight,0,i+1) << " rad/s" << std::endl;
        }
#ifdef RAMP
        for(int i = 0; i < 60; i++)
    {
        left.set((float)i/60.0f*MAX_VEL_DF_DC);
        right.set(-1.0f * (float)i/60.0f*MAX_VEL_DF_DC);
    	std::this_thread::sleep_for (std::chrono::milliseconds(500));
    	std::cout << "Position: " << left.position() << " | " << right.position() << "rad" << std::endl;
        std::cout << "Velocity: " << left.velocity() << " | " << right.velocity() << "rad/s" << std::endl;
    }
    for(int i = 60; i > 0; i--)
    {
        left.set((float)i/60.0f*MAX_VEL_DF_DC);
        right.set((float)-i/60.0f*MAX_VEL_DF_DC);
    	std::this_thread::sleep_for (std::chrono::milliseconds(500));
        std::cout << "Position: " << left.position() << " | " << right.position() << "rad" << std::endl;
        std::cout << "Velocity: " << left.velocity() << " | " << right.velocity() << "rad/s" << std::endl;
    }
#endif
        left.stop();
        right.stop();
        return 0;

    }catch(...)
    {
        left.stop();
        right.stop();
        return 1;
    }


}
