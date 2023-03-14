#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int RED = 12;
int GREEN = 23;
int BLUE = 22;

void setup() {
  pinMode (RED, OUTPUT);
  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);


  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    String message = SerialBT.readString();
    //Serial.write(SerialBT.read());
    if(message=="red"){
      
     // SerialBT.write("Led ON");
     if(digitalRead(RED)==HIGH){
       digitalWrite(RED, LOW);
       

     }
     else{
       digitalWrite(RED, HIGH);
     }

    }
  

    else if (message=="green"){
     if(digitalRead(GREEN)==HIGH){
       digitalWrite(GREEN, LOW);
       

     }
     else{
       digitalWrite(GREEN, HIGH);
     }
      
    }
  
    else if (message=="blue"){
      if(digitalRead(BLUE)==HIGH){
       digitalWrite(BLUE, LOW);
       

     }
     else{
       digitalWrite(BLUE, HIGH);
     }
      
    }
    

    else if (message=="on"){
     digitalWrite(GREEN, HIGH);
     digitalWrite(RED, HIGH);
     digitalWrite(BLUE, HIGH);
    // SerialBT.write("Led OFF");
      
    }
    else if (message=="off"){
     digitalWrite(GREEN, LOW);
     digitalWrite(BLUE, LOW);
     digitalWrite(RED, LOW);
    // SerialBT.write("Led OFF");
      
    }

  }
  delay(20);
}