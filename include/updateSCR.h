void updateSCR(){
    display.clearDisplay();
    display.setCursor(0, 0);
display.setTextSize(1);
    display.println(desc[STATION]);
    display.print("Vol: ");
    display.print(VOLUME);
    display.println("%");
    display.println("");
    display.print("SSID: ");
    display.println(WiFi.SSID());
    display.print("IP: ");
    display.println(WiFi.localIP());
    display.print("Segnale: ");
    display.println(WiFi.RSSI());
    //display.println("");
    display.println(Data);
    display.println(Ora);
    display.display();
}
