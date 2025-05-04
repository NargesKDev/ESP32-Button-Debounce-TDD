#include "bsp.h"
#include <Arduino.h>

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

int bsp_digital_read(uint8_t pin)
{
    return digitalRead(pin);
}
