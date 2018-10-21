#include "common.h"
#include "wifi.h"
#include "user_config.h"
#include <ESP8266mDNS.h>
#include <WiFiManager.h>

#define WIFI_CONNECTION_DELAY_MS 500
unsigned long lastWifiConnectionAttempt = 0;
bool isMdnsSet = false;

void loopWifi()
{
  if (isMdnsSet)
  {
    return;
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    MDNS.begin(HOST_NAME);
    isMdnsSet = true;
  }
  // unsigned long l = millis() - lastWifiConnectionAttempt;
  // if (l<WIFI_CONNECTION_DELAY_MS) {
  //   return;
  // }
  // WiFi.conn
  // while (WiFi.waitForConnectResult() != WL_CONNECTED) {
  //   write_to_log("Connection Failed! Rebooting...");
  //   delay(WIFI_CONNECTION_DELAY_MS);
  //   ESP.restart();
  // }
  write_to_log("Connected to WiFi. Local IP is " + WiFi.localIP().toString());
}

void setupWifi()
{
  WiFiManager wifiManager;
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.autoConnect("RoyLightAP");
  write_to_log(wifiManager.getConfigPortalSSID());
}