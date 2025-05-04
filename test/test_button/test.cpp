#include "unity.h"
#include "bsp.h"
#include "button.h"

#ifdef PIO_UNIT_TESTING
#include <Arduino.h>
#endif
static const uint8_t pin_num = 34;
#define SAMPLES 5

void setUp(void)
{
}

void tearDown(void)
{
}

void test_button_initialization(void)
{
    button_init(pin_num);
    TEST_ASSERT_EQUAL_UINT8(pin_num, bsp_get_button_pin_num());
    TEST_ASSERT_EQUAL_UINT8(BSP_INPUT_PULLUP, bsp_get_button_pin_mode());
    TEST_ASSERT_EQUAL_UINT8(3, bsp_get_button_pin_state());
}

static void simulate_button_state(uint8_t state, uint8_t times)
{
    for (int i = 0; i < times; ++i)
    {
        bsp_set_button_pin_state(pin_num, state);
        button_update_state();
    }
}
void test_button_state_detection(void)
{
    button_init(pin_num);
    simulate_button_state(BUTTON_RELEASED, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());

    // testing falling edge
    simulate_button_state(BUTTON_PRESSED, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, button_get_fall_rise_state());

    // testing pressed edge
    simulate_button_state(BUTTON_PRESSED, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());

    // testing rising edge
    simulate_button_state(BUTTON_RELEASED, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, button_get_fall_rise_state());
    button_set();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_UNINITIALIZED, button_get_fall_rise_state());
}
#ifdef PIO_UNIT_TESTING
void loop() {}
void setup()
#else
int main(void)
#endif
{
    UNITY_BEGIN();
    RUN_TEST(test_button_initialization);
    RUN_TEST(test_button_state_detection);

    return UNITY_END();
}
