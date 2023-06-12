#ifndef TEMPERATURE_CONTROLLER_H
#define TEMPERATURE_CONTROLLER_H

#include <Arduino.h>
#include <DallasTemperature.h>
#include <ClosedCube_HDC1080.h>


class TemperatureController
{
  public:
  
  
  ClosedCube_HDC1080 hdc1080;
  DallasTemperature *sensors;
  double error;
  double temp;
  double lastemp;
  double kP, kI, kD;      
  double P, I, D;
  double pid;
  bool stopFlag;
  
  double setPoint;
  long lastProcess;

  public:
    void  begin(DallasTemperature *sensors);
    void  run();
    float getTemperature();
    float getKP();
    float getKI();
    float getKD();
    void  setPID(float KP, float KI, float KD);
    void  setSetPoint(float setpoint);
    void  start();
    void  stop();
};

#endif 
