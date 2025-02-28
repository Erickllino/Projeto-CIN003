const pino_papel = 2;
const pino_tesoura = 3;
const pino_pedra = 4;
const pino_desconhecido = 5;


void setup(){
    Serial.begin(9600);
    
    pinMode(pino_papel, INPUT);
    pinMode(pino_tesoura, INPUT);
    pinMode(pino_pedra, INPUT);
    pinMode(pino_desconhecido, INPUT);



}


void ganhar(tesoura,pedra,papel,desconhecido){
    if (tesoura == 1 && pedra == 0 && papel == 0 && desconhecido == 0){
        // Se o inimigo jogar tesoura, joga pedra
        Serial.println("Ganhou");
    }elif(tesoura == 0 && pedra == 1 && papel == 0 && desconhecido == 0){
        // Se o inimigo jogar pedra, joga papel
        Serial.println("Ganhou");
    }elif(tesoura == 0 && pedra == 0 && papel == 1 && desconhecido == 0){
        // Se o inimigo jogar papel, joga tesoura
        Serial.println("Ganhou");
    }elif(tesoura == 0 && pedra == 0 && papel == 0 && desconhecido == 1){
        // Se o inimigo jogar desconhecido, ??
        Serial.println("Ganhou");
    }

}

void perder(tesoura,pedra,papel,desconhecido){
    if (tesoura == 1 && pedra == 0 && papel == 0 && desconhecido == 0){
        // Se o inimigo jogar tesoura, joga papel
        Serial.println("Perdeu");
    }elif(tesoura == 0 && pedra == 1 && papel == 0 && desconhecido == 0){
        // Se o inimigo jogar pedra, joga tesoura
        Serial.println("Perdeu");
    }elif(tesoura == 0 && pedra == 0 && papel == 1 && desconhecido == 0){
        // Se o inimigo jogar papel, joga pedra
        Serial.println("Perdeu");
    }elif(tesoura == 0 && pedra == 0 && papel == 0 && desconhecido == 1){
        // Se o inimigo jogar desconhecido, ??
        Serial.println("Perdeu");
    }

}

void empatar(tesoura,pedra,papel,desconhecido){
    if (tesoura == 1 && pedra == 0 && papel == 0 && desconhecido == 0){
        // Se o inimigo jogar tesoura, joga tesoura
        Serial.println("Empatou");
    }elif(tesoura == 0 && pedra == 1 && papel == 0 && desconhecido == 0){
        // Se o inimigo jogar pedra, joga pedra
        Serial.println("Empatou");
    }elif(tesoura == 0 && pedra == 0 && papel == 1 && desconhecido == 0){
        // Se o inimigo jogar papel, joga papel
        Serial.println("Empatou");
    }elif(tesoura == 0 && pedra == 0 && papel == 0 && desconhecido == 1){
        // Se o inimigo jogar desconhecido, ??
        Serial.println("Empatou");
    }

}




void loop(){

    // Leu o estado dos pinos
    tesoura = digitalRead(pino_tesoura);
    papel = digitalRead(pino_papel);
    pedra = digitalRead(pino_pedra);
    desconhecido = digitalRead(pino_desconhecido);

    // Escolhe qual dos 3 jogos serão jogados
    formato_escolhido = 0;

    // Escolhe qual mão será jogada
    if (formato_escolhido == 0){
        ganhar(tesoura, papel, pedra, desconhecido);
    }elif(formato_escolhido == 1){
        perder(tesoura, papel, pedra, desconhecido);
    }elif(formato_escolhido == 2){
        empatar(tesoura, papel, pedra, desconhecido);;
    }


}