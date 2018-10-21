#include "webserver.h"
#include <ESP8266WebServer.h>
#include "common.h"
#include "user_config.h"
#include "ota.h"
#include <ArduinoJson.h>

#define CONFIG_JSON_PATTERN "{\"color\" : {\"r\": %d,\"g\":%d,\"b\":%d},\"autoupdate\":{\"enabled\":%d,\"interval\":%d},\"animationTimeMs\":%d }"

ESP8266WebServer server(80);
const char* ROOT_PAGE = STATIC_PAGE_HOME;

void readConfig()
{
  char temp[200];
  int r = globalState.userSetColor[0];
  int g = globalState.userSetColor[1];
  int b = globalState.userSetColor[2];
  sprintf(temp, CONFIG_JSON_PATTERN, r, g, b, globalState.isAutoChangeColor, globalState.updateInternalSeconds, globalState.animationTimeMs);
  server.send(200, "application/json", temp);
}

void handleConfig()
{
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(server.arg("plain"), 3);
  write_to_log(server.arg("plain"));

  if (!root.success())
  {
    write_to_log(server.arg("plain"));
    write_to_log("parseObject() failed");
    return;
  }
  globalState.userSetColor[0] = root["color"]["r"];
  globalState.userSetColor[1] = root["color"]["g"];
  globalState.userSetColor[2] = root["color"]["b"];
  int temp = root["autoupdate"]["enabled"];
  globalState.isAutoChangeColor = (temp == 1);
  globalState.updateInternalSeconds = root["autoupdate"]["interval"];
  if (root["animationTimeMs"])
  {
    globalState.animationTimeMs = root["animationTimeMs"];
  }
  globalState.version++;
  server.send(200, "text/plain", "ok");
}

void handleNotFound()
{
  write_to_log("not found \"%s\"", server.uri().c_str());
  server.send(404, "text/plain", "not found");
}

void handleLog()
{
  server.send(200, "text/plain", read_log_buffer());
}

void handleOta()
{
  is_ota_enabled = !is_ota_enabled;
  char temp[10];
  sprintf(temp, "{\"ota\" : %d}", is_ota_enabled);
  server.send(200, "application/json", temp);
}

void handleRestart()
{
  write_to_log("Restarting due to API request");
  ESP.restart();
}


//static pages
void handleHome()
{
  server.send(200, "text/html", ROOT_PAGE);
}

void setupWebServer()
{
  server.on("/log", handleLog);
  server.on("/api/ota", handleOta);
  server.on("/api/config", HTTP_POST, handleConfig);
  server.on("/api/config", HTTP_GET, readConfig);
  server.on("/api/rst", handleRestart);
  //static
  server.on("/", handleHome);
  server.on("/home", handleHome);
  server.onNotFound(handleNotFound);
  server.begin();
  write_to_log("Web server listening");
}

void loopWebServer()
{
  server.handleClient();
}
