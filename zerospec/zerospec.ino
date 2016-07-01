#include <SPI.h> // We'll use SPI to transfer data. Faster!

/* PCD8544-specific defines: */
#define LCD_COMMAND  0
#define LCD_DATA     1

/* 84x48 LCD Defines: */
#define LCD_WIDTH   84 // Note: x-coordinates go wide
#define LCD_HEIGHT  48 // Note: y-coordinates go high
#define WHITE       0  // For drawing pixels. A 0 draws white.
#define BLACK       1  // A 1 draws black.

/* Pin definitions:
Most of these pins can be moved to any digital or analog pin.
DN(MOSI)and SCLK should be left where they are (SPI pins). The
LED (backlight) pin should remain on a PWM-capable pin. */
const int scePin = 7;   // SCE - Chip select, pin 3 on LCD.
const int rstPin = 6;   // RST - Reset, pin 4 on LCD.
const int dcPin = 5;    // DC - Data/Command, pin 5 on LCD.
const int sdinPin = 11;  // DN(MOSI) - Serial data, pin 6 on LCD.
const int sclkPin = 13;  // SCLK - Serial clock, pin 7 on LCD.
const int blPin = 9;    // LED - Backlight LED, pin 8 on LCD.

const char font_exclaim[] PROGMEM = "1-7a";
const char font_double_quote[] PROGMEM = "1-02";
const char font_pound[] PROGMEM = "1-02";
const char font_dollar[] PROGMEM = "1-02";
const char font_percent[] PROGMEM = "1-02";
const char font_amp[] PROGMEM = "1-02";
const char font_quote[] PROGMEM = "1-02";
const char font_lparen[] PROGMEM = "1-02";
const char font_rparen[] PROGMEM = "1-02";
const char font_star[] PROGMEM = "1-02";
const char font_plus[] PROGMEM = "1-02";
const char font_comma[] PROGMEM = "1-02";
const char font_dash[] PROGMEM = "3-000e00";
const char font_period[] PROGMEM = "1-02";
const char font_fwd_slash[] PROGMEM = "1-02";
const char font_0[] PROGMEM = "4-06999960";
const char font_1[] PROGMEM = "3-079248";
const char font_2[] PROGMEM = "4-069168f0";
const char font_3[] PROGMEM = "4-06921960";
const char font_4[] PROGMEM = "4-0999f110";
const char font_5[] PROGMEM = "4-0f8e1960";
const char font_6[] PROGMEM = "4-068e9960";
const char font_7[] PROGMEM = "4-0f124440";
const char font_8[] PROGMEM = "4-06969960";
const char font_9[] PROGMEM = "4-06997160";
const char font_colon[] PROGMEM = "1-12";
const char font_semicolon[] PROGMEM = "";
const char font_lt[] PROGMEM = "";
const char font_equal[] PROGMEM = "";
const char font_gt[] PROGMEM = "";
const char font_question[] PROGMEM = "4-06912020";
const char font_at[] PROGMEM = "";
const char font_A[] PROGMEM = "5-0114afc620";
const char font_B[] PROGMEM = "5-07a3e8c7c0";
const char font_C[] PROGMEM = "5-03a30845c0";
const char font_D[] PROGMEM = "5-07a318c7c0";
const char font_E[] PROGMEM = "4-0f8e88f0";
const char font_F[] PROGMEM = "4-0f8e8880";
const char font_G[] PROGMEM = "5-03a309c5c0";
const char font_H[] PROGMEM = "5-0463f8c620";
const char font_I[] PROGMEM = "1-7e";
const char font_J[] PROGMEM = "3-049378";
const char font_K[] PROGMEM = "5-04654e4a20";
const char font_L[] PROGMEM = "4-088888f0";
const char font_M[] PROGMEM = "7-01071d5ab56480";
const char font_N[] PROGMEM = "5-047359c620";
const char font_O[] PROGMEM = "6-01e861861780";
const char font_P[] PROGMEM = "4-0f9f8880";
const char font_Q[] PROGMEM = "6-01c8a28a6781";
const char font_R[] PROGMEM = "5-07a31f4620";
const char font_S[] PROGMEM = "5-03a28345c0";
const char font_T[] PROGMEM = "5-07c8421080";
const char font_U[] PROGMEM = "5-046318c5c0";
const char font_V[] PROGMEM = "5-046318a880";
const char font_W[] PROGMEM = "7-0126ad5aa89100";
const char font_X[] PROGMEM = "5-0454422a20";
const char font_Y[] PROGMEM = "5-0463171080";
const char font_Z[] PROGMEM = "5-07c26643e0";
const char font_lbracket[] PROGMEM = "1-02";
const char font_backslash[] PROGMEM = "1-02";
const char font_rbracket[] PROGMEM = "1-02";
const char font_caret[] PROGMEM = "1-02";
const char font_underscore[] PROGMEM = "1-02";
const char font_tilde[] PROGMEM = "1-02";
const char font_a[] PROGMEM = "4-00797970";
const char font_b[] PROGMEM = "4-088e99e0";
const char font_c[] PROGMEM = "4-00698960";
const char font_d[] PROGMEM = "4-01179970";
const char font_e[] PROGMEM = "4-0069f870";
const char font_f[] PROGMEM = "3-0d7490";
const char font_g[] PROGMEM = "4-00797197";
const char font_h[] PROGMEM = "4-088e9990";
const char font_i[] PROGMEM = "1-5e";
const char font_j[] PROGMEM = "2-1156";
const char font_k[] PROGMEM = "4-089aca90";
const char font_l[] PROGMEM = "1-7e";
const char font_m[] PROGMEM = "6-00083e965940";
const char font_n[] PROGMEM = "3-000d68";
const char font_o[] PROGMEM = "4-00069960";
const char font_p[] PROGMEM = "4-00e99e88";
const char font_q[] PROGMEM = "4-00079711";
const char font_r[] PROGMEM = "3-027920";
const char font_s[] PROGMEM = "2-039c";
const char font_t[] PROGMEM = "3-017490";
const char font_u[] PROGMEM = "4-00099960";
const char font_v[] PROGMEM = "5-000118a880";
const char font_w[] PROGMEM = "6-000021b52480";
const char font_x[] PROGMEM = "4-00096690";
const char font_y[] PROGMEM = "4-00099626";
const char font_z[] PROGMEM = "4-00f248f0";

