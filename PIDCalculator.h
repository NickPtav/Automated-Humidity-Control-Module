#ifndef  PIDCAlCULATOR_H
#define  PIDCALCULATOR_H

class PIDCalculator
{
  public:
    // Sets the values of the PID parameters from the user
    void parametersPID(const float& kP, const float& kI, const float& kD);

    // Sets the SetPoint value
    void setSetPoint(const float& setPoint);

    // Returns the kP parameter
    float getKp(){return kP;};

    // Returns the kI parameter
    float getKi(){return kI;};

    // Returns the kD parameter
    float getKd(){return kD;};

    // Runs the PID maths
    float run(const float& sensorValue);

  private:
    float setPoint;
    float kP = 8.401651;
    float kI = 0.00034;
    float kD = 0.00034;
    float error = 0.0 ;
    float error0 = error;
    float lastTime = 0.0; // milliseconds

    float  P = 0.0;
    float  I = 0.0;
    float  D = 0.0;
    float  PID = 0.0;
};

#endif