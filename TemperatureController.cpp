#include "TemperatureController.h"
#include <Parameters.h>

void TemperatureController::begin(DallasTemperature *sensors) //Inicialização dos modulos
{
    error = 0;
    sensors->requestTemperatures(); //Requisição da temperatura
    temp = sensors->getTempCByIndex(0); //Mede a temperatura e guarda em uma variavel
    lastemp = temp; //Guarda a temperatura do ultimo ciclo na variavel lastemp
    kP = 15.0; kI = 0; kD = 0;     
    P = 0; I = 0; D = 0;
    pid = 0;
    stopFlag = true;
    this->sensors = sensors; //Não entendi muito bem
    lastProcess = millis();
    setPoint = 30.0;
}

void TemperatureController::run() //Contas do PID
{
    //Requisita, mede e guarda a temperatura
    sensors->setWaitForConversion(false);
    sensors->requestTemperatures();
    temp = sensors->getTempCByIndex(0);
    sensors->setWaitForConversion(true);

    error = setPoint - temp; //Calcula o erro entre o setpoint e a temperatura
    auto currentProcess = millis(); //Armazena o tempo do processo em uma variavel
    float deltaTime = (currentProcess - lastProcess) / 1000.0;
    lastProcess = currentProcess;
    
    //P
    P = error * kP;
    
    //I
    I = I + (error * kI) * deltaTime;
    
    //D
    D = (lastemp - temp) * kD / deltaTime;
    lastemp = temp;
    
    // Soma tudo
    pid = P + I + D;
    if (stopFlag == false)
    {
       pid = P + I + D; 

        if (pid >= 255){
        pid = 255;
        }
        if (pid <= 0){
        pid = 0;
        }
        if (pid == 0){
        digitalWrite(2, LOW);
        }
        if (pid > 0){
        digitalWrite(2, HIGH);
        }
        analogWrite(3, pid);
    }
    if (stopFlag == true){
       pid = 0;
      }
}
float TemperatureController::getTemperature()
{
    return temp;
}

float TemperatureController::getKP()
{
    return kP;
}

float TemperatureController::getKI()
{
    return kI;
}

float TemperatureController::getKD()
{
    return kD;
}

void TemperatureController::setPID(float KP, float KI, float KD)
{
    kP = KP;
    kI = KI;
    kD = KD;
}

void TemperatureController::setSetPoint(float setpoint)
{
    setPoint = setpoint;
}

void TemperatureController::start()
{
    stopFlag = false;
}

void TemperatureController::stop()
{
    stopFlag = true;
}
