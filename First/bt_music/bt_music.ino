#include "BluetoothA2DPSource.h"
#include "waves.h"
#include <math.h> 

BluetoothA2DPSource a2dp_source;


SoundData *music = new TwoChannelSoundData((Frame*)waves, waves_len, true);
void setup() {
  Serial.begin(115200);
  a2dp_source.start("HOPESTAR-H11"); 
  a2dp_source.write_data(music);
  a2dp_source.set_volume(75);
  pinMode(2,OUTPUT);
}

void loop() {
  Serial.print("has sound data: ");
  Serial.println(a2dp_source.has_sound_data());
  Serial.print("Volumen ");
  Serial.println(a2dp_source.get_volume());
  if (a2dp_source.is_connected() == 0){
digitalWrite(2,LOW);
  }else{
    digitalWrite(2,HIGH);
  }
  delay(100);
}