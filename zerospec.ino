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

const char font[][18] PROGMEM = {
  "5-0114afc620", // A
  "5-07a3e8c7c0", // B
  "5-03a30845c0", // C
  "5-07a318c7c0", // D
  "4-0f8e88f0", // E
  "4-0f8e8880", //  F
  "5-03a309c5c0", // G 
  "5-0463f8c620", //  H
  "1-7e", //  I
  "3-049378", //  J
  "5-04654e4a20", //  K
  "4-088888f0", //  L
  "7-01071d5ab56480", //  M
  "5-047359c620", //  N
  "6-01e861861780", // O 
  "4-0f9f8880", //  P
  "6-01c8a28a6781", //  Q
  "5-07a31f4620", //  R
  "5-03a28345c0", //  S
  "5-07c8421080", //  T
  "5-046318c5c0", //  U
  "5-046318a880", //  V
  "7-0126ad5aa89100", //  W
  "5-0454422a20", //  X
  "5-0463171080", //  Y
  "5-07c26643e0", //  Z
  "1-02", //
  "1-02", //
  "1-02", //
  "1-02", //
  "1-02", //
  "1-02", //
  "4-00797970", //  a
  "4-088e99e0", //  b
  "4-00698960", //  c
  "4-01179970", //  d
  "4-0069f870", //  e
  "3-0d7490", //  f
  "4-00797197", // g 
  "4-088e9990", //  h
  "1-5e", //  i
  "2-1156", // j 
  "4-089aca90", //  k
  "1-7e", //  
  "6-00083e965940", //  
  "4-008f9990", //  
  "4-00069960", //  
  "4-00e99e88", //  
  "4-00079711", //  
  "3-027920", //  
  "4-069c2970", //  
  "3-017490", //  
  "4-00099960", //  
  "5-000118a880", //  
  "6-000021b52480", //  
  "4-00096690", //  
  "4-00099626", //  
  "4-00f248f0", //  
  "4-06999960", //  
  "3-079248", //  
  "4-069168f0", //  
  "4-06921960", //  
  "4-0999f110", //  
  "4-0f8e1960", //  
  "4-068e9960", //  
  "4-0f124440", //  
  "4-06969960", //  
  "4-06997160", //  
  "1-02", //  
  "4-06912020", //  
  "1-7a", //  
  "1-12", //  
  "3-000e00", //  
 };

byte displayMap[LCD_WIDTH * LCD_HEIGHT / 8];
const int MESSAGE_BUFFER_LEN = 64;
char messageBuffer[MESSAGE_BUFFER_LEN];

void setup() {
  lcdBegin(); // This will setup our pins, and initialize the LCD
  updateDisplay(); // with displayMap untouched, SFE logo
  setContrast(40); // Good values range from 40-60

  clearDisplay(WHITE);
  updateDisplay();

  strncpy(messageBuffer, "Hello World", MESSAGE_BUFFER_LEN);
  writeMessageBuffer();
}

int startX = 0;
int startY = 0;

void writeMessageBuffer(){  
  clearDisplay(WHITE);
  int x = 0;
  int y = 0;

  for(int i = 0; i < MESSAGE_BUFFER_LEN; i++){
    if(messageBuffer[i] == 0){
      break;
    } else if(messageBuffer[i] == ' '){
      x += 6;
    } else {
      startX = x;
      startY = 20;
      x += writeCharacter(messageBuffer[i]) + 2;
    }
    updateDisplay();
  }
  updateDisplay();
}

int writeCharacter(char character){
  int charWidth = 0;
  bool charPixels[8 * 8];
  int bitPosn = 0;

//  for(int i = 0; i < 8 * 8; i++){
//    charPixels[i] = false;
//  }

  int fontIdx = character - 0x41;
  for(int charIdx = 0; charIdx < strlen(font[fontIdx]); charIdx++){
    char byteBuff[2];

    // Determine the width of the letter
    if(charIdx == 0){
    
      char w[1];
      w[0] = font[fontIdx][charIdx];
      charWidth = atoi(w); 
    } else if(charIdx >= 2){
      byteBuff[charIdx % 2] = font[fontIdx][charIdx];
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
        setPixel(x + startX, y + startY);  
      } else {
        clearPixel(x + startX, y + startY);
      }      
    }
  }
  return charWidth;
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
