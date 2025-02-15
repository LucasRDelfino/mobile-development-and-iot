#include<DHT.h>
#include<Servo.h>
#include<ArduinoJson.h>

#define dhtPin 2
#define dhtType DHT22
#define trigger 7
#define echo 8
#define ldrPin A0
#define servoPin 9
int dist = 0;
int ldrValor = 0;

DHT dht(dhtPin, dhtType);
Servo servo;

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo.attach(servoPin);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ldrPin, INPUT);

  
}

void loop() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  dist = pulseIn(echo, HIGH);
  dist /= 58;

  int temp = dht.readTemperature();
  int umi = dht.readHumidity();

  ldrValor = analogRead(ldrPin);

  if(dist < 80){
    servo.write(0);
  }else if (dist < 200){
    servo.write(90);
  }else{
    servo.write(180);
  }

  StaticJsonDocument<200>json;

  json["Distancia: "] = dist;
  json["Temperatura: "] = temp;
  json["Umidade: "] = umi;
  json["Luminosidade: "] = ldrValor;
  json["Serco: "] = servo.read();

  serializeJson(json, Serial);

  Serial.println(json.);
  delay(2000);
 
}
