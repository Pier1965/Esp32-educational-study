void updateTimeScr(){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("");
    int16_t x1, y1;
    uint16_t w, h;
    display.setTextSize(2);
    display.getTextBounds(Data, 0, 0, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(64 - w / 2, 8);
    display.println(Data);
    display.setTextSize(4);
    display.getTextBounds(Ora, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(64 - w / 2, 36);
    display.println(Ora);
    display.display();
}
