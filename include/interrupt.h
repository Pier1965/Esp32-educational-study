////////////////////////////////////////////////
// Debouncing parameters
long debT = 200; //Debouncing Time in Milliseconds
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR previousButtonInterrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(STATION>0)
                STATION--;
            else
                STATION = NR-1;
            last_interrupt_time = interrupt_time;
            nxtButton = 0;
            prvButton = 1;
        }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR nextButtonInterrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(STATION<NR-1)
                STATION++;
            else
                STATION = 0;
            nxtButton = 1;
            prvButton = 0;
            last_interrupt_time = interrupt_time;
        }
    portEXIT_CRITICAL_ISR(&mux);
}


// Gestione pulsanti via interrupt regolazione volume

void IRAM_ATTR volumeDownInterrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(VOLUME>0)
                VOLUME-=DVOL;
            last_interrupt_time = interrupt_time;
        }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR volumeUpInterrupt(){
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(VOLUME<100)
                VOLUME+=DVOL;
                last_interrupt_time = interrupt_time;
        }
    portEXIT_CRITICAL_ISR(&mux);
}
// Gestione pulsanti via interrupt cambio canale

void setupInt(){
  pinMode(previousButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(previousButton), previousButtonInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(nextButton), nextButtonInterrupt, FALLING);

  pinMode(volumeUp, INPUT_PULLUP);
  pinMode(volumeDown, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(volumeUp), volumeUpInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(volumeDown), volumeDownInterrupt, FALLING);
}
