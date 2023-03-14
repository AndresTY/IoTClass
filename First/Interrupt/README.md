# Interruptions

An interrupt is a request to the processor to interrupt the currently executing code (when allowed), so that the event can be processed in time, without constantly reading an input.

# Code 

A button structure is defined, with important circuit characteristics.

In this case, the function will modify the values of the defined structure, increasing the number of clicks made and the value of the photoresistor during the interruption.

```C
struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
    int sensor_values;
};

Button button1 = {18, 0, false,0};

...

void IRAM_ATTR isr() {
  button1.sensor_values = analogRead(ldr);
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
          button1.numberKeyPresses++;
          button1.pressed = true;
        last_button_time = button_time;
  }
}
```

Finally, in the setup, the port type and the action required to affect the interrupt are configured. And if the button is pressed and the interrupt is executed, it will display the properties of the `button` structure in the Serial terminal (115200).

```C

void setup() {
    ...
    pinMode(button1.PIN, INPUT_PULLUP);
    attachInterrupt(button1.PIN, isr, FALLING);
}
```

## Circuit

<img src="Interrupt/circuito.png">
