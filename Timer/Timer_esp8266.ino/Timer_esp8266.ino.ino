/// @file    ColorPalette.ino
/// @brief   Demonstrates how to use @ref ColorPalettes
/// @example ColorPalette.ino

#include <FastLED.h>
#include <RoxMux.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "TIM"
#define APPSK "hopemedia12345"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer webp(80);
ESP8266WebServer clocks(8080);



#define LED_PIN     1
#define NUM_LEDS    86
#define BRIGHTNESS  128
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define RedCl 0
#define GreenCl 1
#define WhiteCl 2
#define YellowCl 3
char Min = 0, Sec = 0;
char SelectedColor = WhiteCl;
char StartPausa = 4, Stop = 5, Up = 6, Down = 7;
char IsStarted = 0, Dir = 0, IsPause = 0, IsDemo = 1, IsWhiteMode = 0, Britn = 100;

long StartTime = 0, StopTime = 0, CurrentTime = 0, ScreenTimeout = 0;

#define UPDATES_PER_SECOND 100
#define MUX_TOTAL 1
Rox74HC165 <MUX_TOTAL> mux;

#define PIN_DATA  2 // pin 9 on 74HC165 (DATA)
#define PIN_LOAD  3 // pin 1 on 74HC165 (LOAD)
#define PIN_CLK   0 // pin 2 on 74HC165 (CLK))

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p FL_PROGMEM;


bool gReverseDirection = false;
uint8_t hue = 0;


void handleRootP() {
  
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", Min, Sec);

  String color = (Dir == 0) ? "green" : "red";

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='1'>";  // Автообновление
  html += "<title>ESP8266 Timer</title>";
  html += "<style>";
  html += "html, body { height: 100%; margin: 0; padding: 0; background-color: black; }";
  html += "body { display: flex; justify-content: center; align-items: center; }";
  html += ".timer {";
  html += "  font-size: 20vw;";
  html += "  color: " + color + ";";
  html += "  font-family: monospace;";
  html += "  border: 10px solid white;";
  html += "  padding: 20px 40px;";
  html += "  border-radius: 20px;";
  html += "  background-color: #222222;";  // Тёмно-серый внутри рамки
  html += "}";
  html += "</style>";
  html += "</head><body>";
  html += "<div class='timer'>" + String(timeStr) + "</div>";
  html += "</body></html>";
  
  webp.send(200, "text/html", html);
}

void handleRootC() {
  clocks.send(200, "text/html", "<h1>Protocol</h1>");
}


void setup() {
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  Britn );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    mux.begin(PIN_DATA, PIN_LOAD, PIN_CLK);

    WiFi.softAP(ssid, password);
    
    webp.on("/", handleRootP);
    webp.begin();

    clocks.on("/", handleRootC);
    clocks.begin();
}

