#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
 

GPIO.setmode(GPIO.BCM)
 
GPIO_TRIGGER = 6
GPIO_ECHO = 12
 

GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)
 
def distance():

    GPIO.output(GPIO_TRIGGER, True)

    time.sleep(0.00001)
    GPIO.output(GPIO_TRIGGER, False)
 
    t_start = time.time()
    t_stop = time.time()
    # signal start
    while GPIO.input(GPIO_ECHO) == 0:
        t_start = time.time()

 
    # signal return
    while GPIO.input(GPIO_ECHO) == 1:
        t_stop = time.time()
 
    
    dT = t_stop - t_start
    # distance is given by v_sound (34300 cm/s) * dT
    # div by 2 as there and back
    distance = (dT * 34300) / 2
 
    return distance
 
if __name__ == '__main__':
    try:
        while True:
            abstand = distance()
            print ("Distance = %.1f cm" % abstand)
            time.sleep(1)
 
        
    except KeyboardInterrupt:
        print("Stopped by user")
        GPIO.cleanup()
