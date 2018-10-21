#include <Arduino.h>
#include "common.h"
#include "user_config.h"

int rgbPins[3] = {LED_STRIP_PIN_R, LED_STRIP_PIN_G, LED_STRIP_PIN_B};
int lastColor[3] = {0, 0, 0};
int currentColor[3] = {0, 0, 0};
int targetColor[3];
unsigned long lastChange = 0;
unsigned int lastGlobalStateVersionHandled = 0;

void chooseRandomTargetColor()
{
    for (int i = 0; i < 3; i++)
    {
        targetColor[i] = rand() % PWMRANGE;
    }
    // write_to_log("set random color (%d,%d,%d)", targetColor[0], targetColor[1], targetColor[2]);
}

void setupStrip()
{
    for (int i = 0; i < 3; i++)
    {
        pinMode(rgbPins[i], OUTPUT);
        digitalWrite(rgbPins[i], true);
        delay(300);
        digitalWrite(rgbPins[i], false);
        targetColor[i] = globalState.userSetColor[i];
    }
    lastGlobalStateVersionHandled = globalState.version;
}

void loopStrip()
{
    if (globalState.version > lastGlobalStateVersionHandled)
    {
        for (int i = 0; i < 3; i++)
        {
            targetColor[i] = globalState.userSetColor[i];
            lastColor[i] = currentColor[i];
        }
        lastGlobalStateVersionHandled = globalState.version;
        lastChange = millis();
        return;
    }
    unsigned long l = millis() - lastChange;
    if (l <= globalState.animationTimeMs)
    {
        for (int i = 0; i < 3; i++)
        {
            int pin = rgbPins[i];
            int delta = targetColor[i] - currentColor[i];
            int step = int(delta * (l / float(globalState.animationTimeMs)));
            int newPwm = currentColor[i] + step;
            currentColor[i] = newPwm;
            analogWrite(pin, newPwm);
        }
    }
    if (globalState.isAutoChangeColor && l >= globalState.updateInternalSeconds * 1000)
    {
        for (int i = 0; i < 3; i++)
        {
            currentColor[i] = targetColor[i];
        }
        chooseRandomTargetColor();
        lastChange = millis();
    }
}