// Usa #define para não ocupar espaço na memória e ser mais rápido


// Ivan, não troca o nome do codigo pode dar problema no git
// Pr ficar organizado, vale 

// Define os botões que escolhe os modos de jogos
#define botao_mao_ganha 6
#define botao_mao_perde 7
#define botao_mao_empata 8
#define botao_mao_aleatoria 9 // !!! Criar essa função !!! (eu vou estudar e fazer erick, relaxe)

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
int botao_apertado(bt_mg, bt_mp, bt_me, bt_ma){
  if (bt_mg == HIGH){
    return 1;
  }
  elif (bt_mp == HIGH){
    return 2;
  }
  elif (bt_me == HIGH){
    return 3;
  }
  elif (bt_ma == HIGH){
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



// Funções para reagir ao resultado
void mao_vencedora(){
  // Vamos colocar aqui os sons e as luzes de que a mão venceu
}

void mao_derrotada(){
  // Vamos colocar aqui os sons e as luzes de que a mão perdeu
}

void mao_empatada(){
  // Vamos colocar aqui os sons e as luzes de que a mão de empate
}




void loop(){
    // Lê os botões
    bt_mg = digitalRead(botao_mao_ganha);
    bt_mp = digitalRead(botao_mao_perde);
    bt_me = digitalRead(botao_mao_empata);
    bt_ma = digitalRead(botao_mao_aleatoria);
    // Escolhe qual dos 3 jogos serão jogados
    modo_de_jogo = botao_apertado(bt_mg, bt_mp, bt_me, bt_ma);

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