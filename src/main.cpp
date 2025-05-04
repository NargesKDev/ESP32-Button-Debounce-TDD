#include "bsp.h"
#include <Arduino.h>
#include "button.h"

void setup()
{
    button_init(GPIO_NUM_34);
    Serial.begin(115200);
}

void loop()
{
    button_update_state();
    if (button_get_state() == 1)
        Serial.println("Button is released");
    else if (button_get_state() == 0)
        Serial.println("Button is pressed");
    if (button_get_fall_rise_state() == 4)
    {
        Serial.println("Falling Edge Happend");
        
        button_set();
    }
    else if (button_get_fall_rise_state() == 2)
    {
        Serial.println("RISING Edge Happend");
        button_set();
    }
    delay(200);
}