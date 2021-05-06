//Radio memorizzate

char *desc[] =  {"Radio Kosmos Gr",
                   "Rai Radio 1", "Rai Radio 2", "Rai Radio 3", "Rai Radio 3 Classica",
                   "BBC 1", "BBC 1X", "BBC 2", "BBC 3", "BBC 4", "BBC 4X", "BBC 6",
                    "Soma FM 80s", "Otto Baroque", "Jazz ru"};
char *host[] = {"radiostreaming.ert.gr",
                  "icestreaming.rai.it","icestreaming.rai.it", "icestreaming.rai.it", "icestreaming.rai.it",
                  "stream.live.vc.bbcmedia.co.uk", "stream.live.vc.bbcmedia.co.uk", "stream.live.vc.bbcmedia.co.uk", "stream.live.vc.bbcmedia.co.uk", "stream.live.vc.bbcmedia.co.uk", "stream.live.vc.bbcmedia.co.uk", "stream.live.vc.bbcmedia.co.uk",
"ice6.somafm.com", "strm112.1.fm", "jazz.streamr.ru"};
char *path[] = {"/ert-kosmos",
                  "/1.mp3","/2.mp3","/3.mp3", "/5.mp3",
                  "/bbc_radio_one","/bbc_1xtra", "/bbc_radio_two", "/bbc_radio_three", "/bbc_radio_fourfm", "/bbc_radio_four_extra", "/bbc_6music",
"/u80s-128-mp3", "/baroque_mobile_mp3", "/jazz-64.mp3"};
int   port[] = {80,80,80,80,80,80,80,80,80,80,80,80,80,80,80};
const int NR = (sizeof(port) / sizeof(port[0]));
