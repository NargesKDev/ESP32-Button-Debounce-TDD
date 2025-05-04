#include "bsp.h"
#include "button.h"

#define INVALID 0xFFU
#define SAMPLES 5U

static uint8_t debounced_state = BUTTON_UNINITIALIZED; // Initial state is released
static uint8_t pin_num = INVALID;                      // Pin number
static uint8_t samples[SAMPLES] = {0};                 // Store the last 5 pin states
static uint8_t sample_index = 0;
static uint8_t button_state = BUTTON_UNINITIALIZED;
static uint8_t button_status = 0;

void button_init(uint8_t pin)
{
    pin_num = pin;
    bsp_pin_mode(pin, BSP_INPUT_PULLUP);
    debounced_state = BUTTON_RELEASED;
}

void button_update_state(void)
{
    int pin_state = bsp_digital_read(pin_num); // Get the current pin state
    // printf("%d\n", pin_state);

    //  Store it into the samples buffer
    samples[sample_index] = (uint8_t)pin_state;
    sample_index = (sample_index + 1U) % SAMPLES; // Circular buffer for samples

    // Check if all 5 samples are the same (either pressed or released)
    uint8_t all_same = 1;
    for (uint8_t i = 0; i < SAMPLES; ++i)
    {
        if (samples[i] != pin_state)
        {
            all_same = 0;
            break; // If any sample is different, break the loop
        }
    }

    // If all the values are the same, update the debounced state
    if (all_same)
    {
        if (pin_state == BUTTON_PRESSED && debounced_state != BUTTON_PRESSED)
        {
            debounced_state = BUTTON_PRESSED;

            button_state = BUTTON_FALLING_EDGE;
            button_status = 1;

            // printf("falling edge happens here");
        }
        else if (pin_state == BUTTON_RELEASED && debounced_state != BUTTON_RELEASED)
        {
            debounced_state = BUTTON_RELEASED;
            button_state = BUTTON_RISING_EDGE;
            button_status = 1;

            // printf("rising edge happens here");
        }
        else if (pin_state == BUTTON_RELEASED)
        {
            debounced_state = BUTTON_RELEASED;
        }
        else if (pin_state == BUTTON_PRESSED)
        {
            debounced_state = BUTTON_PRESSED;
        }
    }
}

uint8_t button_get_state(void)
{
    return debounced_state;
}

uint8_t button_get_fall_rise_state(void)
{
    return button_state;
}

void button_set(void)
{
    if (button_status == 1)
        button_state = BUTTON_UNINITIALIZED;
}
