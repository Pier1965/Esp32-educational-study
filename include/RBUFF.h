// Gestione del ring buffer
//
// Variabili gestione buffer
// Dimensione del buffer: 1 second a 320kbit stereo: 1sec*320kbit*2ch*1024/8 = 81920 byte
// microprocessore a 32 bit: allineamento a 4 byte -> 20480 blocchi da 32 byte
// Ragiono su un buffer pieno al 50% per assecondare 1/2 sec di over e under feed
// Variabili
// Dimensione del buffer in byte
#define RNGBFSZ 82000//81920
#define MAXBF RNGBFSZ/1
#define updateTbuff 1000
uint32_t timeTbuff = 0;
//#define BUFFER 32
// puntatore al blocco di bytes da mandare l VS1053
// Allocazione del ring buffer
__attribute__((aligned(4))) uint8_t rngbuf[RNGBFSZ*sizeof(uint8_t)];
// Segnaposto inizio lettura da sommare al puntatore p_rngbuf
uint32_t rbr_index = 0;
// Segnaposto inizio scrittura da sommare al puntatore p_rngbuf
uint32_t rbw_index = 0;
// Byte memorizzati nel buffer non ancora letti rbw_index - rbr_index
uint32_t rcount = 0;

// Funzioni
// Reset del buffer
void resetBuff(){
    rbr_index = 0;
    rbw_index = 0;
    rcount = 0;
}
// Legge il buffer
uint8_t leggiBuff(){
    uint8_t b = rngbuf[rbr_index];
    rcount--;
    rbr_index++;
    if(rbr_index == RNGBFSZ)
        rbr_index = 0;
    return b;
}
// Scrivi nel buffer
void scriviBuff(uint8_t b){
    rngbuf[rbw_index] = b;
    rbw_index++;
    if(rbw_index == RNGBFSZ)
        rbw_index = 0;
    rcount++;
}
// Spazio libero nel buffer?
inline bool isBuffFree(){
    return(rcount < RNGBFSZ);
}
// Spazio occupato nel buffer
inline uint32_t buffTaken(){
    return(rcount);
}
// Riempio buffer al 50% al cambio di stazione
void fillBuff(){
    uint8_t tmp_b[1];
    resetBuff();
    while ((client.available() > 0) && (buffTaken()<MAXBF) ) {
        uint8_t bytesread = client.read(tmp_b, 1);
        scriviBuff(tmp_b[0]);
        //yield();
    }
}
