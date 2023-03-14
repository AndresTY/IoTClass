
struct Button {
    const uint8_t PIN;
};

hw_timer_t *Timer0_Cfg = NULL;
Button button1 = {18};
Button button2 = {23};


unsigned long button_time = 0;  
unsigned long last_button_time = 0; 
const int motor1 = 21;
const int motor2 = 19;

void IRAM_ATTR Timer0_ISR()
{
    if (digitalRead(motor1) == 1)
      digitalWrite(motor1, LOW);
    if (digitalRead(motor2) == 1)
      digitalWrite(motor2, LOW);
}

void IRAM_ATTR banda() {
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
        digitalWrite(motor1,HIGH);
        timerAlarmWrite(Timer0_Cfg, timerReadMicros(Timer0_Cfg)+5000000, false);
        timerAlarmEnable(Timer0_Cfg);
        last_button_time = button_time;
  }
}

void IRAM_ATTR door() {
  button_time = millis();
  if (button_time - last_button_time > 250)
  {
        digitalWrite(motor2,HIGH);
        timerAlarmWrite(Timer0_Cfg, timerReadMicros(Timer0_Cfg)+5000000, false);
        timerAlarmEnable(Timer0_Cfg);
        last_button_time = button_time;
  }
}

void setup() {
    Serial.begin(115200);

    Timer0_Cfg = timerBegin(0, 80, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    
    pinMode(motor1,OUTPUT);
    pinMode(motor2,OUTPUT);
    pinMode(button1.PIN, INPUT);
    attachInterrupt(button1.PIN, banda, FALLING);
    pinMode(button2.PIN, INPUT);
    attachInterrupt(button2.PIN, door, FALLING);
}

void loop() {
}