void SetSegment(char Seg, char Color_)
{
  if (Color_ == RedCl)
  {
    if (Seg < 14)
    {
      leds[Seg * 3] = CRGB::Red;
      leds[Seg * 3 + 1] = CRGB::Red;
      leds[Seg * 3 + 2] = CRGB::Red;
    }
    else
    {
      leds[Seg * 3 + 2] = CRGB::Red;
      leds[Seg * 3 + 3] = CRGB::Red;
      leds[Seg * 3 + 4] = CRGB::Red;
    }

    leds[43] = CRGB::Red;
    leds[42] = CRGB::Red;
  }

  if (Color_ == GreenCl)
  {
    if (Seg < 14)
    {
      leds[Seg * 3] = CRGB::Green;
      leds[Seg * 3 + 1] = CRGB::Green;
      leds[Seg * 3 + 2] = CRGB::Green;
    }
    else
    {
      leds[Seg * 3 + 2] = CRGB::Green;
      leds[Seg * 3 + 3] = CRGB::Green;
      leds[Seg * 3 + 4] = CRGB::Green;
    }

    leds[43] = CRGB::Green;
    leds[42] = CRGB::Green;
  }

  if (Color_ == YellowCl)
  {
    if (Seg < 14)
    {
      leds[Seg * 3] = CRGB::Yellow;
      leds[Seg * 3 + 1] = CRGB::Yellow;
      leds[Seg * 3 + 2] = CRGB::Yellow;
    }
    else
    {
      leds[Seg * 3 + 2] = CRGB::Yellow;
      leds[Seg * 3 + 3] = CRGB::Yellow;
      leds[Seg * 3 + 4] = CRGB::Yellow;
    }

    leds[43] = CRGB::Yellow;
    leds[42] = CRGB::Yellow;
  }

  if (Color_ == WhiteCl)
  {
    if (Seg < 14)
    {
      leds[Seg * 3] = CRGB::White;
      leds[Seg * 3 + 1] = CRGB::White;
      leds[Seg * 3 + 2] = CRGB::White;
    }
    else
    {
      leds[Seg * 3 + 2] = CRGB::White;
      leds[Seg * 3 + 3] = CRGB::White;
      leds[Seg * 3 + 4] = CRGB::White;
    }

    leds[42] = CRGB::White;
    leds[43] = CRGB::White;
  }
}

void SetNum(char Num, char Value, char Color__)
{
  char Seg_Offset = 0;
  Seg_Offset = Num * 7;

  if (Value == 0)
  {
    SetSegment(Seg_Offset,     Color__);
    SetSegment(Seg_Offset + 1, Color__);
    SetSegment(Seg_Offset + 2, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 4, Color__);
    SetSegment(Seg_Offset + 5, Color__);
  }

  if (Value == 1)
  {
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 2, Color__);
  }

  if (Value == 2)
  {
    SetSegment(Seg_Offset + 1,     Color__);
    SetSegment(Seg_Offset + 2,     Color__);
    SetSegment(Seg_Offset + 4,     Color__);
    SetSegment(Seg_Offset + 5,     Color__);
    SetSegment(Seg_Offset + 6,     Color__);
  }

  if (Value == 3)
  {
    SetSegment(Seg_Offset + 1, Color__);
    SetSegment(Seg_Offset + 2, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 4, Color__);
    SetSegment(Seg_Offset + 6, Color__);
  }

  if (Value == 4)
  {
    SetSegment(Seg_Offset,     Color__);
    SetSegment(Seg_Offset + 2, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 6, Color__);
  }

  if (Value == 5)
  {
    SetSegment(Seg_Offset,     Color__);
    SetSegment(Seg_Offset + 1, Color__);
    SetSegment(Seg_Offset + 6, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 4, Color__);
  }

  if (Value == 6)
  {
    SetSegment(Seg_Offset,     Color__);
    SetSegment(Seg_Offset + 1, Color__);
    SetSegment(Seg_Offset + 6, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 4, Color__);
    SetSegment(Seg_Offset + 5, Color__);
  }

  if (Value == 7)
  {
    SetSegment(Seg_Offset + 1, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 2, Color__);
  }

  if (Value == 8)
  {
    SetSegment(Seg_Offset,     Color__);
    SetSegment(Seg_Offset + 1, Color__);
    SetSegment(Seg_Offset + 2, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 4, Color__);
    SetSegment(Seg_Offset + 5, Color__);
    SetSegment(Seg_Offset + 6, Color__);
  }

  if (Value == 9)
  {
    SetSegment(Seg_Offset,     Color__);
    SetSegment(Seg_Offset + 1, Color__);
    SetSegment(Seg_Offset + 2, Color__);
    SetSegment(Seg_Offset + 3, Color__);
    SetSegment(Seg_Offset + 4, Color__);
    SetSegment(Seg_Offset + 6, Color__);
  }
}

