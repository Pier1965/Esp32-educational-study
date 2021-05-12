///////////////////////////////////////////////////////////
// buffer allineato mandato al player VS1053
///////////////////////////////////////////////////////////
//static __attribute__((aligned(4))) uint8_t buf[BUFFER];
// Riempio il buffer un byte alla volta se ci sono dati disponibili e c'è spazio
if ((client.available() > 0) && ((RNGBFSZ-buffTaken())>BUFFER)) {
    uint8_t bytesread = client.read(mp3buff, BUFFER);
    for(int i=0; i<bytesread; i++){
        scriviBuff(mp3buff[i]);
        //yield();
    }
}

if( player.data_request() && (rcount != 0)){
    int i = 0;
    while((i != BUFFER) && (rcount != 0)){
        mp3buff[i] = leggiBuff();
        i++;
    }
    player.playChunk(mp3buff, i);
}
#ifdef DEBUG
    if((millis()-timeTbuff)>updateTbuff){
        timeTbuff=millis();
        Serial.println(buffTaken());
    }
#endif
