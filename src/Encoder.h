//
// Created by phil on 21.03.20.
//

#ifndef ENCODER_H
#define ENCODER_H

namespace robopi{

    class Encoder
    {
    public:
        Encoder(double ticksPerRad);

        long long wheelTicks() const {return _wheelTicks;}

        double position() const;

        void tick();

        void tickForward();
        
        void tickBackward();

        double ticks() const;

        void reset() {_wheelTicks = 0;};

        void setDirection(bool forward){_direction = forward;}



    protected:
        volatile long long _wheelTicks;
        bool _direction;
        const double _ticksToRad;


    };

}
#endif //ENCODER_H
