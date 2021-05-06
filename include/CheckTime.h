bool checkTime(){
    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    if (currentMillis - startMillis >= updateTime){
        startMillis = currentMillis;
        getLocalTime(&timeinfo);
        Data = dow[timeinfo.tm_wday] + " " + String(timeinfo.tm_mday) + " " +  months[timeinfo.tm_mon];
        Ora = String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min);
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
