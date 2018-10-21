#include <Arduino.h>
#include "wifi.h"
#include "ota.h"
#include "common.h"
#include "user_config.h"
#include "strip.h"
#include "webserver.h"

void setup() {
  setupCommon();
  setupStrip();
  setupWifi();
  setupOta();
  setupWebServer();
}

void loop() {
  loopWifi();
  loopOta();
  loopStrip();
  loopWebServer();
  delay(5);
}
