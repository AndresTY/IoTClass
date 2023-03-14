#include "model2.h"

void setup() {
    Serial.begin(115200);

    while (!model2.begin()) {
        Serial.print("Error in NN initialization: ");
        Serial.println(model2.getErrorMessage());
    }
}

void loop() {
    for (int i = 0; i < 20; i++) {
        float x =  rand() % 100;
        float y =  rand() % 100;
        // even if the input vector is made of a single value
        // you ALWAYS need to create an array
        float input[2] = {x,y};

        float y_true = sqrt(pow(x,2)+pow(y,2));
        // to run the network, call `predict()`
        float y_pred = model2.predict(input);

        Serial.print("x = ");
        Serial.print(x);
        Serial.print("\t y = ");
        Serial.print(y);
        Serial.print("\t r = ");
        Serial.print(y_true);
        Serial.print("\t predicted: ");
        Serial.println(y_pred);
        delay(1000);
    }
}