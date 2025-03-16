/*

Fiz esse arquivo para testes 
Vou usar leds ao inves de motores para testar o código

*/

// Define os botões que escolhe os modos de jogos
#define ESCOLHER_O_JOGO A0

// Define os pinos de possiveis jogadas
#define PEDRA_PIN 2
#define PAPEL_PIN 3
#define TESOURA_PIN 4
#define DESCONHECIDO_PIN 5

// Define os pinos dos motores para cada dedo:
#define dedo_polegar_p1 10
#define dedo_polegar_p2 11
#define dedo_indicador_p1 12
#define dedo_indicador_p2 13
#define dedo_medio_p1 14
#define dedo_medio_p2 15
#define dedo_anelar_p1 16
#define dedo_anelar_p2 17
#define dedo_minimo_p1 18
#define dedo_minimo_p2 19

// Define os pinos dos leds para emular cada dedo da mão
#define MAO_PEDRA_PIN 8
#define MAO_PAPEL_PIN 9
#define MAO_TESOURA_PIN 10

void setup()
{
    Serial.begin(9600);

    pinMode(PEDRA_PIN, INPUT_PULLUP);
    pinMode(PAPEL_PIN, INPUT_PULLUP);
    pinMode(TESOURA_PIN, INPUT_PULLUP);
    pinMode(DESCONHECIDO_PIN, INPUT_PULLUP);

  	pinMode(MAO_PAPEL_PIN, OUTPUT);
  	pinMode(MAO_TESOURA_PIN, OUTPUT);
  	pinMode(MAO_PEDRA_PIN, OUTPUT);
  
    
}

// Função para determinar o jogo escolhido
int jogo_Escolhido(int valor) {
    if (valor >= 0 && valor < 250) {
        return 1;
    }
    if (valor >= 250 && valor < 500) {
        return 2;
    }
    if (valor >= 500 && valor < 750) {
        return 3;
    }
    if (valor >= 750 && valor <= 1023) {
        return 4;
    }
    return 0; // Valor inválido
}

// Abaixo estão definidas os modos de jogo
int ganhar(int pedra,int papel, int tesoura){
  Serial.print("Pedra: "); Serial.print(pedra);
  Serial.print(" | Papel: "); Serial.print(papel);
  Serial.print(" | Tesoura: "); Serial.println(tesoura);
    
  if (tesoura == 0){
    Serial.print("Joguei tesoura");
    // Adiciona a função que faz a mão jogar pedra
    
  }
   else if (pedra == 0){
    Serial.print("Joguei pedra");
    // Adiciona a função que faz a mão jogar papel
    
  }
   else if (papel == 0){
    Serial.print("Joguei papel");
    // Adiciona a função que faz a mão jogar tesoura
    
  };
  
}

int empatar(int pedra,int papel, int tesoura){
  Serial.print("Pedra: "); Serial.print(pedra);
  Serial.print(" | Papel: "); Serial.print(papel);
  Serial.print(" | Tesoura: "); Serial.println(tesoura);
    
  if (tesoura == 0){
    Serial.print("Joguei tesoura");
    // Adiciona a função que faz a mão jogar tesoura
    
  }
   else if (pedra == 0){
    Serial.print("Joguei pedra");
    // Adiciona a função que faz a mão jogar pedra
    
  }
   else if (papel == 0){
    Serial.print("Joguei papel");
    // Adiciona a função que faz a mão jogar papel
    
  };
  
}

int perder(int pedra,int papel, int tesoura){
  Serial.print("Pedra: "); Serial.print(pedra);
  Serial.print(" | Papel: "); Serial.print(papel);
  Serial.print(" | Tesoura: "); Serial.println(tesoura);
    
  if (tesoura == 0){
    Serial.print("Joguei tesoura");
    // Adiciona a função que faz a mão jogar papel
    
  }
   else if (pedra == 0){
    Serial.print("Joguei pedra");
    // Adiciona a função que faz a mão jogar papel
    
  }
   else if (papel == 0){
    Serial.print("Joguei papel");
    // Adiciona a função que faz a mão jogar pedra
    
  };
  
}

int aleatorio(int pedra,int papel,int tesoura){
	return 0;
}

void loop()
{
    // Escolhe qual dos 3 jogos serão jogados
    int potencio = analogRead(A0);
  	
    int modo_de_jogo = jogo_Escolhido(potencio);
    
    // Leu o estado dos pinos
    int pedra = digitalRead(PEDRA_PIN);
    int papel = digitalRead(PAPEL_PIN);
    int tesoura = digitalRead(TESOURA_PIN);
    int desconhecido = digitalRead(DESCONHECIDO_PIN);


    Serial.print("Jogo escolhido: ");
    Serial.println(modo_de_jogo);
	
  	
    // Escolhe qual modo de jogo será jogado
    int resultado;
    if (modo_de_jogo == 1){
      resultado = ganhar(pedra,papel,tesoura);
    }
  	else if(modo_de_jogo == 2){
      resultado = perder(pedra,papel,tesoura);
    }
  	else if(modo_de_jogo == 3){
      resultado = empatar(pedra,papel,tesoura);
    }
  	else if(modo_de_jogo == 4){
        // Função que ainda não foi criada
      resultado = aleatorio(pedra,papel,tesoura);
    }


    // Efeito especial executado conforme o resultado
    if (resultado == 1){
      // Mão ganhou
      
    } 
    else if(resultado == 0){
      // Mão empatou
      
    }
    else if(resultado == -1){
      // Mão perdeu
      
    }
    
    delay(500); // Pequena pausa para evitar spam na Serial
}
