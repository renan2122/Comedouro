//Módulo Esp8266 Nodemcu V3 
//2x servo motor
//sensor de força 
//sensor de distancia ultrassonico
#include<Arduino.h>
#include <Servo.h>

int fsrAnalogPin = 0;
int LEDpin = 9;      
int fsrReading;
int LEDbrightness;
const int trigger = 8;
const int eco = 7;
Servo meuServo;

int angulo;
long duracao;
float dist;

void setup() {
  Serial.begin(9600);  
  pinMode(LEDpin, OUTPUT);
  pinMode(trigger, OUTPUT); // Configura o pino trigger como saída
  pinMode(eco, INPUT); // Configura o pino eco como entrada.
  Serial.println("Insira o angulo desejado: ");
  meuServo.attach(9);

void loop(){
  SensordeForca();
  SensorUltrassonico();
  ServoMotor();
  
}

void SensordeForca(){
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
 
  //Esse map eh fantastico!
      LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
  //LED gets brighter the harder you press
      analogWrite(LEDpin, LEDbrightness);
  delay(100);
}

void SensorUltrassonico(){
    // Limpa o trigger
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  // Configurar o trigger para nível alto para transmissão de sinais
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10); // tempo para envio do sinal
  digitalWrite(trigger, LOW);
    
  // Inicia contagem de tempo e lê o pino de eco
  
  duracao = pulseIn(eco, HIGH);
  
  
  // Calcular a distância
  dist = duracao * 0.034 / 2;
  // Mostrar a distância no monitor serial
  if (dist >= 400 || dist <= 2) {
  Serial.println("Valor fora do alcance");
  }
  else {
  Serial.print("Distancia em cm: ");
  Serial.println(dist);
    
  }
  // Aguardar 100ms antes da próxima leitura para evitar interferência
  delay(100);
  }

void ServoMotor(){
  if (Serial.available())
  {
    angulo = Serial.parseInt();
    meuServo.write(angulo);
    delay (2000);
  }
}
