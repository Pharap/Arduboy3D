#include <Arduboy2.h>
#include "Game.h"

Arduboy2Base arduboy;
Sprites sprites;

uint8_t GetInput()
{
  uint8_t result = 0;
  
  if(arduboy.pressed(A_BUTTON))
  {
    result |= INPUT_A;  
  }
  if(arduboy.pressed(B_BUTTON))
  {
    result |= INPUT_B;  
  }
  if(arduboy.pressed(UP_BUTTON))
  {
    result |= INPUT_UP;  
  }
  if(arduboy.pressed(DOWN_BUTTON))
  {
    result |= INPUT_DOWN;  
  }
  if(arduboy.pressed(LEFT_BUTTON))
  {
    result |= INPUT_LEFT;  
  }
  if(arduboy.pressed(RIGHT_BUTTON))
  {
    result |= INPUT_RIGHT;  
  }

  return result;
}

void SetLED(uint8_t r, uint8_t g, uint8_t b)
{
  arduboy.digitalWriteRGB(r ? RGB_ON : RGB_OFF, g ? RGB_ON : RGB_OFF, b ? RGB_ON : RGB_OFF);
}

void PutPixel(uint8_t x, uint8_t y, uint8_t colour)
{
  arduboy.drawPixel(x, y, colour);
}

// Adpated from https://github.com/a1k0n/arduboy3d/blob/master/draw.cpp
// since the AVR has no barrel shifter, we'll do a progmem lookup
const uint8_t topmask_[] PROGMEM = {
  0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80 };
const uint8_t bottommask_[] PROGMEM = {
  0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };

void DrawVLine(uint8_t x, int8_t y0_, int8_t y1_, uint8_t pattern) 
{
  uint8_t *screenptr = arduboy.getBuffer() + x;

  if (y1_ < y0_ || y1_ < 0 || y0_ > 63) return;

  // clip (FIXME; clipping should be handled elsewhere)
  // cast to unsigned after clipping to simplify generated code below
  uint8_t y0 = y0_, y1 = y1_;
  if (y0_ < 0) y0 = 0;
  if (y1_ > 63) y1 = 63;

  uint8_t *page0 = screenptr + ((y0 & 0x38) << 4);
  uint8_t *page1 = screenptr + ((y1 & 0x38) << 4);
  if (page0 == page1) 
  {
    uint8_t mask = pgm_read_byte(topmask_ + (y0 & 7))
      & pgm_read_byte(bottommask_ + (y1 & 7));
    *page0 &= ~mask;
    *page0 |= pattern & mask;  // fill y0..y1 in same page in one shot
  }
  else
  {
    uint8_t mask = pgm_read_byte(topmask_ + (y0 & 7));
    *page0 &= ~mask;
    *page0 |= pattern & mask;  // write top 1..8 pixels
    page0 += 128;
    while (page0 != page1) 
    {
      *page0 = pattern;  // fill middle 8 pixels at a time
      page0 += 128;
    }
    mask = pgm_read_byte(bottommask_ + (y1 & 7));  // and bottom 1..8 pixels
    *page0 &= ~mask;
    *page0 |= pattern & mask;
  }
}


void DrawBackground()
{
  uint8_t* ptr = arduboy.getBuffer();
  uint8_t counter = 64;
  
  while(counter--)
  {
    *ptr++ = 0x55;  *ptr++ = 0; 
    *ptr++ = 0x55;  *ptr++ = 0; 
    *ptr++ = 0x55;  *ptr++ = 0; 
    *ptr++ = 0x55;  *ptr++ = 0; 
  }

  counter = 64;
  while(counter--)
  {
    *ptr++ = 0x55;  *ptr++ = 0xAA;  
    *ptr++ = 0x55;  *ptr++ = 0xAA;  
    *ptr++ = 0x55;  *ptr++ = 0xAA;  
    *ptr++ = 0x55;  *ptr++ = 0xAA;
  }
}

void DrawSprite(int16_t x, int16_t y, const uint8_t *bitmap,
  const uint8_t *mask, uint8_t frame, uint8_t mask_frame)
{
  sprites.drawExternalMask(x, y, bitmap, mask, frame, mask_frame);
}

void DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap)
{
  uint8_t w = pgm_read_byte(&bitmap[0]);
  uint8_t h = pgm_read_byte(&bitmap[1]);
  arduboy.drawBitmap(x, y, bitmap + 2, w, h);
}

void DrawSolidBitmap(int16_t x, int16_t y, const uint8_t *bitmap)
{
  uint8_t w = pgm_read_byte(&bitmap[0]);
  uint8_t h = pgm_read_byte(&bitmap[1]);
  arduboy.fillRect(x, y, w, h, BLACK);
  arduboy.drawBitmap(x, y, bitmap + 2, w, h);
}

void FillScreen(uint8_t colour)
{
  arduboy.fillScreen(colour);
}

/*
void DrawFilledRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t colour)
{
  arduboy.fillRect(x, y, w, h, colour);
}

void DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t colour)
{
  arduboy.drawRect(x, y, w, h, colour);
}
*/
/*
void DrawBitmap(const uint8_t* bmp, uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
  arduboy.drawBitmap(x, y, bmp, w, h, WHITE);
}*/

void setup()
{
  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.bootLogo();
  arduboy.setFrameRate(30);

  //Serial.begin(9600);

  InitGame();
}

void loop()
{
  if(arduboy.nextFrameDEV())
  {
    TickGame();
    
    //Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
    arduboy.display(false);
  }
}
