#include <Arduino.h>
#include "common.h"
#include "user_config.h"

int rgbPins[3] = {LED_STRIP_PIN_R, LED_STRIP_PIN_G, LED_STRIP_PIN_B};
int currentPin = 0;
unsigned long lastChange = 0;

void setupStrip()
{
    for (int i = 0; i < 3; i++)
    {
        pinMode(rgbPins[i], OUTPUT);
    }
}

void loopStrip()
{
    unsigned long l = millis() - lastChange;
    if (l < 10)
    {
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        int pin = rgbPins[i];
        bool b = (i == currentPin);
        if (!b)
        {
            digitalWrite(pin, b);
        }
        else
        {
            analogWrite(pin, l);
        }
    }
    if (l >= 1024)
    {
        currentPin++;
        if (currentPin > 2)
        {
            currentPin = 0;
        }
        lastChange = millis();
    }

}