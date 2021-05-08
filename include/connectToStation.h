void connectToStation()
{
    #ifdef USEBUFFER
        resetBuff();
    #endif
    player.softReset();
    //player.switchToMp3Mode();
    DEBUG_PRINT("Connecting to ");
    DEBUG_PRINTLN(desc[STATION]);
  if (!client.connect(host[STATION], port[STATION])) {
    DEBUG_PRINTLN("Connection failed");
    DEBUG_PRINT("Canale non raggiungibile...");
    printSCR_notavail();
    delay(1000);
    if (nxtButton == 1){
      if(STATION < NR-1){
        STATION++;
      }else{
        STATION = 0;
      }
    }else{
      if(STATION > 0){
        STATION--;
      }else{
        STATION = NR-1;
      }
    }
    return;
  }

    DEBUG_PRINTLN(host[STATION]);
    DEBUG_PRINT("Requesting stream: ");
    DEBUG_PRINTLN(path[STATION]);

    /*client.print(String("GET ") + path[STATION] + " HTTP/1.1\r\n" +
                 "Host: " + host[STATION] + "\r\n" +
                 "Connection: close\r\n\r\n");*/
    //Cambiato HTTP 1.1 in HTTP 1.0 per risolvere problema BBC
    client.print(String("GET ") + path[STATION] + " HTTP/1.0\r\n" +
                 "Host: " + host[STATION] + "\r\n" +
                 "Connection: close\r\n\r\n");
delay(2000);
}
