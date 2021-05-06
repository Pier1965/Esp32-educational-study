//IR codifica tasti
#define APPLE_IR 1
//#define ELEGO_IR 1
//#define SAMS_IR 1

#ifdef APPLE_IR
  #define IR_UP 0x77E1D009
  #define IR_DN 0x77E1B009
  #define IR_NX 0x77E1E009
  #define IR_PV 0x77E11009
  #define IR_RS 0x77E14009
#endif
#ifdef ELEGO_IR
  #define IR_UP 0xFF629D
  #define IR_DN 0xFFA857
  #define IR_NX 0xFFC23D
  #define IR_PV 0xFF22DD
  #define IR_RS 0xFFA25D
#endif
#ifdef SAMS_IR
  #define IR_UP 0xE0E0E01F
  #define IR_DN 0xE0E0D02F
  #define IR_NX 0xE0E048B7
  #define IR_PV 0xE0E008F7
  #define IR_RS 0xE0E040BF
#endif