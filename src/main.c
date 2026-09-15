#include <f401_re_hal.h>
#include <timer.h>

#include <board_definition.h>

#define TICK_FREQUENCY_HZ (1000)
#define TIMER_DELAY_MSEC (500)
#define TIMER_DELAY_TICKS (((TICK_FREQUENCY_HZ) * (TIMER_DELAY_MSEC)) / 1000)

static void set_led_counter_value(uint8_t value);

static void test_button_trigger(void* p)
{
    static int irq_counter = 0;
    
    irq_counter++;
}

int main(void) 
{
    systick_cfg_t systick_cfg =
    {
        .tick_freq = TICK_FREQUENCY_HZ,
        .clk_src = SYSTICK_CLK_SRC_AHB_DIV_8,
        .enable_irq = TRUE,
        .enable_counter = TRUE
    };

    if (SysTick_Init(&systick_cfg) != TRUE)
        return -1;

    gpio_config_t gpio_output_init =
    {
        .mode = GPIO_MODE_OUTPUT,
    };

    GPIO_Init(LED_GPIO_PORT, LED_PIN_RED, &gpio_output_init);
    GPIO_Init(LED_GPIO_PORT, LED_PIN_GREEN, &gpio_output_init);
    GPIO_Init(LED_GPIO_PORT, LED_PIN_BLUE, &gpio_output_init);
    
    gpio_config_t gpio_input_init =
    {
        .mode = GPIO_MODE_INPUT,
        .pupd = GPIO_PUPD_PULLDOWN
    };
    
    GPIO_Init(BUTTON_GPIO_PORT, BUTTON_PIN, &gpio_input_init);
    
    gpio_interrupt_cfg_t gpio_interrupt =
    {
        .type = GPIO_INTERRUPT_ANY_EDGE,
        .callback = test_button_trigger,
    };
    
    if (!GPIO_EnableInterrupt(BUTTON_GPIO_PORT, BUTTON_PIN, &gpio_interrupt))
    {
        while (1);
    }

    timer_t timer;
    Timer_Init(&timer, SysTick_GetTick);

    uint8_t i = 0;

    while (1)
    {
        if (Timer_IsRunning(&timer))
            continue;
        
        set_led_counter_value(i);

        Timer_Start(&timer, TIMER_DELAY_TICKS);
        i++;
    }
    
    return 0;
}

static void set_led_counter_value(uint8_t value)
{
    GPIO_Write(LED_GPIO_PORT, LED_PIN_RED, !!(value & 0x1));
    GPIO_Write(LED_GPIO_PORT, LED_PIN_GREEN, !!(value & 0x2));
    GPIO_Write(LED_GPIO_PORT, LED_PIN_BLUE, !!(value & 0x4));
}
