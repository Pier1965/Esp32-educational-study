#include "./wifi_ssid.h"
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

void connectToWIFI(){
    for(int i=0; i<Nssid; i++)
        wifiMulti.addAP(ssid[i], password[i]);
    delay(500);
/*
    for(int i=0; i<Nssid; i++){
        WiFi.begin(host[n], [n]);

    }
*/

    while(wifiMulti.run() != WL_CONNECTED) {
        printSCR_attesaWL();
        delay(1000);
        yield();
    }

    DEBUG_PRINT("WiFi connected to ");
    DEBUG_PRINTLN(WiFi.SSID());
    DEBUG_PRINT("Local esp32 IP address: ");
    DEBUG_PRINTLN(WiFi.localIP());
    DEBUG_PRINTLN("");
/*
    bool success = Ping.ping("www.google.com", 3);
    if(!success){
        printSCR_yesnet();
        delay(1000);
    }else{
        printSCR_nonet();
        delay(1000);
    }
*/
}

void checkWiFi(){
    if(wifiMulti.run() != WL_CONNECTED){
        connectToWIFI();
    }
}
