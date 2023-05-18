// простейшие динамические эффекты
// сначала ознакомься с примером microLED_guide !!!

#define STRIP_PIN 3     // пин ленты
#define NUMLEDS 86      // кол-во светодиодов

#define COLOR_DEBTH 3
#include <microLED.h>   // подключаем библу
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

#define RedCl 0
#define GreenCl 1
#define WhiteCl 2
#define YellowCl 3
char Min = 0, Sec = 0;
char SelectedColor = WhiteCl;
char StartPausa = 4, Stop = 5, Up = 6, Down = 7;
char IsStarted = 0, Dir = 0, IsPause = 0, IsDemo = 1, Britn = 180;

long StartTime = 0, StopTime = 0, CurrentTime = 0, ScreenTimeout = 0;



void setup() {
  strip.setBrightness(Britn);
  pinMode(StartPausa, INPUT);
  pinMode(Stop, INPUT);
  pinMode(Up, INPUT);
  pinMode(Down, INPUT);

  digitalWrite(StartPausa, HIGH);
  digitalWrite(Stop, HIGH);
  digitalWrite(Up, HIGH);
  digitalWrite(Down, HIGH);
}


void SetSegment(char Seg, char Color_)
{
  if (Color_ == RedCl)
  {
    if (Seg < 14)
    {
      strip.leds[Seg * 3] = mRed;
      strip.leds[Seg * 3 + 1] = mRed;
      strip.leds[Seg * 3 + 2] = mRed;
    }
    else
    {
      strip.leds[Seg * 3 + 2] = mRed;
      strip.leds[Seg * 3 + 3] = mRed;
      strip.leds[Seg * 3 + 4] = mRed;
    }

    strip.leds[43] = mRed;
    strip.leds[42] = mRed;
  }

  if (Color_ == GreenCl)
  {
    if (Seg < 14)
    {
      strip.leds[Seg * 3] = mGreen;
      strip.leds[Seg * 3 + 1] = mGreen;
      strip.leds[Seg * 3 + 2] = mGreen;
    }
    else
    {
      strip.leds[Seg * 3 + 2] = mGreen;
      strip.leds[Seg * 3 + 3] = mGreen;
      strip.leds[Seg * 3 + 4] = mGreen;
    }

    strip.leds[43] = mGreen;
    strip.leds[42] = mGreen;
  }

  if (Color_ == YellowCl)
  {
    if (Seg < 14)
    {
      strip.leds[Seg * 3] = mYellow;
      strip.leds[Seg * 3 + 1] = mYellow;
      strip.leds[Seg * 3 + 2] = mYellow;
    }
    else
    {
      strip.leds[Seg * 3 + 2] = mYellow;
      strip.leds[Seg * 3 + 3] = mYellow;
      strip.leds[Seg * 3 + 4] = mYellow;
    }

    strip.leds[43] = mYellow;
    strip.leds[42] = mYellow;
  }

  if (Color_ == WhiteCl)
  {
    if (Seg < 14)
    {
      strip.leds[Seg * 3] = mWhite;
      strip.leds[Seg * 3 + 1] = mWhite;
      strip.leds[Seg * 3 + 2] = mWhite;
    }
    else
    {
      strip.leds[Seg * 3 + 2] = mWhite;
      strip.leds[Seg * 3 + 3] = mWhite;
      strip.leds[Seg * 3 + 4] = mWhite;
    }

    strip.leds[42] = mWhite;
    strip.leds[43] = mWhite;
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

  strip.clear();
  SetNum(0, Num1, Color);
  SetNum(1, Num2, Color);

  SetNum(2, Num3, Color);
  SetNum(3, Num4, Color);
  strip.show();
}


void loop() {

  long Time_ = 0, Diff_time;
  float Rest, Tim, Currnt;
  unsigned int Cnt = 0;

  while (1)
  {
    if (IsDemo == 0)
    {
      if (IsStarted == 0)
      {
        SelectedColor = WhiteCl;
        if (digitalRead(Up) == 0)
        {
          if (Min < 99)
          {
            Min++;
          }
          ScreenTimeout = millis() + 60000;
          delay(150);
        }

        if (digitalRead(Down) == 0)
        {
          if (Min != 0)
          {
            Min--;
          }
          ScreenTimeout = millis() + 60000;
          delay(150);
        }

        if (digitalRead(Stop) == 0)
        {
          Min = 0;
          Sec = 0;
          ScreenTimeout = millis() + 60000;
        }

        if (digitalRead(StartPausa) == 0)
        {
          SelectedColor = GreenCl;
          IsStarted = 1;
          StartTime = millis();
          StopTime = millis() + (long)Min * 60 * 1000;
          ScreenTimeout = millis() + 60000;
          while (digitalRead(StartPausa) == 0)
          {

          }
          delay(300);
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

            if (Rest < 10)
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
            SelectedColor = RedCl;
          }

          if (digitalRead(Stop) == 0)
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

          if (digitalRead(StartPausa) == 0)
          {
            Diff_time = millis();
            IsPause = 1;
            ScreenTimeout = millis() + 60000;
            while (digitalRead(StartPausa) == 0)
            {

            }
            delay(300);
          }

        }
        else
        {
          if (digitalRead(StartPausa) == 0)
          {
            StartTime += millis() - Diff_time;
            StopTime += millis() - Diff_time;
            IsPause = 0;
            ScreenTimeout = millis() + 60000;
            while (digitalRead(StartPausa) == 0)
            {

            }
            delay(300);
          }

          if (digitalRead(Stop) == 0)
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
      { strip.setBrightness(70); rainbow(); }

      if(Cnt > 1000 && Cnt < 2000)
      { strip.setBrightness(70); filler(); }

      if(Cnt > 2000 && Cnt < 3000)
      { strip.setBrightness(50); colorCycle(); }

      if(Cnt > 3000 && Cnt < 3200)
      { strip.setBrightness(70); runningDots(); }

      if(Cnt > 3200)
      { breathing();}

      Cnt++;
      if(Cnt > 4400)
      { Cnt = 0;}
      
      strip.show();
      delay(30);

      if (digitalRead(Up) == 0)
      {
        ScreenTimeout = millis() + 60000;
        strip.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }

      if (digitalRead(Down) == 0)
      {
        ScreenTimeout = millis() + 60000;
        strip.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }

      if (digitalRead(StartPausa) == 0)
      {
        ScreenTimeout = millis() + 60000;
        strip.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }

      if (digitalRead(Stop) == 0)
      {
        ScreenTimeout = millis() + 60000;
        strip.setBrightness(Britn);
        IsDemo = 0;
        delay(150);
      }
    }
  }

}



void rainbow() {
  static byte counter = 0;
  for (int i = 0; i < NUMLEDS; i++) {
    strip.set(i, mWheel8(counter + i * 255 / NUMLEDS));   // counter смещает цвет
  }
  counter += 3;   // counter имеет тип byte и при достижении 255 сбросится в 0
}

void filler() {
  static int counter = 0, clrCount = 0;
  strip.clear();

  if(clrCount == 0)
  strip.fill(0, counter, mRed);

  if(clrCount == 1)
  strip.fill(0, counter, mGreen);

  if(clrCount == 2)
  strip.fill(0, counter, mBlue);

  
  counter++;
  if (counter >= NUMLEDS) 
  {
    counter = 0;
    clrCount++;
    if(clrCount == 3)
    {clrCount = 0;}
  }
}

void colorCycle() {
  static byte counter = 0;
  strip.fill(mWheel8(counter));
  counter += 3;
}

void runningDots() {
  static byte counter = 0;
  // перемотка буфера со сдвигом (иллюзия движения пикселей)
  for (int i = 0; i < NUMLEDS - 1; i++) strip.leds[i] = strip.leds[i + 1];

  // каждый третий вызов - последний пиксель красным, иначе чёрным
  if (counter % 3 == 0) strip.leds[NUMLEDS - 1] = mWhite;
  else strip.leds[NUMLEDS - 1] = mBlack;
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
  strip.setBrightness(bright);
}
