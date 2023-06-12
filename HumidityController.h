#ifndef HUMIDITYCONTROLLER_H
#define HUMIDITYCONTROLLER_H

#include <Arduino.h>
#include "PIDCalculator.h"
#include <Adafruit_AHTX0.h>
#include "Parameters.h"
#include "DigiPotX9Cxxx.h"

/*

  Controls the relative humidity using the PID controller

*/
class HumidityController
{
  public:

    // Initializes the class
    void begin(const float& Kp, const float& Ki, const float& Kd);

    // Starts the control in the manual mode
    void startManualMode(const float& potIntensity);

    // Starts the control in the automatic mode
    void startAutomaticMode(const float& relativeHumidity);

    // Stops the controller
    void stop();

    // Returns the current mode (0=manual, 1=automatic)
    int getMode(){ return mode; };

    // Sets the PID parameters
    void setParametersPID(const float& Kp, const float& Ki, const float& Kd) { pidPot.parametersPID(Kp, Ki, Kd); };

    // Returns the Kp parameter
    float getKp(){ return pidPot.getKp(); };

    // Returns the Ki parameter
    float getKi(){ return pidPot.getKi(); };

    // Returns the Kd parameter
    float getKd(){ return pidPot.getKd(); };

    // Returns the current value of the PID
    float getPID(){return PID;};

    // Returns the current relative humidity
    float getRelativeHumidity(){return humidity.relative_humidity;};

    // Returns the current fogger intensity
    float getpotIntensity(){return potIntensity;};

    // Runs the controller for a while
    void run();

  private:

    Adafruit_AHTX0             aht; // Humidity sensor   
    PIDCalculator           pidPot; // PID calculator
    int                   mode {0}; // 0 = manual mode, 1 = automatic mode
    float                PID {0.0}; // Current PID value
    sensors_event_t humidity, temp; // Variables to read the relative humidity and the temperature
    int               potIntensity; // Returns the current pontentiometer intensity
    DigiPot                digiPot; //Digital Potentiometer

};

#endif