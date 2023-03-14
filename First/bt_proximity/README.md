# bt_proximity

The ESP32 scans the available devices on the bluetooth connection, and displays the characteristics of these devices.

## BLE

Bluetooth Low Energy (Bluetooth LE, colloquially BLE, formerly marketed as Bluetooth Smart) is a wireless personal area network technology designed and marketed by the Bluetooth Special Interest Group (Bluetooth SIG) aimed at novel applications in the healthcare, fitness, beacons, security, and home entertainment industries. 

## RSSI

received signal strength indicator (RSSI) is a measurement of the power present in a received radio signal.

RSSI is usually invisible to a user of a receiving device. However, because signal strength can vary greatly and affect functionality in wireless networking, IEEE 802.11 devices often make the measurement available to users. 

<img src="https://www.speedtest.pl/wiadomosci/wp-content/uploads/2018/02/rssi-signal-thresholds.jpg">

## Code 

With the help of BLE, a scan object is defined, which will be in charge of scanning the available devices.

As it does not have to connect to the devices but only obtain the MAC address and RSSI, an unnamed BLE object is defined and the scan is activated.

```C
BLEScan *scan = BLEDevice::getScan();

void setup() {
  ...
  BLEDevice::init("");
  scan->setActiveScan(true);
}
```

On the other hand, the loop generates a scan every 10 seconds that returns the number of devices detected and also prints the characteristics of the devices found. 

In the case, if its RSSI is better than the defined `CUTOFF` the led will light up showing that the device is close. 

```C

void loop() {
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
```

## Notes

Smartphones use “private resolvable random addresses” which can be changed as frequently as desired and that happens to protect the privacy of the user as the phone cannot be tracked for long.

The purpose of a Resolvable Random Private Address is to prevent malicious third-parties from tracking a Bluetooth device while still allowing one or more trusted parties from identifying the Bluetooth device of interest.
