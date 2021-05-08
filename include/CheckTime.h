bool checkTime(){
    String ore;
    String Giorno;
    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    if (currentMillis - startMillis >= updateTime){
        startMillis = currentMillis;
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
        return true;
    }
    if (currentMillis - startMillis >= 5*updateTime){
        player.softReset();
        //player.switchToMp3Mode();
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
