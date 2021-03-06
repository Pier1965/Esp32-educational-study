#include <EEPROM.h>
// incremento volume click
#define DVOL 5
int STATION = 0;
int OLDSTATION = STATION;
int nxtButton = 1;
int prvButton = 0;
int VOLUME = 90;
int OLDVOLUME = VOLUME;
// gestione valori in flash eeprom
// memorizziamo STATION e VOLUME
#define EEPROM_SIZE 2
void restoreEeprom(){
    // gestione pulsanti
    DEBUG_PRINTLN("Recupero i dati di volume e stazione da eprom");
    EEPROM.begin(EEPROM_SIZE);
    STATION = EEPROM.read(0);
    if(STATION > NR-1){
        STATION = 0;
        EEPROM.write(0, STATION);
    }
    OLDSTATION = STATION;
    nxtButton = 1;
    prvButton = 0;
    // Default volume
        VOLUME = EEPROM.read(1);
    if(VOLUME > 100){
        VOLUME = 100;
        EEPROM.write(1, VOLUME);
    }
    OLDVOLUME = VOLUME;
    EEPROM.commit();
}

void updateEeprom(){
    EEPROM.write(0, STATION);
    EEPROM.write(1, VOLUME);
    EEPROM.commit();
}
