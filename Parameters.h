#ifndef PARAMETERS_H
#define PARAMETERS_H

namespace parameters
{
  //Pinos responsaveis pelo umidificador
  static constexpr int pinPot1  = 2;
  static constexpr int pinPot2  = 3;
  static constexpr int pinPot3  = 4;

  //Pinos responsaveis pelo secador
  static constexpr int pSENSOR  = 7;
  static constexpr int pCONTROLE = 3;
  static constexpr int ld = 2;
  static constexpr int DT = A1;
  static constexpr int SCK = A0;
};



#endif