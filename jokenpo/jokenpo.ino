// Usa #define para não ocupar espaço na memória e ser mais rápido


// Ivan, não troca o nome do codigo pode dar problema no git
// Pr ficar organizado, vale 

// Define os botões que escolhe os modos de jogos
#define escolha_do_jogo A0

// Define os pinos de possiveis jogadas
#define pino_papel 2
#define pino_tesoura 3
#define pino_pedra 4
#define pino_desconhecido 5

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



void setup(){
    Serial.begin(9600);
    // Receberá informações do raspberrypi
    pinMode(pino_papel, INPUT);
    pinMode(pino_tesoura, INPUT);
    pinMode(pino_pedra, INPUT);
    pinMode(pino_desconhecido, INPUT);
    // Botão quando pressionado apresenta HIGH
    pinMode(botao_mao_ganha, INPUT_PULLDOWN);
    pinMode(botao_mao_perde, INPUT_PULLDOWN);
    pinMode(botao_mao_empata, INPUT_PULLDOWN);
    pinMode(botao_mao_aleatoria, INPUT_PULLDOWN);
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
  if (valor > 250 && valor < 500){
    return 2;
  }
  if (valor > 500 && valor < 750){
    return 3;
  }
  if (valor > 750 && valor <= 1023){
    return 4;
  }

  // !!! Ideia: fazer a mão dar joinha pra confirmar que realmente um botão foi confirmado, oq acha? !!!
}

// Descobre o que o jogador jogou contra a máquina
char jogada_do_player(tesoura, pedra, papel, desconhecido){
  if (tesoura == 1){
    
    return "tesoura";
  }
  elif (pedra == 1){
    return "pedra";
  }
  elif (papel == 1){
    return "papel";
  }
  elif (desconhecido == 1){
    return "desconhecido";
  }
    
}


// Abaixo estão definidas os modos de jogo
int mao_ganha(jogada){
    switch(jogada){
      case tesoura:
        // Faz a mão jogar pedra

        break;
      case papel:
        // Faz a mão jogar tesoura

        break;
      case pedra:
        // Faz a mão jogar papel

        break;
    }
    // Imprime no monitor serial
    Serial.println("A mão venceu!");
    // Retorna que a mão venceu
    return 1;

}

int mao_perde(jogada){
    switch(jogada){
      case tesoura:
        // Faz a mão jogar papel

        break;
      case papel:
        // Faz a mão jogar tesoura

        break;
      case pedra:
        // Faz a mão jogar papel

        break;
    }

    // Imprime no monitor serial
    Serial.println("A mão perdeu");
    // Retorna que a mão venceu
    return -1;

}

int mao_empata(tesoura,pedra,papel,desconhecido){
    switch(jogada){
      case tesoura:
        // Faz a mão jogar papel

        break;
      case papel:
        // Faz a mão jogar tesoura

        break;
      case pedra:
        // Faz a mão jogar papel

        break;
    }

    // Imprime no monitor serial
    Serial.println("A mão empatou com o jogador");
    // Retorna que a mão venceu
    return 0;

}






void loop(){
    

    // Escolhe qual dos 3 jogos serão jogados
    int potencio = analogRead(A0);
    modo_de_jogo = botao_apertado(potencio);

    // Leu o estado dos pinos
    tesoura = digitalRead(pino_tesoura);
    papel = digitalRead(pino_papel);
    pedra = digitalRead(pino_pedra);
    desconhecido = digitalRead(pino_desconhecido);

    // Descobre a jogada do player
    jogada = jogada_do_player(tesoura, pedra, papel, desconhecido);


    // Escolhe qual modo de jogo será jogado
    if (modo_de_jogo == 1){
      resultado = ganhar(jogada);
    }elif(modo_de_jogo == 2){
      resultado = perder(jogada);
    }elif(modo_de_jogo == 3){
      resultado = empatar(jogada);
    }elif(modo_de_jogo) == 4{
        // Função que ainda não foi criada
      }

    // Efeito especial executado conforme o resultado
    if (resultado == 1){
      // Mão ganhou
      mao_vencedora();
    } 
    elif(resultado == 0){
      // Mão empatou
      mao_empatada();
    }
    elif(resultado == -1){
      // Mão perdeu
      mao_empatada();
    }
    }


}