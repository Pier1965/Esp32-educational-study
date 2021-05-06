#ifdef ARDUINO_ARCH_ESP32
  #include <WiFi.h>
  #define VS1053_CS     5
  #define VS1053_DCS    0
  #define VS1053_DREQ   4
#endif
const int previousButton = 12;
const int nextButton = 13;
const int volumeUp = 32;
const int volumeDown = 33;
const int RCSelector = 36;
