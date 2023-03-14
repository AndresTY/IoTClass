# bt_music

Another of the possibilities of Bluetooth is the transfer of data between devices. 

In this work, the ESP32 will be used to send music to a speaker via Bluetooth.

## Code

A song can be represented with an array of values that represent the value of the wave that generates the sound, thanks to this a `waves.h` file is made where the array with the values and the length of this array is found.

```C
extern const int waves_len=10000;

extern const unsigned char waves[] = {128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
...
};
```

In the `bt_music.ino` file, the music file is imported and a SoundData object is generated. In this case, the object has two channels and is initialized with an array, its length, and a boolean value indicating whether the music should be repeated or not.

Finally, in the `setup` method, it automatically connects to the speaker and sends the music for the speaker to play at its respective volume.

```C
SoundData *music = new TwoChannelSoundData((Frame*)waves, waves_len, true);
void setup() {
  Serial.begin(115200);
  a2dp_source.start("HOPESTAR-H11"); 
  a2dp_source.write_data(music);
  a2dp_source.set_volume(75);
  pinMode(2,OUTPUT);
}
```
