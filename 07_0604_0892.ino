#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


# define OLED_RESET 4
# define SCREEN_W 128
# define SCREEN_H 32
# define Buzzer 12
Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, OLED_RESET);

int hours = 0;
int minutes = 0;
int seconds = 59;
int Timer_hours;
int Timer_minutes;
const int Timer_seconds = 0;
bool Time_Stop = 1;

unsigned long currentMillis = 0;
int elapsedTimeUpdateMillis = 0;
unsigned long previousTimeUpdateMillis = 0;

const int PIN_BUTTON_TIMER_MODE = 4;
const int PIN_BUTTON_MODE = 3;
const int PIN_BUTTON_SET = 2;

unsigned long elapsedMusicMillis = 0;
unsigned long previousMusicMillis = 0;
struct music {
  int note;
  int Time; 
};     
typedef const struct music Test;
Test Music[56]={

  {NOTE_D5,125},
  {NOTE_CS5,125},
  {NOTE_B4,250},
  {NOTE_FS4,250},
  {0,125},
  {NOTE_FS4,125},
  {NOTE_FS4,125},
  {NOTE_FS4,125},
  {NOTE_FS4,125},
  {NOTE_FS4,125},

  {NOTE_B4,125},
  {NOTE_B4,125},
  {NOTE_B4,125},
  {NOTE_B4,125},
  {NOTE_A4,250},
  {NOTE_B4,125},
  {0,125},
  
  {NOTE_G4,125},
  {0,125},
  {0,125},
  {NOTE_G4,125},
  {0,125},
  {NOTE_G4,125},
  {NOTE_G4,125},
  {NOTE_G4,125},
  {NOTE_G4,125},
  {NOTE_G4,125},
  
  {NOTE_B4,125},
  {NOTE_B4,150},
  {NOTE_B4,150},
  {NOTE_B4,150},
  {NOTE_CS5,250},
  {NOTE_D5,250},
  {0,125},
  {0,125},
  {NOTE_A4,125},
  {0,125},
  
  {NOTE_A4,125},
  {NOTE_A4,125},
  {NOTE_A4,125},
  {NOTE_A4,125},
  
  {NOTE_D5,250},
  {NOTE_CS5,125},
  {NOTE_D5,125},
  {NOTE_CS5,125},
  {NOTE_D5,125},
  {NOTE_E5,125},
  {NOTE_E5,125},  
};

int BUTTON_MODE_DEBOUNCE_TIME = 250;
int BUTTON_SET_DEBOUNCE_TIME = 175;

unsigned long elapsedButtonModeMillis = 0;
unsigned long previousButtonModeMillis = 0;

unsigned long elapsedButtonSetMillis = 0;
unsigned long previousButtonSetMillis = 0;

const int MODE_SHOW_TIME = 0;
const int MODE_SET_MINUTES = 2;
const int MODE_SET_HOURS = 1;
const int MODE_SET_TIMER_MINUTES = 4;
const int MODE_SET_TIMER_HOURS = 3;
byte currentMode = MODE_SHOW_TIME;
byte previousMode = 0;

int vr_pin = A0;
int led_pin = 9;
bool light = false;

