/**
  Ennesima Web radio con ESP32

  Pierpaolo Garofalo - http://pier.unirc.eu
  Licensed under GNU GPL v3

  Wiring:
  --------------------------------
  | VS1053  | ESP8266 |  ESP32   | VS1053 Rosso
  --------------------------------
  |   SCK   |   D5    |   IO18   | SCK
  |   MISO  |   D6    |   IO19   | MISO
  |   MOSI  |   D7    |   IO23   | MOSI
  |   XRST  |   RST   |   EN     | X_RESET
  |   CS    |   D1    |   IO5    | X_CS
  |   DCS   |   D0    |   IO0    | X_DCS
  |   DREQ  |   D3    |   IO4    | DREQ (Terzo pin)
  |   5V    |   5V    |   5V     |
  |   GND   |   GND   |   GND    |
  --------------------------------

  ---------------------------
  | JMDO 96C-1 OLED | ESP32 |
  ---------------------------
  | SDA             | 21    |
  | SCL             | 22    |
  | GND             | GND   |
  | 5V              | 5V    |
  ---------------------------

  ---------------------------
  | IR module elegoo | ESP32 |
  ---------------------------
  | G                | GND   |
  | R                | 5V    |
  | Y                | G26   |
  ----------------------------

  ----------------------------
  | Pulsanti         | ESP32  |
  ----------------------------
  | Vol UP           | G32    |
  | Vol Down         | G33    |
  | Next Station     | G13    |
  | Prv Station      | G12    |
  | Radio-Clock Sel  | G36    |
  ----------------------------

27/04/2021
1) Gestisce immissione cambio stazioni e volume tramite pulsanti HW con debouncing SW e HW  (v)
2) Memorizza Stazion e Volume in eeprom                                                     (v)
Otto baroque si sente a volte bene e a volte con singhiozzo a buffer 64, con 32 pare liscio
28/04/2021
3) Interfaccia OLED con info rete e canale                                                  (v)
4) Telecomando IR di vari tipi per cambio stazione e volume                                 (v)
5) Orario e data in OLED                                                                    (v)
01/05/2021
6) Modalità radio oppure orologio

*/
//#define DEBUG
#ifdef DEBUG
  #define DEBUG_PRINT(x)     Serial.print (x)
  #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x)
#endif
//
// gestione pin IO
#include "./include/gpio.h"
#include <VS1053.h>
// incremento volume click
#define DVOL 5
// Valori ritornati da cambio stazione o volume
#define STNCH 1
#define VOLCH 2
// dimensione buffer Otto Baroque con 32 non singhiozza
#define BUFFER 32
uint8_t mp3buff[BUFFER];
// Radio memorizzate e numero NR delle stesse
#include "./include/stations.h"
VS1053 player(VS1053_CS, VS1053_DCS, VS1053_DREQ);
// Recupero di dati di volume e stazione da eeprom. Si serve di NR
#include"./include/Eeprom.h"
// Gestione OLED SSD1306 128x64
#include "./include/oled.h"
#include"./include/connectToStation.h"
// Funzione di controllo della variazione dei valori di Volume e Stazione gestiti da interrupt
#include"./include/checkButtons.h"
// Gestione interrupt pulsanti
#include"./include/interrupt.h"
#include"./include/initMp3Decoder.h"
//Codici telecomandi IR
#include "./include/ir_butt.h"
#include "./include/ir.h"
// WiFi settings
const char *ssid = "SSSR65";
const char *password = "38314447668501196816";
#include"./include/connectToWIFI.h"
//Gestione data e ora
#include "./include/datetime.h"
#include "./include/updateSCR.h"
#include "./include/updateTimeScr.h"
#include "./include/CheckTime.h"
#include "./include/confSelector.h"
///////////////////////////////////////

void setup() {
    Serial.begin(115200);
    SPI.begin();
    restoreEeprom();
    //Setup OLED : Strano... se messo dopo setupInt fa incartare l'ascolto
    initSCR();
    //nizializzazione MP3 decoder
    initMP3Decoder();
    // Wait for VS1053 and PAM8403 to power up
    // otherwise the system might not start up correctly
    delay(3000);
    DEBUG_PRINTLN("\n\nSimple Radio Node WiFi Radio");
    // Setup delle routine di interrupt per i tasti stazone e volume
    setupInt();
    //Setup del modo di funzionamento
    confSelector();
    WMode = workingMode();
    //Inizializza sensore IR
    initIR();
    //Connessione alla rete wifi e recupero data e ora
    connectToWIFI();
    initTime();
    //Connessione all'ultima stazione ascoltata prima dello spegnimento
    //connectToStation();
    if(workingMode()){
      updateSCR();
    }else{
       updateTimeScr();
    }
    oldWMode=WMode;
    //VOLUME=90;
    //STATION=9;
}

void loop() {
  WMode = workingMode();
  if(oldWMode != WMode){
    oldWMode = WMode;
    if(WMode)
      updateSCR();
    else
      updateTimeScr();
  }
  if(WMode){
    //Modalità radio
    if (!client.connected()) {
        DEBUG_PRINTLN("Reconnecting...");
        connectToStation();
        updateSCR();
    }
    if (client.available() > 0) {
        uint8_t bytesread = client.read(mp3buff, BUFFER);
        player.playChunk(mp3buff, bytesread);
    }
    //Check dei tasti e dei comandi IR
    checkIR();
    switch (checkButtons()) {
      case STNCH:
        connectToStation();
        updateSCR();
      break;
      case VOLCH:
        player.setVolume(VOLUME);
        updateSCR();
      break;
    }
    if(checkTime()){
      updateSCR();
    }
  }else{
    //Modalità orologio
    if(checkTime()){
      updateTimeScr();
    }
  }
}
