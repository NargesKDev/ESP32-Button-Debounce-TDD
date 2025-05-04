#ifndef BUTTON_H
#define BUTTON_H
#include <stdio.h>

#include <stdint.h>

#define BUTTON_UNINITIALIZED (3U)
#define BUTTON_FALLING_EDGE (4U)
#define BUTTON_RISING_EDGE (2U)
#define BUTTON_RELEASED (1U)
#define BUTTON_PRESSED (0U)

/**
 * @brief This function is used to initialize the module.
 *
 * @param pin The pin number used to connect a button.
 */
void button_init(uint8_t pin);

/**
 * @brief This function is used to update the debounced state of the button.
 *        This function is called intervally by the client.
 *
 */
void button_update_state(void);

/**
 * @brief This function is used to get the debounced state of the button.
 *
 * @return uint8_t The state; BUTTON_UNINITIALIZED if the module has not been initialized, otherwise
 *                            BUTTON_PRESSED, BUTTON_RELEASED, BUTTON_RISING_EDGE or BUTTON_FALLING_EDGE
 */
uint8_t button_get_state(void);

uint8_t button_get_fall_rise_state(void);

void button_set(void);
#endif /* BUTTON_H */