void ShowNums(char Color)
{
  char Num1, Num2, Num3, Num4;

  Num1 = Min / 10;
  Num2 = Min % 10;

  Num3 = Sec / 10;
  Num4 = Sec % 10;

  FastLED.clear(); 
  SetNum(0, Num1, Color);
  SetNum(1, Num2, Color);

  SetNum(2, Num3, Color);
  SetNum(3, Num4, Color);
  FastLED.show();
}

char GetButton(char Bt)
{
  mux.update();
  if(Bt == StartPausa)
  {
    bool But_st = mux.read(4);
    if(But_st == true)
    {return 1;}
    else
    {return 0;}
  }

  if(Bt == Stop)
  {
    bool But_st = mux.read(5);
    if(But_st == true)
    {return 1;}
    else
    {return 0;}
  }

  if(Bt == Up)
  {
    bool But_st = mux.read(6);
    if(But_st == true)
    {return 1;}
    else
    {return 0;}
  }

  if(Bt == Down)
  {
    bool But_st = mux.read(7);
    if(But_st == true)
    {return 1;}
    else
    {return 0;}
  }
  return 1;
}

void loop()
{
  long Time_ = 0, Diff_time;
  float Rest, Tim, Currnt;
  unsigned int Cnt = 0;

  while (1)
  {
    webp.handleClient();
    clocks.handleClient();
    
    if (IsDemo == 0)
    {
      if (IsStarted == 0)
      {
        SelectedColor = WhiteCl;
        if (GetButton(Up) == 0)
        {
          if (Min < 99)
          {
            Min++;
          }
          ScreenTimeout = millis() + 60000;
          delay(150);
        }

        if (GetButton(Down) == 0)
        {
          if (Min != 0)
          {
            Min--;
          }
          ScreenTimeout = millis() + 60000;
          delay(150);
        }

        if (GetButton(Stop) == 0)
        {
          Min = 0;
          Sec = 0;
          IsWhiteMode = 0;
          ScreenTimeout = millis() + 60000;
        }

        if (GetButton(StartPausa) == 0)
        {
          StartTime = millis();
          StopTime = millis() + (long)Min * 60 * 1000;
          ScreenTimeout = millis() + 60000;
          IsStarted = 1;

          if(Min == 0)
          { IsWhiteMode = 1;}
          else
          { SelectedColor = GreenCl;}
          
          while (GetButton(StartPausa) == 0)
          { }
          delay(200);
        }
      }
      else
      {
        if (IsPause == 0)
        {
          if (Dir == 0)
          {
            Min = CurrentTime / 1000 / 60;
            Sec = (CurrentTime / 1000) - ((long)Min * 60);
            CurrentTime = StopTime - millis();

            Time_ = StopTime - StartTime;

            Tim = Time_ / 1000;
            Currnt = CurrentTime / 1000;
            Rest = Currnt / Tim * 100;

            if (Rest < 15)
            {
              SelectedColor = YellowCl;
            }


            if (CurrentTime < 0)
            {
              Dir = 1;
            }
          }
          else
          {
            Min = CurrentTime / 1000 / 60;
            Sec = (CurrentTime / 1000) - ((long)Min * 60);
            CurrentTime = millis() - StopTime;

            if(IsWhiteMode == 0)
            SelectedColor = RedCl;
            else
            SelectedColor = WhiteCl;
          }

          if (GetButton(Stop) == 0)
          {
            Min = 0;
            Sec = 0;
            SelectedColor = WhiteCl;
            IsStarted = 0;
            StartTime = 0;
            StopTime = 0;
            CurrentTime = 0;
            Dir = 0;
            ScreenTimeout = millis() + 60000;
          }

          if (GetButton(StartPausa) == 0)
          {
            Diff_time = millis();
            IsPause = 1;
            ScreenTimeout = millis() + 60000;
            while (GetButton(StartPausa) == 0)
            {

            }
            delay(300);
          }

        }
        else
        {
          if (GetButton(StartPausa) == 0)
          {
            StartTime += millis() - Diff_time;
            StopTime += millis() - Diff_time;
            IsPause = 0;
            ScreenTimeout = millis() + 60000;
            while (GetButton(StartPausa) == 0)
            {

            }
            delay(300);
          }

          if (GetButton(Stop) == 0)
          {
            Min = 0;
            Sec = 0;
            SelectedColor = WhiteCl;
            IsStarted = 0;
            StartTime = 0;
            StopTime = 0;
            CurrentTime = 0;
            Dir = 0;
            IsPause = 0;
            ScreenTimeout = millis() + 60000;
          }
        }

      }

      ShowNums(SelectedColor);
      delay(30);

      if(ScreenTimeout < millis() && IsStarted == 0)
      { IsDemo = 1;}
    }
    else
    {
      if(Cnt < 1000)
      { FastLED.setBrightness(70); rainbow(); }

      if(Cnt > 1000 && Cnt < 2000)
      { FastLED.setBrightness(70); filler(); }

      if(Cnt > 2000 && Cnt < 3000)
      { FastLED.setBrightness(50); colorCycle(); }

      if(Cnt > 3000 && Cnt < 3200)
      { FastLED.setBrightness(70); runningDots(); }

      if(Cnt > 3200)
      { breathing();}

      Cnt++;
      if(Cnt > 4400)
      { Cnt = 0;}
      
      FastLED.show();
      delay(30);

      if (GetButton(Up) == 0)
      {
        ScreenTimeout = millis() + 60000;
        FastLED.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }

      if (GetButton(Down) == 0)
      {
        ScreenTimeout = millis() + 60000;
        FastLED.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }

      if (GetButton(StartPausa) == 0)
      {
        ScreenTimeout = millis() + 60000;
        FastLED.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }

      if (GetButton(Stop) == 0)
      {
        ScreenTimeout = millis() + 60000;
        FastLED.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }
    }
  }



  
    //ChangePalettePeriodically();
    
    //static uint8_t startIndex = 0;
    //startIndex = startIndex + 1; /* motion speed */
    
    //FillLEDsFromPaletteColors( startIndex);
    
    //FastLED.show();
    //FastLED.delay(1000 / UPDATES_PER_SECOND);
}



