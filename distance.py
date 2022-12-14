from definitions import *
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)


class Sensor:
    def ultrasonic(self, TRIG_PIN, ECHO_PIN):
        GPIO.output(TRIG_PIN, 1)
        time.sleep(1E-6)
        GPIO.output(TRIG_PIN, 0)

        while GPIO.input(ECHO_PIN) == 0:
            pass
        # Gives us the system time (starting the stopwatch)
        echoStartTime = time.time()
        while GPIO.input(ECHO_PIN) == 1:
            pass
        # Stopping the stopwatch
        echoStopTime = time.time()
        pingTravelTime = echoStopTime - echoStartTime

        distance = 34300 * (pingTravelTime/2)

        # sensor requires a delay before sending and receiving the ping
        time.sleep(0.2)
        # Rounding to two decimal point in cm
        return (round(distance, 2))
