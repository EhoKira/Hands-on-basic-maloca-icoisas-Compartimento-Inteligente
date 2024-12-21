#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h> 

// Configurações de rede Wi-Fi
const char* ssid = "SS_ID";
const char* password = "PASSWORD";

// Configurações do HiveMQ Broker
const char* mqtt_server = "SERVER_URL";
const char* mqtt_topic = "TOPIC";  
const char* mqtt_username = "USERNAME"; 
const char* mqtt_password = "PASSWORD_HIVE"; 
const int mqtt_port = 8883;  

WiFiClientSecure espClient;  
PubSubClient client(espClient);

// Definição dos pinos
#define led_remedio1  32
#define led_remedio2  33
#define led_remedio3  22
#define led_remedio4  23
#define buzzer        18


// Função de callback para receber mensagens MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida: ");
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Aciona os LEDs e o buzzer com base no tópico recebido
  if (message == "remedio1") {
    acionaLedEBuzzer(led_remedio1, "Remédio 1");
  } else if (message == "remedio2") {
    acionaLedEBuzzer(led_remedio2, "Remédio 2");
  } else if (message == "remedio3") {
    acionaLedEBuzzer(led_remedio3, "Remédio 3");
  } else if (message == "remedio4") {
    acionaLedEBuzzer(led_remedio4, "Remédio 4");
  } else if (message == "on_led") {
    digitalWrite(23, HIGH);  // Ação de ligar um dispositivo (se necessário)
  } else if (message == "off_led") {
    digitalWrite(23, LOW);   // Ação de desligar o dispositivo (se necessário)
  }
}

// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi conectado.");
}

// Função para reconectar ao broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando se reconectar ao MQTT...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("Conectado.");
      client.subscribe(mqtt_topic);  // Inscreve-se no tópico
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos.");
      delay(5000);
    }
  }
}

// Função para acionar o LED e o buzzer
void acionaLedEBuzzer(int ledPin, const char* nomeRemedio) {
  Serial.println("Entrou");
  digitalWrite(ledPin, HIGH);
  tone(buzzer, 2500); 
  Serial.println(nomeRemedio);
  delay(4000);      
  digitalWrite(ledPin, LOW);
  noTone(buzzer);
}

void setup() {
  Serial.begin(115200);

  // Configura os pinos dos LEDs como saída
  pinMode(led_remedio1, OUTPUT);
  pinMode(led_remedio2, OUTPUT);
  pinMode(led_remedio3, OUTPUT);
  pinMode(led_remedio4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(23, OUTPUT); 

  // Conexão ao Wi-Fi e MQTT
  setup_wifi();
  espClient.setInsecure(); 
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
