struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
    int sensor_values;
};

Button button1 = {18, 0, false,0};

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 
const int ldr = 27;

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

void setup() {
    Serial.begin(115200);
    pinMode(ldr,INPUT);
    pinMode(button1.PIN, INPUT_PULLUP);
    attachInterrupt(button1.PIN, isr, FALLING);
}

void loop() {
    if (button1.pressed) {
        Serial.printf("Button has been pressed %u times and sensor %d\n", button1.numberKeyPresses,button1.sensor_values);
        button1.pressed = false;
    }
}