void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; ++i) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

const TProgmemPalette16 myRedWhiteBluePalette_p FL_PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

void fill(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}



void rainbow() {
  fill_rainbow(leds, NUM_LEDS, hue, 255/NUM_LEDS);
  FastLED.show();
  
  hue++;
}

void filler() {
  // Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((55 * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < 120 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

void colorCycle() 
{
  static int counter = 0, clrCount = 0;

  if(clrCount == 0)
  fill(CRGB::Red);

  if(clrCount == 1)
  fill(CRGB::Green);

  if(clrCount == 2)
  fill(CRGB::Blue);

  
  counter++;
  if (counter >= NUM_LEDS) 
  {
    counter = 0;
    clrCount++;
    if(clrCount == 3)
    {clrCount = 0;}
  }
}

void runningDots() {
  static byte counter = 0;
  // перемотка буфера со сдвигом (иллюзия движения пикселей)
  for (int i = 0; i < NUM_LEDS - 1; i++) leds[i] = leds[i + 1];

  // каждый третий вызов - последний пиксель красным, иначе чёрным
  if (counter % 3 == 0) leds[NUM_LEDS - 1] = CRGB::White;
  else leds[NUM_LEDS - 1] = CRGB::Black;
  counter++;
  delay(100);   // дополнительная задержка
}

void breathing() {
  static int dir = 1;
  static int bright = 0;
  bright += dir * 5;    // 5 - множитель скорости изменения

  if (bright > 255) {
    bright = 255;
    dir = -1;
  }
  if (bright < 0) {
    bright = 0;
    dir = 1;
  }
  FastLED.setBrightness(bright);
}
