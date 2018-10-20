#include "common.h"
#include "wifi.h"
#include "user_config.h"
#include <ESP8266mDNS.h>

#define WIFI_CONNECTION_DELAY_MS 500
unsigned long lastWifiConnectionAttempt = 0;
bool isMdnsSet = false;



void loopWifi() {
  if (isMdnsSet) {
    return;
  }
  if (WiFi.status() == WL_CONNECTED) {
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
  // write_to_log("Connected to WiFi. Local IP is " + WiFi.localIP().toString());
}


void setupWifi() {
  WiFi.hostname(HOST_NAME);
  WiFi.mode(WIFI_STA);
  #ifdef IP_ADDR
  IPAddress ip(IP_ADDR);
  IPAddress gateway(IP_GW);
  IPAddress subnet(IP_SUBNET);
  WiFi.config(ip, gateway, subnet);
  #endif

  WiFi.begin(WIFI_SSID, WIFI_PSWD);
}
