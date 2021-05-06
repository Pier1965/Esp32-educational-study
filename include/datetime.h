const char* ntpServer = "1.it.pool.ntp.org";
const long  gmtOffset_sec = 3600;   // Eastern Standard Time
const int   daylightOffset_sec = 3600;
String time_string;
struct tm timeinfo;
  // int tm_sec;
  // int tm_min;
  // int tm_hour;
  // int tm_mday;
  // int tm_mon;
  // int tm_year;
  // int tm_wday;
  // int tm_yday;
  // int tm_isdst;
  String dow[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  String months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
  String Data;
  String Ora;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long updateTime = 60000; // 1 min aggiorno orologio su scr

void initTime(){
// Init and get the time
    int nr = 0;         // numero di tentativi
    int ntMax = 5;     //numero di tentativi di connessione al server ntp
    int dt = 1000;      //tempo attesa ri-tentativo
    DEBUG_PRINTLN("Syncing time...");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    while(time(nullptr) <= 150000) {
        DEBUG_PRINTLN("..........");
        nr++;
        if (nr > ntMax) {
			DEBUG_PRINTLN("Gave up waiting for network time(nullptr) to have a valid value.");
			break;
		}
        delay(dt);
    }
    getLocalTime(&timeinfo);
    delay(10);
    Data = dow[timeinfo.tm_wday] + " " + String(timeinfo.tm_mday) + " " +  months[timeinfo.tm_mon];
    Ora = String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min);

    DEBUG_PRINTLN("Time from Internet  ");
    DEBUG_PRINT(Data);
    DEBUG_PRINT(" - ");
    DEBUG_PRINTLN(Ora);

}
