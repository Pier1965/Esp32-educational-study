bool checkTime(){
    String ore;
    String Giorno;
    currentMillis = millis();  //che ore sono?
    if (currentMillis - startMillis >= updateTime){ //è ora di aggiornare l'ora?
        startMillis = currentMillis;
        if(gotTime){ //Il tentativo di inizializzare l'ora ha avuto successo all'accensione?
            initTime(); // No... riproviamo
        }else{
            time(&now); // Si aggiorniamo senza ricontattare il server NTP
            localtime_r(&now, &timeinfo);
        }
        if(timeinfo.tm_mday<10)
            Giorno = "0" + String(timeinfo.tm_mday);
        else
            Giorno = String(timeinfo.tm_mday);
        Data = dow[timeinfo.tm_wday] + " " + Giorno + " " +  months[timeinfo.tm_mon];
        if(timeinfo.tm_hour<10)
            ore = "0" + String(timeinfo.tm_hour);
        else
            ore = String(timeinfo.tm_hour);
        if(timeinfo.tm_min<10)
            minuti = "0" + String(timeinfo.tm_min);
        else
            minuti = String(timeinfo.tm_min);
        Ora = ore + ":" + minuti;

        DEBUG_PRINTLN("Time from Internet  ");
        DEBUG_PRINT(Data);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(Ora);
        return true;
    }
    return false;
}

void setTime(){
        String ore;
        String Giorno;
        getLocalTime(&timeinfo);
        if(timeinfo.tm_mday<10)
            Giorno = "0" + String(timeinfo.tm_mday);
        else
            Giorno = String(timeinfo.tm_mday);
        Data = dow[timeinfo.tm_wday] + " " + Giorno + " " +  months[timeinfo.tm_mon];
        if(timeinfo.tm_hour<10)
            ore = "0" + String(timeinfo.tm_hour);
        else
            ore = String(timeinfo.tm_hour);
        if(timeinfo.tm_min<10)
            minuti = "0" + String(timeinfo.tm_min);
        else
            minuti = String(timeinfo.tm_min);
        Ora = ore + ":" + minuti;
        //updateSCR();
        DEBUG_PRINTLN("Time from Internet  ");
        DEBUG_PRINT(Data);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(Ora);
}
