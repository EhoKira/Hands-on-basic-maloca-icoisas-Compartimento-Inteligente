// Definição dos pinos
#define led_remedio1  32
#define  led_remedio2 33
#define  led_remedio3  22
#define  led_remedio4  23
#define buzzer  18

void setup(void) {
  Serial.begin(115200); 
  // Configura os pinos dos LEDs como saída
  pinMode(led_remedio1, OUTPUT);
  pinMode(led_remedio2, OUTPUT);
  pinMode(led_remedio3, OUTPUT);
  pinMode(led_remedio4, OUTPUT);
  
  // Configura o pino do buzzer como saída
  pinMode(buzzer, OUTPUT);
}

void loop(void) {
  // Acende o LED 1 e toca o buzzer
  digitalWrite(led_remedio1, HIGH);
  Serial.println("Remédio 1");
  // tone(buzzer, 500); 
  delay(500);         // Aguarda meio segundo
  digitalWrite(led_remedio1, LOW);
  // noTone(buzzer);     // Para o som

  // Acende o LED 2 e toca o buzzer
  digitalWrite(led_remedio2, HIGH);
  Serial.println("Remédio 2");
  // tone(buzzer, 500);
  delay(500);
  digitalWrite(led_remedio2, LOW);
  // noTone(buzzer);

  // Acende o LED 3 e toca o buzzer
  digitalWrite(led_remedio3, HIGH);
  Serial.println("Remédio 3");
  // tone(buzzer, 500);
  delay(500);
  digitalWrite(led_remedio3, LOW);
  // noTone(buzzer);

  // Acende o LED 4 e toca o buzzer
  digitalWrite(led_remedio4, HIGH);
  Serial.println("Remédio 4");
  // tone(buzzer, 500);
  delay(500);
  digitalWrite(led_remedio4, LOW);
  // noTone(buzzer);

  // Aguarda um segundo antes de reiniciar a sequência
  delay(1000);
}
