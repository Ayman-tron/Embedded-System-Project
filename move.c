// Author: Thomas Habitch
#include <Stepper.h>
// Include Stepper Library
// Stepper Motor X
const int stepPinx = 2; // X.STEP drive motor
const int dirPinx = 5;  // X.DIR drive motor
// Stepper Motor Z
const int stepPinz = 12; // drive motor
const int dirPinz = 13;  // drive motor

// driving data
double stepsF = 0;
double stepsF1 = 0;
double stepsF2 = 0;
double stepsF3 = 0;
double stepsRev = 0;
double stepsRev1 = 0;
double corstepsR = 40;
double corstepsL = 100;
double corstepsL1 = 100;
double corstepsL2 = 5;
double stepsL = 273;
double stepsL1 = 158;
double stepsR = 273;
double stepsR1 = 158;
double delayT = 0;
int delayUpper = 5000;
int delayUpper2 = 5000;
int delayLower = 250;
int delayVal = 9500;
double proportionalSteps = 0;
double delayStart;

// acceleration/deacceleration variables
float accelKi = 0;
float accelKd = 0;
float accelKp = .98;
int target = 250;
float deltaS;
float deds;
int eintegral;
float currentStep;
float previousStep;
int e = 0;
int eprev = 0;
float acceldedt = 0;
float accel;

// Centering Variables
float centerKi = 0;
float centerKd = 0;
float centerKp = 0.92;
double lcsteps = 0;
double rcsteps = 100;
float center;
float centerv;
float currente = 0;
float previouse = 0;
int cumerr = 0;
float rateerr = 0;
int centervp = 0;
int targetc = 45;
int targetb = 56;

// IR interrupt variables
int interCheckR = 0;
int interCheckL = 0;
int zstate = 0;
int xstate = 0;
int correcthap = 0;

// distance calculation values
// Steps for complete motor rotation
int motorRotate = 400;
// distance travel values = mm *stepsPermm
int distance = 0;
double distancemm = 0;
int circum = 227;
double stepsPermm = 3.552;

int analogPin = A15;

int val = 0;

void setup()
{
    // Sets the two pins as Outputs
    pinMode(stepPinx, OUTPUT);
    pinMode(dirPinx, OUTPUT);
    pinMode(stepPinz, OUTPUT);
    pinMode(dirPinz, OUTPUT);

    // Serial for Sensor Testing
    Serial.begin(115200); // Intialize terminal serial port
    delay(5000);
    pulse();
}
void loop()
{

    val = analogRead(analogPin); // read the input pin

    if (val > 600)
    {
        FGO();
    }

    if (val < 600)
    {
        digitalWrite(dirPinz, HIGH); // Changes the rotations direction
        digitalWrite(dirPinx, HIGH); // Changes the rotations direction
        for (int x = 0; x < 5; x++)
        {
            digitalWrite(stepPinz, HIGH);
            digitalWrite(stepPinx, HIGH);
            delayMicroseconds(750);
            digitalWrite(stepPinx, LOW);
            digitalWrite(stepPinz, LOW);
            delayMicroseconds(750);
        }
    }
}

void FGO()
{
    zstate = 1;
    xstate = 1;
    interCheckR = 0;
    interCheckL = 0;
    accelKp = .9998;
    accel = 750;
    // drive
    for (int x = 0; x < 700; x++)
    {
        digitalWrite(stepPinx, HIGH);
        digitalWrite(stepPinz, HIGH);
        delayMicroseconds(accel);
        digitalWrite(stepPinx, LOW);
        digitalWrite(stepPinz, LOW);
        delayMicroseconds(accel);
        interCheckL = 0;
        interCheckR = 0;
        delayT = accel;
        currentStep = x;
        // delta
        deltaS = ((float)(currentStep - previousStep));
        previousStep = currentStep;
        // error
        e = delayUpper - delayT;
        // derivative
        deds = (e - eprev) / (deltaS);
        eprev = e;
        // integral
        eintegral = eintegral + e * deltaS;
        // control
        accel = accelKp * e + accelKd * deds + accelKi * eintegral;
        accel = 5000 - accel;
    }
    delay(10000);
}

void pulse()
{
    accel = 10000;

    digitalWrite(dirPinz, HIGH); // Changes the rotations direction
    digitalWrite(dirPinx, HIGH); // Changes the rotations direction

    // drive
    for (int x = 0; x < 2; x++)
    {
        digitalWrite(stepPinx, HIGH);
        digitalWrite(stepPinz, HIGH);
        delayMicroseconds(accel);
        digitalWrite(stepPinx, LOW);
        digitalWrite(stepPinz, LOW);
        delayMicroseconds(accel);
        delayT = accel;
        currentStep = x;
        // delta
        deltaS = ((float)(currentStep - previousStep));
        previousStep = currentStep;
        // error
        e = delayT - delayLower;
        // derivative
        deds = (e - eprev) / (deltaS);
        eprev = e;
        // integral
        eintegral = eintegral + e * deltaS;
        // control
        accel = accelKp * e + accelKd * deds + accelKi * eintegral + 500;
    }
}
