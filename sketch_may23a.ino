#include <DHT.h>
#include <Servo.h>

// Definição dos pinos
#define DHTPIN 2     // Pino de dados do DHT11
#define DHTTYPE DHT22 // Tipo do sensor DHT

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

const int servoPin = 9;  // Pino do servo motor

void setup() {
  Serial.begin(9600);
  dht.begin();
  myServo.attach(servoPin);
  myServo.write(90); // Posicionar o servo no meio (posição neutra)
}

void loop() {
  float umidade = dht.readHumidity();
  
  // Verifica se a leitura falhou e tenta novamente
  if (isnan(umidade)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }
  // else if (umidade > 60) {
  //     myServo.write(myServo.read() - 1); // Gira lentamente no sentido  anti - horário 
  // } else if (umidade < 50) {
  //     myServo.write(myServo.read() + 1); // Gira lentamente no sentido horário
  // }
  myServo.write(myServo.read() - ((umidade > 80)? 1 : 0) + ((umidade < 70)? 1 : 0));
  
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("%");
     
  delay(2000); // Delay entre as leituras do sensor
}
