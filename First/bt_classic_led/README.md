# bt_classic_led

<p>
  In order to make an approach to bluetooth management, an activity based on the classic blink is implemented, which through the use of a terminal turns on, off or defines the color of the LED wirelessly.
</p>

## Code

  For the bluetooth configuration the `BluetoothSerial.h` library is used and an object of the `BluetoothSerial` class is defined.

On the other hand, to initialize the object we use the begin method to define the device name.

```C
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  ...
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
```
<p>
  And finally, the loop validates that the bluetooth serial connection is enabled to send and receive messages. And finally, depending on the message received, see will perform one or another action.
</p>

```C
void loop(){
...

 if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    String message = SerialBT.readString();
    ...  
  }
...
}
```




<img src="https://www.electronicshub.org/wp-content/uploads/2021/03/ESP32-Bluetooth-Pairing.jpg" alt="imagen de ejemplo (electronicshub.org)">
