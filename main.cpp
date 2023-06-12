#include "HumidityController.h"
#include "TemperatureController.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ClosedCube_HDC1080.h>
#include "Parameters.h"
#include <CommunicationControl.h>

OneWire ourWire(parameters::pSENSOR);
DallasTemperature sensors(&ourWire);
TemperatureController temperatureController;
ClosedCube_HDC1080 hdc1080;
CommunicationControl communicationControl;
HumidityController humidityController;

void setup() {
  Serial.print("hello");
  communicationControl.begin();
  Serial.begin(9600);
  sensors.begin();
  pinMode(parameters::pSENSOR, INPUT);
  pinMode(parameters::pCONTROLE, OUTPUT);
  pinMode(parameters::ld,OUTPUT);
  temperatureController.begin(&sensors);
  hdc1080.begin(0x40); //Inicia o sensor de umidade
  

  //humidityController.startManualMode(99);
  humidityController.startAutomaticMode(90.0);
}

void loop() {

  Serial.print("HR: ");
  Serial.println(humidityController.getRelativeHumidity());
  Serial.print("Humidifier PID: ");
  Serial.println(humidityController.getPID());
  Serial.print("Potenciometer: ");
  Serial.println(humidityController.getpotIntensity());
  Serial.print("Dryer Temperature: ");
  Serial.println(temperatureController.getTemperature());
  Serial.print("Hello1");

  humidityController.run(); // Runs the PID responsable for the humidifier
  Serial.print("Hello2");

  float temp = hdc1080.readTemperature();
  float h = hdc1080.readHumidity();

  temperatureController.run(); //Runs the PID responsable for the dryer
  communicationControl.run(); //Runs the communication between dryer and computer interface
  Serial.print("Hello3");
  delay(300);

}