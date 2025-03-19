// Usa #define para não ocupar espaço na memória e ser mais rápido


// Ivan, não troca o nome do codigo pode dar problema no git
// Pr ficar organizado, vale 

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

#define MAO_PEDRA 8
#define MAO_PAPEL 9
#define MAO_TESOURA 10

void setup(){
    Serial.begin(9600);
    // Receberá informações do raspberrypi
    pinMode(PEDRA_PIN, INPUT_PULLUP);
    pinMode(PAPEL_PIN, INPUT_PULLUP);
    pinMode(TESOURA_PIN, INPUT_PULLUP);
    pinMode(DESCONHECIDO_PIN, INPUT_PULLUP);
    
	pinMode(MAO_PEDRA, OUTPUT);
  	pinMode(MAO_PAPEL, OUTPUT);
  	pinMode(MAO_TESOURA, OUTPUT);
}

// Estamos escrevendo muitas funçoes, acho interresante criar um arquivo .h para colocar todas as funções
// e deixar o código mais limpo
// !!! Vou estudar como fazer isso e te falo !!!


// Descobre a opção de modo de jogo escolhida pelo player
// Trocar isso por um potenciometro

int jogo_Escolhido(int valor){
  if (valor >= 0 && valor < 250){
    return 1;
  }
  else if (valor > 250 && valor < 500){
    return 2;
  }
  else if (valor > 500 && valor < 750){
    return 3;
  }
  else if (valor > 750 && valor <= 1023){
    return 4;
  }
	return 0;
  // !!! Ideia: fazer a mão dar joinha pra confirmar que realmente um botão foi confirmado, oq acha? !!!
}


void jogar_pedra() {
    digitalWrite(MAO_PEDRA, HIGH);
    digitalWrite(MAO_PAPEL, LOW);
    digitalWrite(MAO_TESOURA, LOW);
}

void jogar_papel() {
    digitalWrite(MAO_PEDRA, LOW);
    digitalWrite(MAO_PAPEL, HIGH);
    digitalWrite(MAO_TESOURA, LOW);
}

void jogar_tesoura() {
    digitalWrite(MAO_PEDRA, LOW);
    digitalWrite(MAO_PAPEL, LOW);
    digitalWrite(MAO_TESOURA, HIGH);
}

// Abaixo estão definidas os modos de jogo
int ganhar(int pedra,int papel, int tesoura){

    
  if (tesoura == 0){
    Serial.print("Joguei tesoura");
    // Adiciona a função que faz a mão jogar pedra
    jogar_pedra();
  }
   else if (pedra == 0){
    Serial.print("Joguei pedra");
    // Adiciona a função que faz a mão jogar papel
    jogar_papel();
  }
   else if (papel == 0){
    Serial.print("Joguei papel");
    // Adiciona a função que faz a mão jogar tesoura
    jogar_tesoura();
  };
  return 1;
  
}

int empatar(int pedra,int papel, int tesoura){

    
  if (tesoura == 0){
    Serial.print("Joguei tesoura");
    // Adiciona a função que faz a mão jogar tesoura
    jogar_tesoura();
  }
   else if (pedra == 0){
    Serial.print("Joguei pedra");
    // Adiciona a função que faz a mão jogar pedra
    jogar_pedra();
  }
   else if (papel == 0){
    Serial.print("Joguei papel");
    // Adiciona a função que faz a mão jogar papel
    jogar_papel();
  };
  return 0;
}

int perder(int pedra,int papel, int tesoura){

    
  if (tesoura == 0){
    Serial.print("Joguei tesoura");
    // Adiciona a função que faz a mão jogar papel
    jogar_papel();
  }
   else if (pedra == 0){
    Serial.print("Joguei pedra");
    // Adiciona a função que faz a mão jogar tesoura
    jogar_tesoura();
  }
   else if (papel == 0){
    Serial.print("Joguei papel");
    // Adiciona a função que faz a mão jogar pedra
    jogar_pedra();
  };
  return -1;
}

int aleatorio(int pedra,int papel,int tesoura){
  return 0;
}

void loop(){

    if (Serial.available() > 0) {  // Verifica se há dados disponíveis na serial
        String recebido = Serial.readStringUntil(', ');  // Lê a string até encontrar um caractere de nova linha
        recebido.trim(); // Remove espaços e quebras de linha extras
        
        

        // Escolhe qual dos 3 jogos serão jogados
        int potencio = analogRead(A0);
        int modo_de_jogo = jogo_Escolhido(potencio);

        // Leu o estado dos pinos


        Serial.print("Jogo escolhido: ");
        Serial.println(modo_de_jogo);

        int pedra = 1,papel = 1,tesoura = 1;

        
        if (recebido == "Pedra,"){
          pedra = 0;
          papel = 1;
          tesoura = 1;
        };
        if (recebido == "Papel,"){
          pedra = 1;
          papel = 0;
          tesoura = 1;
        };
        if (recebido == "Tesoura,"){
          pedra = 1;
          papel = 1;
          tesoura = 0;
        };
        

        // Escolhe qual modo de jogo será jogado
        int resultado;
        if (modo_de_jogo == 1){
          resultado = ganhar(pedra,papel,tesoura);
        }else if(modo_de_jogo == 2){
          resultado = perder(pedra,papel,tesoura);
        }else if(modo_de_jogo == 3){
          resultado = empatar(pedra,papel,tesoura);
        }else if(modo_de_jogo == 4){
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
    }  

	delay(500);
}