#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SLIDER A2

int x,y,xb,yb,score = 0,runner = 1;
int dx = 1,dy = 1;

void title(){
  display.clearDisplay();
  display.setTextSize(3);      
  display.setTextColor(SSD1306_WHITE);    
  display.setCursor(20, 2);
  display.println(F("PONG"));
  display.display();
  x=random(0,120);
  y=random(0,10);
  yb=31;
  delay(2000);
}

void taolookball(int x,int y){
  display.clearDisplay();
  display.drawPixel(x, y, SSD1306_WHITE);
  display.display();
}

void drawBar(int xb, int yb){
  display.drawFastHLine(xb,yb,15,WHITE);
  display.display();
  }

void gameOvereiei(int sc){
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);    
  display.setCursor(20, 2);
  display.println(F("Game Over"));
  display.setCursor(20, 12);
  display.println(F("Score: "));
  display.setCursor(70, 12);
  display.println(sc);
  display.display();
  delay(3000);
 }

void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    }
   //for(;;);
   title();
   
}
void loop(){
  if(runner == 1){
    drawBar(xb,yb);
    //Slider
    xb = map(analogRead(SLIDER), 0, 1024, 0, 117);
    
    taolookball(x,y);
    
    //Check deng
    if(x > 127){
      dx = -1;
    }
    if(y > 31){
      if(x > xb && x < xb+15){
          tone(9,440,300);
          score+=1;
          dy = -1;
        }
      else{
        runner = 0;
        }
     }
    if(x <= 0){
      dx = 1;
     }
    if(y <= 0){
      dy = 1;
     }
    x+=dx;
    y+=dy;
  }
  else{
    gameOvereiei(score);
    }
 }
