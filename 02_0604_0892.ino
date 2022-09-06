#define button1 12 
#define button2 11
#define button3 10
#define LED1 4
#define LED2 3
#define LED3 2
#define delayTime 80
#define TogLED(a, i)                         \
    {                                           \
        if (millis() - cooldown[i] > delayTime) \
        {                                       \
            begin[i] = millis();                \
            LedState[i] = !LedState[i];         \
            digitalWrite(a, LedState[i]);       \
        }                                       \
        cooldown[i] = millis();                 \
    }

int button[3] = {button1, button2, button3};

bool LedState[3] = {LOW, LOW, LOW};
bool Y = LOW;
bool ButtonState[3] = {LOW, HIGH, HIGH};
bool LastState[3] = {LOW, HIGH, HIGH};
bool reading[3];

long int begin[3] = {0, -2000, 0};
unsigned long long int lastDebounceTime[3];
unsigned long long int cooldown[3];


void debounce(int i)
{
    reading[i] = digitalRead(button[i]);
    if (reading[i] != LastState[i])
        lastDebounceTime[i] = millis();

    if (millis() - lastDebounceTime[i] > delayTime)
    {
        ButtonState[i] = reading[i];
    }
    LastState[i] = reading[i];
}
void setup()
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(button1, INPUT);        
    pinMode(button2, INPUT);        
    pinMode(button3, INPUT_PULLUP);
}
void loop()
{
    debounce(0); 
    if (!LedState[0])
    {
        debounce(2); 
        if (!LedState[2])
            debounce(1); 
    }
    if (millis() - begin[0] > 3000) 
    {
        LedState[0] = LOW;
        digitalWrite(LED1, LedState[0]);
    }
    if (millis() - begin[2] > 3000) 
    {
        LedState[2] = LOW;
        digitalWrite(LED3, LedState[2]);
    }
    if (millis() - begin[1] > 2000) 
    {
        LedState[1] = LOW;
        digitalWrite(LED2, LedState[1]);
    }
    else
    {
        if (millis() - begin[1] < 500)
        {
            Y = HIGH;
            digitalWrite(LED2, Y);
        }
        else if (millis() - begin[1] < 1000)
        {
            Y = LOW;
            digitalWrite(LED2, Y);
        }
        else if (millis() - begin[1] < 1500)
        {
            Y = HIGH;
            digitalWrite(LED2, Y);
        }
    }
    
    if (ButtonState[0] == HIGH)
        TogLED(LED1, 0) 
    if (ButtonState[1] == LOW)
        TogLED(LED2, 1) 
    if (ButtonState[2] == LOW)
        TogLED(LED3, 2)
}
