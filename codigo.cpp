

/* o codigo nao esta funcionando, eu imaginei que isso aconteceria,
mas como a julia me recomendou a dizer, eu compreendi o que deveria ser feito,
e a partir do que eu consegui nas aulas aprender acho que fiz corretamente a ideia dos semaforos que piscam,
no temporizador correto, no entando errei na parte da montagem do sistema provavelmente e nao sei fazer corretamente as conexoes,
entao o que conseguir considerar por tentativa eu agradeço, e mesmo nao conseguindo fazer o exercicio por completo e entregar,
confesso que fiquei orgulhoso de ter chegado longe!! abs */


// Definindo numeros dos pinos pros leds
#define led_verde 41    // Led verde
#define led_vermelho 40 // Led vermelho
#define led_amarelo 8   // Led azul

// Definindo pino do botão e do LDR 
const int buttonPin = 18;  // pino do botão
const int ldrPin = 4;      // pino do Ldr

// Variaveis do botao e do Ldr
int buttonState = 0;  // para segurar o botao
int ldrstatus = 0;    // para segurar o valor do sensor Ldr
int threshold = 600;  // LDR threshold pra claro e escuro
int buttonPressCount = 0; // para contar o numero de apertos no botao
unsigned long lastDebounceTime = 0;  // tempo dp Debounce
unsigned long debounceDelay = 50;    // Delay do debounce

void setup() {
  // Inicializando comunicação do debug
  Serial.begin(9600);
  
  // Marcando os LEDs como OUTPUT com o pinMode
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  
  // Marcando o botao como INPUT
  pinMode(buttonPin, INPUT);


  // Inicializando os LEDs para ficarem desligados com o digitalWrite
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);
}


void loop() {
  // para ler o valor do Ldr
  ldrstatus = analogRead(ldrPin);
  
  // para ler o botao e a logica do debounce
  int reading = digitalRead(buttonPin);
  if (reading != buttonState) {
    lastDebounceTime = millis();  // reset no tempo do debounce
  }


  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        buttonPressCount++;
        Serial.println("Button Pressed");
      }
    }
  }

}
  // Se tiver a noite ativar o modo escuro (ou seja o amarelo piscante)
  if (ldrstatus <= threshold) {
    Serial.println("It's dark! Activating night mode...");
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_amarelo, HIGH); // ligar o Led amarelo
    delay(1000);
    digitalWrite(led_amarelo, LOW); // desligar o led amarelo
    delay(1000);
  } else {
    // se tiver claro, normalizar os semaforos
    Serial.println("esta de dia, semaforos normais!...");
    digitalWrite(led_amarelo, LOW); // desligue o amarelo para modo normal
    
    // Led vermelho (5 segundos)
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, HIGH);
    delay(5000);


    // Led verde (3 segundos)
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_verde, HIGH);
    delay(3000);


    // Led amarelo (2 segundos)
    digitalWrite(led_verde, LOW);
    digitalWrite(led_amarelo, HIGH);
    delay(2000);
    digitalWrite(led_amarelo, LOW);
  }



  


