#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
// Esp32:   SDA -> G21, SCL -> G22
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/*
#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
*/

void initSCR() {
  DEBUG_PRINTLN("Inizializzo OLED");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    DEBUG_PRINTLN(F("SSD1306 allocation failed... System locked"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("WR PPPC65");
   //display.setCursor(0, 1);
  display.print("Marzo 2021");
  display.display();
  delay(1000);
}


void printSCR_notavail(){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Canale non disponibile...");
    //lcd.setCursor(0, 1);
    display.print("Riconnessione...");
    display.display();
    //delay(1000);
}

void printSCR_yesnet(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Internet OK");
        display.print("SSID: ");
        display.println(WiFi.SSID());
        display.print("IP: ");
        display.println(WiFi.localIP());
        display.display();
}
void printSCR_nonet(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("No Internet");
        display.display();
}
void printSCR_attesaWL(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Attesa WIFI!");
        //lcd.setCursor(0, 1);
        display.print("Connessione...");
        display.display();
}
