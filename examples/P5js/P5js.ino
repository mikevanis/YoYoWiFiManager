#include <YoYoWiFiManager.h>
#include <YoYoSettings.h>

YoYoWiFiManager wifiManager;
YoYoSettings *settings;

const int LED_RED_PIN = 13;

void setup() {
  Serial.begin(115200);

  settings = new YoYoSettings(512); //Settings must be created here in Setup() as contains call to EEPROM.begin() which will otherwise fail
  wifiManager.init(settings, NULL, onYoYoMessageGET, onYoYoMessagePOST, true);
  wifiManager.begin("YoYoMachines", "blinkblink", false);
  
  pinMode(LED_RED_PIN, OUTPUT);
}

void loop() {
  wifiManager.loop();
}

bool onYoYoMessageGET(JsonVariant message) {
  return(false);
}

bool onYoYoMessagePOST(JsonVariant message) {
  bool success = false;
  
  if(message["path"] == "/yoyo/active") {
    digitalWrite(LED_RED_PIN, message["payload"]["active"].as<bool>());
    success = true;
  }

  return(success);
}