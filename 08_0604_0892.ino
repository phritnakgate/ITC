#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED     6
#define YELLOW  7
#define GREEN   8

#define SW1     2
#define SW2     3
#define SW3     4

int YState = LOW;
unsigned long previousMillis = 0;

const long interval = 300; 

bool rstat = 0;
bool ystat = 0;
bool gstat = 0;

QueueHandle_t ledREDQueue = nullptr;
QueueHandle_t ledYELLOWQueue = nullptr;
QueueHandle_t ledGREENQueue = nullptr; 

const uint8_t *SWR = (uint8_t *) 2;
const uint8_t *SWY = (uint8_t *) 3;
const uint8_t *SWG = (uint8_t) 4;
const uint8_t taskParam[3][2] = { {SWR,rstat}, 
    {SWY, ystat}, 
    {SWG, gstat} };


void setup() {
  Serial.begin(9600);
  ledREDQueue =  xQueueCreate(20,sizeof(bool));
  ledYELLOWQueue =  xQueueCreate(1,sizeof(bool));
  ledGREENQueue =  xQueueCreate(1,sizeof(bool));
      
  xTaskCreate(redFunction, "buttonRED", 128, &taskParam[0], 1, NULL);
  xTaskCreate(yellowFunction, "buttonYELLOW", 128, &taskParam[1], 1, NULL);
  xTaskCreate(greenFunction, "buttonGREEN", 128, &taskParam[2], 1, NULL);
  xTaskCreate(LEDRED, "LEDRED", 64, NULL, 1, NULL);
  xTaskCreate(LEDYELLOW, "LEDYELLOW", 64, NULL, 1, NULL);
  xTaskCreate(LEDGREEN, "LEDGREEN", 64, NULL, 1, NULL);
}
void redFunction(void *pvParameters)
{
    uint8_t *SW = pvParameters;
    int ledPin= SW[0];
    int Bool = SW[1];
    pinMode(ledPin, INPUT_PULLUP);
    Serial.println(ledPin);
    while (true)
    {
        Serial.print("ledpin: ");
        Serial.println(ledPin);
        bool isPressed = !digitalRead(ledPin);
        Serial.print("isPress: ");
        Serial.println(isPressed);
        if (isPressed && isPressed != Bool)
        {
            Serial.println(xQueueSend(ledREDQueue, &isPressed, 0));
        }
        Bool = isPressed;
        vTaskDelay(10);
    }
}


void yellowFunction(void *pvParameters)
{
    uint8_t *SW = pvParameters;
    int ledPin= SW[0];
    int Bool = SW[1];
    pinMode(ledPin, INPUT_PULLUP);
    Serial.println(ledPin);
    while (true)
    {
        Serial.print("ledpin: ");
        Serial.println(ledPin);
        bool isPressed = !digitalRead(ledPin);
        Serial.print("isPress: ");
        Serial.println(isPressed);
        if (isPressed && isPressed != Bool)
        {
            Serial.println(xQueueSend(ledYELLOWQueue, &isPressed, 0));
        }
        Bool = isPressed;
        vTaskDelay(10);
    }
}

void greenFunction(void *pvParameters)
{
    uint8_t *SW = pvParameters;
    int ledPin= SW[0];
    int Bool = SW[1];
    pinMode(ledPin, INPUT_PULLUP);
    Serial.println(ledPin);
    while (true)
    {
        Serial.print("ledpin: ");
        Serial.println(ledPin);
        bool isPressed = !digitalRead(ledPin);
        Serial.print("isPress: ");
        Serial.println(isPressed);
        if (isPressed && isPressed != Bool)
        {
            Serial.println(xQueueSend(ledGREENQueue, &isPressed, 0));
        }
        Bool = isPressed;
        vTaskDelay(10);
    }
}


void LEDRED()
{
    pinMode(RED, OUTPUT);
    while (true)
    {
        if (xQueueReceive(ledREDQueue, nullptr, 10))
        {
            digitalWrite(RED, HIGH);
            vTaskDelay(pdMS_TO_TICKS(3000));
        }
        else
        {
            digitalWrite(RED, LOW);
        }
    }
}

void LEDYELLOW()
{
    pinMode(YELLOW, OUTPUT);
    bool blinking = true;
    while (true)
    {
        if (xQueueReceive(ledYELLOWQueue, nullptr, 1))
            blinking = !blinking;
        if (blinking)
        {
          unsigned long currentMillis = millis();
          if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            if (YState == LOW) {
              YState = HIGH;
            } else {
              YState = LOW;
            }
            digitalWrite(YELLOW, YState);
         }
        }
        else
        {
            digitalWrite(YELLOW, LOW);
        }
          
    }
}

void LEDGREEN()
{
    pinMode(GREEN, OUTPUT);
    while (true)
    {
        if (xQueueReceive(ledGREENQueue, nullptr, 10))
        {
         xQueueSend(ledGREENQueue, nullptr, 0);
            for (size_t i = 0; i < 6; i++)
            {
                digitalWrite(GREEN, !digitalRead(GREEN));
                vTaskDelay(pdMS_TO_TICKS(500) - 1);
            }
            xQueueReceive(ledGREENQueue, nullptr, 0);
      }
  }
}
void loop() {
  
}
