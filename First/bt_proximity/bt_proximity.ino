#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define PIN 2
#define CUTOFF -60

BLEScan *scan = BLEDevice::getScan();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN,OUTPUT);
  BLEDevice::init("");
  scan->setActiveScan(true);
}

void loop() {
  // put your main code here, to run repeatedly:  
  BLEScanResults results = scan->start(10);
  int best = CUTOFF;
  for (int i =0; i<results.getCount(); i++){
    Serial.println(results.getDevice(i).toString().c_str());
    if (results.getDevice(i).getRSSI() > best){
      best = results.getDevice(i).getRSSI();
    }
    
  }

  scan->clearResults();
  digitalWrite(PIN, best > CUTOFF ? HIGH : LOW);
}
