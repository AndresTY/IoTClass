#include <DHT.h>
#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"

#define lightInit 15
#define LED 2
#define DHTPIN 27
#define ROTARY_ENCODER_A_PIN 23
#define ROTARY_ENCODER_B_PIN 22
#define ROTARY_ENCODER_BUTTON_PIN 21
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4


/* DHT11 */
DHT dht(DHTPIN, DHT11);

struct temperature{
 float temperatura;
 float humedad;
};

temperature readDHT() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  struct temperature temp;
  temp.temperatura = t;
  temp.humedad = h;
  return temp;
}

void led(){
  int a = zelda();
  Serial.println(a);
  if(a<=1300){
    digitalWrite(LED,HIGH);
  }else{
    digitalWrite(LED,LOW);
  }
}

int zelda(){
  int a  = analogRead(lightInit);
  return a;
}

/* rotary encode */
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

void rotary_onButtonClick()
{
    static unsigned long lastTimePressed = 0; // Soft debouncing
    if (millis() - lastTimePressed < 500)
    {
            return;
    }
    lastTimePressed = millis();
    Serial.print("button pressed ");
    Serial.print(millis());
    Serial.println(" milliseconds after restart");
}

void rotary_loop()
{
  
    //dont print anything unless value changed
    if (rotaryEncoder.encoderChanged())
    {
            Serial.print("New Value: ");
            Serial.println(rotaryEncoder.readEncoder());
    }
    if (rotaryEncoder.isEncoderButtonClicked())
    {
            rotary_onButtonClick();
    }
    Serial.print("Value: ");
    Serial.print(rotaryEncoder.readEncoder());
    Serial.print("  click: ");
    Serial.println(rotaryEncoder.isEncoderButtonDown());
}

void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}


/* setup */

void setup(){
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(lightInit,INPUT);
  dht.begin();
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  bool circleValues = false;
  rotaryEncoder.setBoundaries(0, 1000, circleValues);
  rotaryEncoder.setAcceleration(250);
}

void loop(){
  struct temperature aux = readDHT();
  Serial.printf("%f -- %f \n",aux.temperatura,aux.humedad);
  led();
  rotary_loop();
  delay(50);
}