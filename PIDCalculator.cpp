#include "PIDCalculator.h"
#include <Arduino.h>

void PIDCalculator::parametersPID(const float& kP, const float& kI, const float& kD)
{
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
}

void PIDCalculator::setSetPoint(const float& setPoint)
{
 this -> setPoint = setPoint;
}

float PIDCalculator::run(const float& sensorValue)
{ 
  error = sensorValue-setPoint; 
  float deltaTime = (millis()-lastTime)/1000.0;
  lastTime = millis();
  P = error * kP;
  I = I + ((error * kI) * deltaTime);
  D = (error - error0) * kD / deltaTime;
  PID = P + I + D;
  return PID;
}