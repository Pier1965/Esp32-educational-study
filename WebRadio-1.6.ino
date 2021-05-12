/**
  Ennesima Web radio con ESP32

  Pierpaolo Garofalo - http://pier.unirc.eu
  Licensed under GNU GPL v3

  Wiring:
  ---------------------
  | VS1053  |  ESP32  |
  ---------------------
  |   SCK   |  IO18   |
  |   MISO  |  IO19   |
  |   MOSI  |  IO23   |
  |   XRST  |  EN     |
  |   CS    |  IO5    |
  |   DCS   |  IO0    |
  |   DREQ  |  IO4    |
  |   5V    |  5V     |
  |   GND   |  GND    |
  ---------------------

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
08/05/21
7) Pare risolta questione BBC #208 https://www.youtube.com/watch?v=aMS4XwEr8s0&t=51s Nei commenti di random sporadic projects
8) Aggiunto digit a orari inferiori alle 9
09/05/2021
9) Modificata gestione ora. Se l'orario è stato ottenuto in avvio da NTP non usiamo di nuovo la connessione alla rete
10) Multiwifi per connettersi a piu reti wifi e riconnessione corretta nel caso si perda il collegamento
10/05/21
11) Quando si cambia modalità da Clock a Radio riconnettere wifi e stazione e viceversa
12/05/2021
12) Implementato ring buffer per risolvere Otto Baroque a 320kbps che balbetta... pare funzionare
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
// Routine di lettura stream e feed al VS1053
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
//uint8_t mp3buff[BUFFER];
__attribute__((aligned(4))) uint8_t mp3buff[BUFFER];
// Radio memorizzate e numero NR delle stesse
#include "./include/stations.h"
VS1053 player(VS1053_CS, VS1053_DCS, VS1053_DREQ);
WiFiClient client;
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
#include"./include/connectToWIFI.h"
//Gestione data e ora
#include "time.h"
#include "./include/datetime.h"
#include "./include/updateSCR.h"
#include "./include/updateTimeScr.h"
#include "./include/CheckTime.h"
#include "./include/confSelector.h"
// Inclusione uso Ring Buffer
//#define NORBUFF
#define RBUFF
#ifdef RBUFF
  #include "./include/RBUFF.h"
#endif
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
    DEBUG_PRINTLN("\n\nSimple WiFi Radio");
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
    // Se la levetta è in modalità orologio spegni il wifi
    if(!workingMode()){
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      updateTimeScr();
    }
    oldWMode=WMode;
}

void loop() {
  WMode = workingMode();
  if(oldWMode != WMode){
    oldWMode = WMode;
    if(WMode){
      DEBUG_PRINTLN("Reconnecting...");
      connectToWIFI();
      initTime();
      delay(500);
      connectToStation();
      #ifdef RBUFF
        fillBuff();
      #endif
      delay(1000);
      updateSCR();}
    else{
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      updateTimeScr();}
  }
  if(WMode){
    //Modalità radio
    if (!client.connected()) {
        DEBUG_PRINTLN("Reconnecting...");
        connectToWIFI();
        initTime();
        delay(500);
        connectToStation();
        #ifdef RBUFF
          fillBuff();
        #endif
        delay(1000);
        updateSCR();
    }
    #ifdef NORBUFF
      #include "./include/playNoBuff.h"
    #endif
    #ifdef RBUFF
      #include "./include/playBuff.h"
    #endif
    //Check dei tasti e dei comandi IR
    checkIR();
    switch (checkButtons()) {
      case STNCH:
        connectToStation();
        #ifdef RBUFF
          fillBuff();
        #endif
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
