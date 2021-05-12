const char* ntpServer;
const long  gmtOffset_sec = 3600;   // Eastern Standard Time
const int   daylightOffset_sec = 3600;
bool gotTime = false;
String time_string;
struct tm timeinfo;
time_t now;
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
  String minuti;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long updateTime = 60000; // 1 min aggiorno orologio su scr
// Recupero dell'ora
void initTime(){
if(WiFi.SSID()=="SSSR65")
    {
        ntpServer = "192.168.178.1";
    }else{
        ntpServer = "pool.ntp.org";
    }
// Init and get the time
    int nr = 0;         // numero di tentativi
    int ntMax = 5;     //numero di tentativi di connessione al server ntp
    int dt = 1000;      //tempo attesa ri-tentativo
    String ore;
    String Giorno;
    DEBUG_PRINTLN("Syncing time...");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    while(time(nullptr) <= 150000) {
        DEBUG_PRINTLN("Tentativo di recupero orario...");
        nr++;
        if (nr > ntMax) {
			DEBUG_PRINTLN("Recupero orario fallito...");
            gotTime = false;
			break;
		}
        delay(dt);
    }
    if(nr < ntMax){
            DEBUG_PRINTLN("Recupero orario eseguito...");
            gotTime = true;

    }
    !getLocalTime(&timeinfo);
    delay(10);
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

}
