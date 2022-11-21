import time
import RPi.GPIO as GPIO
from definitions import *
from distance import *


# Creating a sensor objuct
sensor = Sensor()

GPIO.setmode(GPIO.BOARD)

# ================================================================ #
# =================== Ultrasonic Sensor PINS ===================== #
GPIO.setup(TRIG_PIN_A, GPIO.OUT)
GPIO.setup(ECHO_PIN_A, GPIO.IN)

#GPIO.setup(inPin, GPIO.IN)
GPIO.setup(inPin2, GPIO.OUT)
#GPIO.setup(ledPin, GPIO.OUT)

GPIO.output(inPin2, GPIO.LOW)


def get_data():
    front = sensor.ultrasonic(TRIG_PIN_A, ECHO_PIN_A)
    return front


def main():
    try:
        while True:
            #GPIO.output(ledPin, True)
            #time.sleep(0.3)
            #GPIO.output(ledPin, False)
            #time.sleep(0.3)

             distance = get_data()
        #     #readVal = GPIO.input(inPin)

        #     #time.sleep(0.5)
             if distance <= 7:
                 GPIO.output(inPin2, GPIO.HIGH)
                 #print("Less")
                 #print(readVal)

             else:
                 GPIO.output(inPin2, GPIO.LOW)
                 #print(readVal)
             #print(distance)
    except (KeyboardInterrupt, TypeError):
        GPIO.cleanup()
        print(" Cleanup successful")


main()
