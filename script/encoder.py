#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
 

GPIO.setmode(GPIO.BCM)
 
GPIO_RIGHT = 5
GPIO_LEFT = 2
GPIO_ENC = GPIO_LEFT 

GPIO.setup(GPIO_ENC, GPIO.IN)

TICKS_TO_M = 0.006235294 
if __name__ == '__main__':
    try:
        stateRight = GPIO.input(GPIO_ENC)
        ticksRight = 0
        roundsRight = 0
        stateLeft = 0
        wheelsRight = 0
        while True:
            _stateRight = GPIO.input(GPIO_ENC)
            if _stateRight != stateRight:
                ticksRight += 1
                stateRight = _stateRight
                if ticksRight >= 20:
                   roundsRight += 1
                   ticksRight = 0
                if roundsRight % 4 == 0 and ticksRight == 4:
                   wheelsRight += 1
            print ("State: " + str(stateRight))
            print ("Ticks: " + str(ticksRight))
            print ("Rounds: " + str(roundsRight))
            print ("M: " + str((roundsRight*20+ticksRight)*TICKS_TO_M))
            time.sleep(0.05)
 
        
    except KeyboardInterrupt:
        print("Stopped by user")
        GPIO.cleanup()
