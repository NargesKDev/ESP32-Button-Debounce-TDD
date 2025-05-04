#include "bsp.h"
#ifdef PIO_UNIT_TESTING
#include <Arduino.h>
#endif
#define INVALID 0xFFU

static uint8_t button_pin_state = 3;
static bool button_pin_status = true; // Default to active high (pressed when HIGH)
static uint8_t button_pin_num = INVALID;
static uint8_t button_pin_mode = INVALID;

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    button_pin_num = pin;
    button_pin_mode = mode;

#ifdef PIO_UNIT_TESTING
    pinMode(pin, mode);
#endif
}

int bsp_digital_read(uint8_t pin)
{
    button_pin_num = pin;

#ifdef PIO_UNIT_TESTING
    return button_pin_status ? digitalRead(pin) : !digitalRead(pin);
#else
    return button_pin_status ? button_pin_state : !button_pin_state;
#endif
}

void bsp_set_button_pin_state(uint8_t pin, uint8_t state)
{
    if (pin == button_pin_num)
    {
        button_pin_state = state;
    }
}

void bsp_set_button_pin_status(bool status)
{
    button_pin_status = status;
}

uint8_t bsp_get_button_pin_num(void)
{
    return button_pin_num;
}

uint8_t bsp_get_button_pin_mode(void)
{
    return button_pin_mode;
}

//  (PESSED/RELEASED)
uint8_t bsp_get_button_pin_state(void)
{
    return button_pin_state;
}
