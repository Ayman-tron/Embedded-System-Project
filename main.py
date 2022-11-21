import time
import RPi.GPIO as GPIO
from definitions import *
from distance import *


# Creating a sensor objuct
sensor = Sensor()

GPIO.setmode(GPIO.BOARD)


def get_data():
    front = sensor.ultrasonic(TRIG_PIN_A, ECHO_PIN_A)
    return front


def main():
    try:
        while True:
            distance = get_data()
            if distance <= 7:
                print("Less")
            else:
                pass
            print(distance)
    except (KeyboardInterrupt, TypeError):
        GPIO.cleanup()
        print(" Cleanup successful")


main()
