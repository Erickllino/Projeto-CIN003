#include <Servo.h>

// Potenciômetro para escolher o modo de jogo
#define ESCOLHER_O_JOGO A0

// Define semente randômica
#define RANDOM_SEED A1

#define pino_pedra 2
#define pino_papel 3
#define pino_tesoura 4

// Define os pinos dos motores para cada dedo:
Servo servoMotor1;
Servo servoMotor2;

void setup(){
  Serial.begin(9600);
      
  servoMotor1.attach(12);
  servoMotor2.attach(13);

  pinMode(pino_pedra,INPUT_PULLUP);
  pinMode(pino_papel,INPUT_PULLUP);
  pinMode(pino_tesoura,INPUT_PULLUP);

  // Implementa critérios de aleatoriedade para sorteio
  randomSeed(analogRead(RANDOM_SEED));
}

// Descobre a opção de modo de jogo escolhida pelo player
int jogo_Escolhido(int valor){
  if (valor >= 0 && valor < 250){
    return 1;
  }
  else if (valor >= 250 && valor < 500){
    return 2;
  }
  else if (valor >= 500 && valor < 750){
    return 3;
  }
  else if (valor >= 750 && valor <= 1023){
    return 4;
  }
  return 0;
}


// Funções para os movimentos da mão
void jogar_pedra() {
    // Fecha os motores 1 e 2 para jogar "pedra"
    servoMotor1.write(90);
    servoMotor2.write(90);
    delay(570);
    servoMotor1.write(90);
    servoMotor2.write(90);
    delay(1000);
    servoMotor1.write(90);
    servoMotor2.write(90);
    delay(570);
}

void jogar_papel() {

    servoMotor1.write(0);
    servoMotor2.write(0);
    delay(570);
    servoMotor1.write(90);
    servoMotor2.write(90);
    delay(1000);
    servoMotor1.write(180);
    servoMotor2.write(180);
    delay(570);
  

}

void jogar_tesoura() {
 
    servoMotor1.write(0);
    servoMotor2.write(90);
    delay(570);
    servoMotor1.write(90);
    servoMotor2.write(90);
    delay(1000);
    servoMotor1.write(180);
    servoMotor2.write(90);
    delay(570);

}

// Modos de jogo

int ganhar(int pedra, int papel, int tesoura){
  if (tesoura == 0){
    // Se o player jogou tesoura, a mão joga pedra para ganhar
    jogar_pedra();
  }
  else if (pedra == 0){
    // Se o player jogou pedra, a mão joga papel para ganhar
    jogar_papel();
  }
  else if (papel == 0){
    // Se o player jogou papel, a mão joga tesoura para ganhar
    jogar_tesoura();
  }
  return 1;
}

int empatar(int pedra, int papel, int tesoura){   
  if (tesoura == 0){
    // Se o player jogou tesoura, a mão também joga tesoura
    jogar_tesoura();
  }
  else if (pedra == 0){
    // Se o player jogou pedra, a mão joga pedra
    jogar_pedra();
  }
  else if (papel == 0){
    // Se o player jogou papel, a mão joga papel
    jogar_papel();
  }
  return 0;
}

int perder(int pedra, int papel, int tesoura){    
  if (tesoura == 0){
    // Se o player jogou tesoura, a mão joga papel para perder
    jogar_papel();
  }
  else if (pedra == 0){
    // Se o player jogou pedra, a mão joga tesoura para perder
    jogar_tesoura();
  }
  else if (papel == 0){
    // Se o player jogou papel, a mão joga pedra para perder
    jogar_pedra();
  }
  return -1;
}

int aleatorio(int pedra, int papel, int tesoura){
  int jogada_mao = random(1, 4);
  int mao_pedra = 0, mao_papel = 0, mao_tesoura = 0;



  if (jogada_mao == 1){
    mao_pedra = 1;
    // A mão joga pedra
    jogar_pedra();
  }
  else if (jogada_mao == 2){
    mao_papel = 1;
    // A mão joga papel
    jogar_papel();
  }
  else if (jogada_mao == 3){
    mao_tesoura = 1;
    // A mão joga tesoura
    jogar_tesoura();
  }

  // Verifica o resultado da jogada comparado com a escolha do player
  if ((mao_pedra == 1 && tesoura == 0) ||
      (mao_papel == 1 && pedra == 0) ||
      (mao_tesoura == 1 && papel == 0)) {
    return 1; // A mão ganha
  }
  else if ((pedra == 0 && mao_tesoura == 1) ||
           (papel == 0 && mao_pedra == 1) ||
           (tesoura == 0 && mao_papel == 1)) {
    return -1; // O player ganha
  }
  else {
    return 0; // Empate
  }
}

void loop(){
  servoMotor1.write(90);
  servoMotor2.write(90);
  // Lê o valor do potenciômetro e escolhe o modo de jogo
  int potencial = analogRead(ESCOLHER_O_JOGO);
  int modo_de_jogo = jogo_Escolhido(potencial);

    // Leu o estado dos pinos
  int pedra = digitalRead(pino_pedra);
  int papel = digitalRead(pino_papel);
  int tesoura = digitalRead(pino_tesoura);

  
  // Escolhe qual modo de jogo será executado
  int resultado;
  if (pedra+papel+tesoura < 3){
    if (modo_de_jogo == 1){
      resultado = ganhar(pedra, papel, tesoura);
    }
    else if(modo_de_jogo == 2){
      resultado = perder(pedra, papel, tesoura);
    }
    else if(modo_de_jogo == 3){
      resultado = empatar(pedra, papel, tesoura);
    }
    else if(modo_de_jogo == 4){
      resultado = aleatorio(pedra, papel, tesoura);
    }
  }
    // Efeito especial executado conforme o resultado (mesma ação para ganhar, empatar ou perder)

}
