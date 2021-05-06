WiFiClient client;

void connectToWIFI()
  {
    DEBUG_PRINT("Connecting to SSID ");
    DEBUG_PRINTLN(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        DEBUG_PRINTLN(".");
    }

    DEBUG_PRINT("WiFi connected to ");
    DEBUG_PRINTLN(ssid);
    DEBUG_PRINT("Local esp32 IP address: ");
    DEBUG_PRINTLN(WiFi.localIP());

  }