void setup() 
{
  pinMode(vr_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  Serial.begin(9600);
  hours = EEPROM.read(0);
  minutes = EEPROM.read(1);
  Timer_hours = EEPROM.read(2);
  Timer_minutes = EEPROM.read(3);
  display.clearDisplay();
  drawTime();
  display.display();
}
int i = 1;
void loop() 
{ 
  display.fillScreen(BLACK);
  currentMillis = millis();
  checkTime();
  if (currentMode > 2) 
  {
    increaseSeconds();
    checkTimer();
    drawTimer();
    if(currentMode == 3)
    {
      display.drawTriangle(22 , 0, 29, 3, 36, 0, WHITE);   
    }
    else
    {
      display.drawTriangle(87 , 0, 94, 3, 101, 0, WHITE);
    }
  } 
  else if (currentMode == MODE_SHOW_TIME) 
  {
    increaseSeconds();
    drawTime();
    if(hours == Timer_hours && minutes == Timer_minutes && seconds == Timer_seconds)
    {
      Time_Stop = 0;
    }
    elapsedMusicMillis = currentMillis - previousMusicMillis;
    //Serial.println(seconds);
    if(Time_Stop == 0 && elapsedMusicMillis> Music[i-1].Time)
    {
      tone(Buzzer,Music[i].note,Music[i].Time);
      i++;
      previousMusicMillis = currentMillis;
      if(i > 56){
        i = 1; 
      }
      light = true;
      
    }
    else if (Time_Stop == 1){
      noTone(12);
      i=1;
    }
  } 
  else 
  {
    previousTimeUpdateMillis = currentMillis;
    drawTime();
    if(currentMode == 1)
    {
      display.drawTriangle(22 , 0, 29, 3, 36, 0, WHITE);   
    }
    else
    {
      display.drawTriangle(87 , 0, 94, 3, 101, 0, WHITE);
    }
  }
  
  if (digitalRead(PIN_BUTTON_TIMER_MODE) == LOW) {
    buttonTimerModeHandler();
    Time_Stop = 1;
    light = false;
    analogWrite(led_pin,0);
  }
  if (digitalRead(PIN_BUTTON_MODE) == LOW) {
    buttonModeHandler();
    Time_Stop = 1;
    light = false;
    analogWrite(led_pin,0);
  }
  if (digitalRead(PIN_BUTTON_SET) == LOW) {
    buttonSetHandler();
    Time_Stop = 1;
    light = false;
    analogWrite(led_pin,0);
  }
  if(light == true){
    int vr = analogRead(vr_pin);
    int vr1 = map(vr,0,1023,0,255);
    analogWrite(led_pin,vr1);
    //Serial.println(vr1);
  }
  display.display();
}

void drawTime()
{
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if (hours<10){
    display.setCursor(9, 5);
    display.println("0");
    display.setCursor(39, 5);
    display.println(hours);
  }
  else{
    display.setCursor(9, 5);
    display.println(hours);
  }
  display.setCursor(54, 5);
  display.println(":");
  if (minutes<10){
    display.setCursor(74, 5);
    display.println("0");
    display.setCursor(104, 5);
    display.println(minutes);
  }
  else{
    display.setCursor(74, 5);
    display.println(minutes);
  }
}

void drawTimer()
{
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if (Timer_hours<10){
    display.setCursor(9, 5);
    display.println("0");
    display.setCursor(39, 5);
    display.println(Timer_hours);
  }
  else{
    display.setCursor(9, 5);
    display.println(Timer_hours);
  }
  display.setCursor(54, 5);
  display.println(":");
  if (Timer_minutes<10){
    display.setCursor(74, 5);
    display.println("0");
    display.setCursor(104, 5);
    display.println(Timer_minutes);
  }
  else{
    display.setCursor(74, 5);
    display.println(Timer_minutes);
  } 
}

void checkTime() {
  if (seconds > 59) 
  {
    seconds = 0;
    minutes++;
    //EEPROM.put(1, minutes);
  }
  if (minutes > 59) 
  {
    minutes = 0;
    hours++;
    //EEPROM.put(0, hours);
  }
  if (hours > 23) 
  {
    hours = 0;
  }
}

void checkTimer() {
  if (Timer_minutes > 59) 
  {
    Timer_minutes = 0;
    Timer_hours++;
  }
  if (Timer_hours > 23) 
  {
    Timer_hours = 0;
  }
}

void increaseSeconds() 
{
  elapsedTimeUpdateMillis = currentMillis - previousTimeUpdateMillis;

  if (elapsedTimeUpdateMillis > 1000) 
  {
    seconds++;
    previousTimeUpdateMillis = currentMillis - (elapsedTimeUpdateMillis - 1000);
  }
}

void buttonModeHandler() 
{
  previousMode = 0;
  elapsedButtonModeMillis = currentMillis - previousButtonModeMillis;
  if (elapsedButtonModeMillis > BUTTON_MODE_DEBOUNCE_TIME) 
  {
    previousButtonModeMillis = currentMillis;
    currentMode++;

    if (currentMode > 2) 
    {
      currentMode = 0;
      //EEPROM.update(1, minutes);
      //EEPROM.update(0, hours);
    }

  }
}

void buttonTimerModeHandler() 
{
  elapsedButtonModeMillis = currentMillis - previousButtonModeMillis;
  if (elapsedButtonModeMillis > BUTTON_MODE_DEBOUNCE_TIME) 
  {
    previousButtonModeMillis = currentMillis;
    currentMode = 3;
    currentMode+=previousMode;
    previousMode++;

    if (currentMode > 4) 
    {
      currentMode = 0;
      previousMode = 0;
      //EEPROM.update(3, Timer_minutes);
      //EEPROM.update(2, Timer_hours);
    }
  }
}

void buttonSetHandler() 
{
  elapsedButtonSetMillis = currentMillis - previousButtonSetMillis;
  if (elapsedButtonSetMillis > BUTTON_SET_DEBOUNCE_TIME) 
  {
    previousButtonSetMillis = currentMillis;

    if (currentMode == MODE_SET_MINUTES) 
    {
      minutes++;
    }
    if (currentMode == MODE_SET_HOURS) 
    {
      hours++;
    }
    if (currentMode == MODE_SET_TIMER_MINUTES) 
    {
      Timer_minutes++;
    }
    if (currentMode == MODE_SET_TIMER_HOURS) 
    {
      Timer_hours++;
    }
  }
}
