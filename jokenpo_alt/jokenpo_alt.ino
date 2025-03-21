#define LED_PEDRA 3
#define LED_PAPEL 4
#define LED_TESOURA 5

void setup() {
    Serial.begin(9600);  // Inicia a comunicação serial com a mesma taxa de transmissão usada no Python
    
    while (!Serial) {
        pinMode(LED_PEDRA, OUTPUT);
        pinMode(LED_PAPEL, OUTPUT);
        pinMode(LED_TESOURA, OUTPUT);
         // Aguarda a conexão serial ser estabelecida (funciona no Arduino Leonardo e Micro)
    }

}

void loop() {
    int potencio = analogRead(A0);

    if (Serial.available() > 0) {  // Verifica se há dados disponíveis na serial
        String recebido = Serial.readStringUntil(', ');  // Lê a string até encontrar um caractere de nova linha
        recebido.trim(); // Remove espaços e quebras de linha extras
        
        Serial.print("Recebido: ");
        Serial.println(recebido);
        
        // Desliga todos os LEDs antes de acender o correto
        digitalWrite(LED_PEDRA, LOW);
        digitalWrite(LED_PAPEL, LOW);
        digitalWrite(LED_TESOURA, LOW);

        if (recebido == "Pedra") {
            digitalWrite(LED_PEDRA, HIGH);
        } 
        else if (recebido == "Papel") {
            digitalWrite(LED_PAPEL, HIGH);
        } 
        else if (recebido == "Tesoura") {
            digitalWrite(LED_TESOURA, HIGH);
        }
    }
}