const char * const font_table[] PROGMEM = {font_exclaim, font_double_quote, font_pound, font_dollar, font_percent, font_amp, font_quote, font_lparen, font_rparen, font_star, font_plus, font_comma, font_dash, font_period, font_fwd_slash, font_0, font_1, font_2, font_3, font_4, font_5, font_6, font_7, font_8, font_9, font_colon, font_semicolon, font_lt, font_equal, font_gt, font_question, font_at, font_A, font_B, font_C, font_D, font_E, font_F, font_G, font_H, font_I, font_J, font_K, font_L, font_M, font_N, font_O, font_P, font_Q, font_R, font_S, font_T, font_U, font_V, font_W, font_X, font_Y, font_Z, font_lbracket, font_backslash, font_rbracket, font_caret, font_underscore, font_tilde, font_a, font_b, font_c, font_d, font_e, font_f, font_g, font_h, font_i, font_j, font_k, font_l, font_m, font_n, font_o, font_p, font_q, font_r, font_s, font_t, font_u, font_v, font_w, font_x, font_y, font_z};

byte displayMap[LCD_WIDTH * LCD_HEIGHT / 8];
const int MESSAGE_BUFFER_LEN = 96;
char messageBuffer[MESSAGE_BUFFER_LEN];

void setup() {
  lcdBegin(); // This will setup our pins, and initialize the LCD
  updateDisplay(); // with displayMap untouched, SFE logo
  setContrast(40); // Good values range from 40-60

  clearDisplay(WHITE);
  updateDisplay();

  strncpy(messageBuffer, "Hello World!\nThis string demonstrates word wrapping.", MESSAGE_BUFFER_LEN);
  writeMessageBuffer();
}

int gTextStartX = 0;
int gTextStartY = 0;

void writeMessageBuffer(){  
  addLineBreaksToMessageBuffer();

  clearDisplay(WHITE);
  gTextStartX = 0;
  gTextStartY = 0;

  for(int i = 0; i < MESSAGE_BUFFER_LEN; i++){
    if(gTextStartX > (LCD_WIDTH - 8)){
      gTextStartX = 0;  
      gTextStartY += 8;
    }

    if(messageBuffer[i] == 0){
      break;
    } else if(messageBuffer[i] == '\n') {
      gTextStartY += 8;
      gTextStartX = 0;
    } else if(messageBuffer[i] == ' '){
      gTextStartX += 6;
    } else {
      gTextStartX += writeCharacter(messageBuffer[i]) + 2;
    }
  }
  updateDisplay();
}

void addLineBreaksToMessageBuffer() {
  int msgX = 0;
  int lastSpaceIdx = -1;
  int lastSplitIdx = -1;
  
  for(int i = 0; i < strlen(messageBuffer); i++){
    if(messageBuffer[i] == ' '){
      lastSpaceIdx = i;
      msgX += 6;
    } else if(messageBuffer[i] == '\n'){
      msgX = 0;
      lastSpaceIdx = -1;
    } else {
      msgX += calcCharWidth(messageBuffer[i]) + 2;
      if(msgX > (LCD_WIDTH - 8)){
        if(lastSpaceIdx != -1 && lastSplitIdx != lastSpaceIdx){
          messageBuffer[lastSpaceIdx] = '\n';
          lastSplitIdx = lastSpaceIdx;
          i = lastSpaceIdx + 1;
          msgX = 0;          
        } else {
          msgX = 0;
        }
      }
    }
  }
}

