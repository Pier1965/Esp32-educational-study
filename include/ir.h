#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

//Infrarosso collegato a Pin Esp32
const uint16_t kRecvPin = 26;

// Sensore IR
IRrecv irrecv(kRecvPin);
decode_results results;

void initIR(){
    DEBUG_PRINTLN("Inizializzo sensore IR");
    irrecv.enableIRIn(); // Start the receiver
}

void checkIR(){
  if (irrecv.decode(&results)) {
    //serialPrintUint64(results.value, DEC);
    switch (results.value) {
      case IR_UP:
        DEBUG_PRINTLN("Volume UP");
        if(VOLUME < 100)
          VOLUME+=DVOL;
      break;
      case IR_DN:
        DEBUG_PRINTLN("volume DOWN");
        if(VOLUME>0)
          VOLUME-=DVOL;
      break;
      case IR_NX:
        DEBUG_PRINTLN("Next");
        if(STATION<NR-1)
          STATION++;
        else
          STATION = 0;
        nxtButton = 1;
        prvButton = 0;
      break;
      case IR_PV:
        DEBUG_PRINTLN("PREV");
          if(STATION>0)
            STATION--;
          else
            STATION = NR-1;
          nxtButton = 0;
          prvButton = 1;
      break;
      case IR_RS:
        DEBUG_PRINTLN("RESET");
        delay(1000);
        updateEeprom();
        initMP3Decoder();
        //player.softReset();
        //ESP.restart();
      break;
      default:
        //serialPrintUint64(results.value, HEX);
      break;
    }
    updateEeprom();
    //Serial.println("");
    irrecv.resume();  // Receive the next value
  }
}
