
#include "handControl.h"
#include <Arduino.h>

// Definição dos pinos (se necessário, pode movê-los para um arquivo de configuração separado)
const int dedo_polegar_p1 = 10;
const int dedo_polegar_p2 = 11;
const int dedo_indicador_p1 = 12;
const int dedo_indicador_p2 = 13;
const int dedo_medio_p1 = 14;
const int dedo_medio_p2 = 15;
const int dedo_anelar_p1 = 16;
const int dedo_anelar_p2 = 17;
const int dedo_minimo_p1 = 18;
const int dedo_minimo_p2 = 19;




void mao_fecha(){
    // Faz a mão fechar
  
    // Fecha o polegar
    digitalWrite(dedo_polegar_p1, LOW);
    digitalWrite(dedo_polegar_p2, HIGH);
  
    // Fecha o indicador
    digitalWrite(dedo_indicador_p1, LOW);
    digitalWrite(dedo_indicador_p2, HIGH);
  
    // Fecha o médio
    digitalWrite(dedo_medio_p1, LOW);
    digitalWrite(dedo_medio_p2, HIGH);
  
    // Fecha o anelar
    digitalWrite(dedo_anelar_p1, LOW);
    digitalWrite(dedo_anelar_p2, HIGH);
  
    // Fecha o mínimo
    digitalWrite(dedo_minimo_p1, LOW);
    digitalWrite(dedo_minimo_p2, HIGH);
  }
  
  void mao_joga_pedra(){
    // Faz a mão jogar pedra
    // Aqui não precisa fechar a mão, pois a mão já está fechada na hora de jogar
  
  }
  
  void mao_joga_papel(){
    // Faz a mão jogar papel
    
    // Solta o polegar
    digitalWrite(dedo_polegar_p1, HIGH);
    digitalWrite(dedo_polegar_p2, LOW);
  
    // Solta o indicador
    digitalWrite(dedo_indicador_p1, HIGH);
    digitalWrite(dedo_indicador_p2, LOW);
  
    // Solta o médio
    digitalWrite(dedo_medio_p1, HIGH);
    digitalWrite(dedo_medio_p2, LOW);
  
    // Solta o anelar
    digitalWrite(dedo_anelar_p1, HIGH);
    digitalWrite(dedo_anelar_p2, LOW);
  
    // Solta o mínimo
    digitalWrite(dedo_minimo_p1, HIGH);
    digitalWrite(dedo_minimo_p2, LOW);
  
  
  }
  
  void mao_joga_tesoura(){
    // Faz a mão jogar tesoura
  
    // Solta o polegar
    digitalWrite(dedo_polegar_p1, HIGH);
    digitalWrite(dedo_polegar_p2, LOW);
  
    // Solta o anelar
    digitalWrite(dedo_anelar_p1, HIGH);
    digitalWrite(dedo_anelar_p2, LOW);
  
    // Solta o mínimo
    digitalWrite(dedo_minimo_p1, HIGH);
    digitalWrite(dedo_minimo_p2, LOW);
  
  }
  