int writeCharacter(char character){
  int charWidth = calcCharWidth(character);
  bool charPixels[8 * 8];
  int bitPosn = 0;

  int fontIdx = charToFontIdx(character);
  char fontBuffer[16];
  strcpy_P(fontBuffer, (char*)pgm_read_word(&(font_table[fontIdx])));   
   
  for(int charIdx = 0; charIdx < strlen(fontBuffer); charIdx++){
    char byteBuff[2];

    // Determine the width of the letter
    if(charIdx >= 2){
      byteBuff[charIdx % 2] = fontBuffer[charIdx];
      if(charIdx % 2 == 1){
        unsigned long hex = strtoul(byteBuff, NULL, 16);
        for(int bit = 0; bit < 8; bit++){
          unsigned long mask = 1UL << (7 - bit);
          unsigned long result = mask & hex;
          charPixels[bitPosn] = (result > 0);
          bitPosn++;
        }
      }
    }
  }

  for(int x = 0; x < charWidth; x++){
    for(int y = 0; y < 8; y++){
      if(charPixels[x + y * charWidth]){
        setPixel(x + gTextStartX, y + gTextStartY);  
      } else {
        clearPixel(x + gTextStartX, y + gTextStartY);
      }      
    }
  }
  return charWidth;
}

int charToFontIdx(char character) {
  return character - 0x21;
}

int calcCharWidth(char character) {
  int fontIdx = charToFontIdx(character);
  char w[1];
  strncpy_P(w, (char*)pgm_read_word(&(font_table[fontIdx])), 1);  
  return atoi(w);
}


void loop() {
  // put your main code here, to run repeatedly:

}

// Helpful function to directly command the LCD to go to a
// specific x,y coordinate.
void gotoXY(int x, int y)
{
  LCDWrite(0, 0x80 | x);  // Column.
  LCDWrite(0, 0x40 | y);  // Row.  ?
}

// This will actually draw on the display, whatever is currently
// in the displayMap array.
void updateDisplay()
{
  gotoXY(0, 0);
  for (int i=0; i < (LCD_WIDTH * LCD_HEIGHT / 8); i++)
  {
    LCDWrite(LCD_DATA, displayMap[i]);
  }
}

// This function clears the entire display either white (0) or
// black (1).
// The screen won't actually clear until you call updateDisplay()!
void clearDisplay(boolean bw)
{
  for (int i=0; i<(LCD_WIDTH * LCD_HEIGHT / 8); i++)
  {
    if (bw)
      displayMap[i] = 0xFF;
    else
      displayMap[i] = 0;
  }
}


// Because I keep forgetting to put bw variable in when setting...
void setPixel(int x, int y)
{
  setPixel(x, y, BLACK); // Call setPixel with bw set to Black
}

void clearPixel(int x, int y)
{
  setPixel(x, y, WHITE); // call setPixel with bw set to white
}

// This function sets a pixel on displayMap to your preferred
// color. 1=Black, 0= white.
void setPixel(int x, int y, boolean bw)
{
  // First, double check that the coordinate is in range.
  if ((x >= 0) && (x < LCD_WIDTH) && (y >= 0) && (y < LCD_HEIGHT))
  {
    byte shift = y % 8;

    if (bw) // If black, set the bit.
      displayMap[x + (y/8)*LCD_WIDTH] |= 1<<shift;
    else   // If white clear the bit.
      displayMap[x + (y/8)*LCD_WIDTH] &= ~(1<<shift);
  }
}

// Set contrast can set the LCD Vop to a value between 0 and 127.
// 40-60 is usually a pretty good range.
void setContrast(byte contrast)
{
  LCDWrite(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow
  LCDWrite(LCD_COMMAND, 0x80 | contrast); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
  LCDWrite(LCD_COMMAND, 0x20); //Set display mode
}

// There are two memory banks in the LCD, data/RAM and commands.
// This function sets the DC pin high or low depending, and then
// sends the data byte
void LCDWrite(byte data_or_command, byte data)
{
  //Tell the LCD that we are writing either to data or a command
  digitalWrite(dcPin, data_or_command);

  //Send the data
  digitalWrite(scePin, LOW);
  SPI.transfer(data); //shiftOut(sdinPin, sclkPin, MSBFIRST, data);
  digitalWrite(scePin, HIGH);
}
//This sends the magical commands to the PCD8544
void lcdBegin(void)
{
  //Configure control pins
  pinMode(scePin, OUTPUT);
  pinMode(rstPin, OUTPUT);
  pinMode(dcPin, OUTPUT);
  pinMode(sdinPin, OUTPUT);
  pinMode(sclkPin, OUTPUT);
  pinMode(blPin, OUTPUT);
  analogWrite(blPin, 255);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  //Reset the LCD to a known state
  digitalWrite(rstPin, LOW);
  digitalWrite(rstPin, HIGH);

  LCDWrite(LCD_COMMAND, 0x21); //Tell LCD extended commands follow
  LCDWrite(LCD_COMMAND, 0xB0); //Set LCD Vop (Contrast)
  LCDWrite(LCD_COMMAND, 0x04); //Set Temp coefficent
  LCDWrite(LCD_COMMAND, 0x14); //LCD bias mode 1:48 (try 0x13)
  //We must send 0x20 before modifying the display control mode
  LCDWrite(LCD_COMMAND, 0x20);
  LCDWrite(LCD_COMMAND, 0x0C); //Set display control, normal mode.
}
