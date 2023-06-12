#include "HumidityController.h"

void HumidityController::begin(const float& Kp, const float& Ki, const float& Kd)
{
  // Initializing the humidity sensor
  if (! aht.begin()) {
    while (1) delay(10);
  }

  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

  // Initializing the potentiometer
  digiPot.begin(parameters::pinPot1, parameters::pinPot2, parameters::pinPot3);

  //Reset the initial value of the potentiometer
  digiPot.reset();

  // Setting parameters kP, kI and kD of the PID calculator
  pidPot.parametersPID(Kp, Ki, Kd);

  // Initializes stopped
  stop();
}

void HumidityController::startManualMode(const float& potIntensity)
{
  mode = 0;

  this->potIntensity = potIntensity;

  //The system will work with the determined value, throughout the process
  digiPot.set(potIntensity);

}

void HumidityController::startAutomaticMode(const float& relativeHumidity)
{
  mode = 1;

  //The module takes the relativeHumidity setpoint for the process and uses to determinated the PID value
  pidPot.setSetPoint(relativeHumidity);
}


void HumidityController::stop()
{
  digiPot.set(0);
}


void HumidityController::run()
{
  // Reading the humidity
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  
  if ( mode == 0 )
  {
    // Do nothing
  }
  else
  {
    // Calculating the PID for Fogger
    PID = pidPot.run(humidity.relative_humidity);
    
    if( PID == 0.0 )
    {
      potIntensity = 0;
      digiPot.set(potIntensity);

    } else if (PID < 0 ) 
    {
      /* If the PID value is negative, it means we need to turn the fogger On
      so we map the PID value to (0, 100) range. */
      potIntensity = map(PID, -100,0,99,0);
      digiPot.set(potIntensity);



    }else if (PID > 0 )
    {
      potIntensity = 0;
      digiPot.set(potIntensity);
    }
  }

  digiPot.set(potIntensity);
}