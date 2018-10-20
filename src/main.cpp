#include <Arduino.h>
#include "wifi.h"
#include "ota.h"
#include "common.h"
#include "user_config.h"
#include "strip.h"

void setup() {
  setupCommon();
  setupWifi();
  setupOta();
  setupStrip();
}

void loop() {
  loopWifi();
  loopOta();
  loopStrip();
  delay(5);
}
