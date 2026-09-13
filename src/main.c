#include <f401-re-hal.h>
#include <timer.h>

#include <board_definition.h>

#define TICK_FREQUENCY_HZ (1000)
#define TIMER_DELAY_MSEC (500)
#define TIMER_DELAY_TICKS (((TICK_FREQUENCY_HZ) * (TIMER_DELAY_MSEC)) / 1000)

static void set_led_counter_value(uint8_t value);

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

    gpio_config_t gpio_init =
    {
        .mode = GPIO_MODE_OUTPUT,
    };

    GPIO_Init(Offboard_LED_GPIO_Port, Offboard_LED_Pin_Red, &gpio_init);
    GPIO_Init(Offboard_LED_GPIO_Port, Offboard_LED_Pin_Green, &gpio_init);
    GPIO_Init(Offboard_LED_GPIO_Port, Offboard_LED_Pin_Blue, &gpio_init);

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
    GPIO_Write(Offboard_LED_GPIO_Port, Offboard_LED_Pin_Red, !!(value & 0x1));
    GPIO_Write(Offboard_LED_GPIO_Port, Offboard_LED_Pin_Green, !!(value & 0x2));
    GPIO_Write(Offboard_LED_GPIO_Port, Offboard_LED_Pin_Blue, !!(value & 0x4));
}
