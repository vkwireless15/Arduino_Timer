#include <FastLED.h>
//#include <WiFi.h>
#include <ESP8266WiFi.h>


const char* ssid = "TIM";
const char* password = "hopemedia12345";

const char* server_ip = "192.168.4.1";
const uint16_t server_port = 8080;



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

char Britn = 100, IsStarted = 0;
char M = 0, S = 0, Clr = 0, TimState = 0, IsDemo = 0;
unsigned int Cnt = 0;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p FL_PROGMEM;
bool gReverseDirection = false;
uint8_t hue = 0;

const unsigned long checkInterval = 500;
unsigned long previousMillis = 0;


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

void ShowNums(char Color, char Min, char Sec)
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
  for ( int i = 0; i < 16; ++i) {
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
  fill_rainbow(leds, NUM_LEDS, hue, 255 / NUM_LEDS);
  FastLED.show();

  hue++;
}

void filler() {
  // Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((55 * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < 120 ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    CRGB color = HeatColor( heat[j]);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }
}

void colorCycle()
{
  static int counter = 0, clrCount = 0;

  if (clrCount == 0)
    fill(CRGB::Red);

  if (clrCount == 1)
    fill(CRGB::Green);

  if (clrCount == 2)
    fill(CRGB::Blue);


  counter++;
  if (counter >= NUM_LEDS)
  {
    counter = 0;
    clrCount++;
    if (clrCount == 3)
    {
      clrCount = 0;
    }
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


char Sw (char Dig)
{
  char number;
  switch (Dig) 
  {
    case '0': number = 0; break;
    case '1': number = 1; break;
    case '2': number = 2; break;
    case '3': number = 3; break;
    case '4': number = 4; break;
    case '5': number = 5; break;
    case '6': number = 6; break;
    case '7': number = 7; break;
    case '8': number = 8; break;
    case '9': number = 9; break;
    default:
    number = 10;  // Ошибка: не цифра
    break;
  }
  return number;
}

char GetNum(char Dig1, char Dig2)
{
  char Nums;
  if(Sw(Dig1) != 10)
  {
    Nums = Sw(Dig1) * 10;
  }
  else
  {
    return 0;
  }

  if(Sw(Dig2) != 10)
  {
    Nums += Sw(Dig2);
  }
  else
  {
    return 0;
  }
  return Nums;
}

void Show_data(char data_[])
{
  M = GetNum(data_[0], data_[1]);
  S = GetNum(data_[3], data_[4]);
  Clr = GetNum(data_[6], data_[7]);
  TimState = GetNum(data_[9], data_[10]);
  IsDemo = GetNum(data_[12], data_[13]);
}

char Get_Data()
{
  char tim_data[255];
  char i = 0;
  
  WiFiClient client;
  
  if (!client.connect(server_ip, server_port)) 
  { return 0; }
  else
  { 
    client.print("TIM"); 
  }

  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      client.stop();
      return 0;
    }
  }

  while (client.available()) 
  {
    tim_data[i] = static_cast<char>(client.read());
    //Serial.print(tim_data[i]);
    i++;
  }
  client.stop();
  
  Show_data(tim_data);

  //Serial.println();
  //Serial.print((int) M);
  //Serial.print((int) S);
  //Serial.print((int)Clr);
  //Serial.print((int)TimState);
  //Serial.println("--");
  
  
  return 1;
}


void setup()
{
  //Serial.begin(115200);
  
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  Britn );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    leds[18] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    FastLED.show();
    delay(300);
    leds[18] = CRGB::Black;
    leds[19] = CRGB::Black;
    leds[20] = CRGB::Black;
    FastLED.show();
    delay(300);
  }
  //Serial.println("Connected");
}

void loop()
{
  unsigned long currentMillis = millis();

  // Проверка подключения каждые checkInterval миллисекунд
  if (currentMillis - previousMillis >= checkInterval) 
  {
    previousMillis = currentMillis;
    if (WiFi.status() != WL_CONNECTED) 
    {
      WiFi.disconnect();
      WiFi.begin(ssid, password);
      FastLED.clear();
      while (WiFi.status() != WL_CONNECTED) 
      {
        leds[18] = CRGB::White;
        leds[19] = CRGB::White;
        leds[20] = CRGB::White;
        FastLED.show();
        delay(300);
        leds[18] = CRGB::Black;
        leds[19] = CRGB::Black;
        leds[20] = CRGB::Black;
        FastLED.show();
        delay(300);
      }
    } 
    else
    {
      Serial.println("Get data");
      if(Get_Data() == 0)
      {
        FastLED.clear();
        leds[18] = CRGB::Red;
        leds[19] = CRGB::Red;
        leds[20] = CRGB::Red;
        FastLED.show();
      }
    }
  }

  if(IsDemo == 0)
  {
    ShowNums(Clr, M, S);
  }
  else
  {
    if (Cnt < 1000)
    {
      FastLED.setBrightness(70);
      rainbow();
    }

    if (Cnt > 1000 && Cnt < 2000)
    {
      FastLED.setBrightness(70);
      filler();
    }

    if (Cnt > 2000 && Cnt < 3000)
    {
      FastLED.setBrightness(50);
      colorCycle();
    }

    if (Cnt > 3000 && Cnt < 3200)
    {
      FastLED.setBrightness(70);
      runningDots();
    }

    if (Cnt > 3200)
    {
      breathing();
    }

    Cnt++;
    if (Cnt > 4400)
    {
      Cnt = 0;
    }

    delay(30);
    FastLED.show();
  }

}
