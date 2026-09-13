//
// Created by tomly on 07/09/2026.
//

#include <timer.h>

void Timer_Init(timer_t* timer, get_ticks_t* get_ticks)
{
    timer->get_ticks = get_ticks;
    timer->start_time = 0;
    timer->duration = 0;
}

void Timer_Start(timer_t* timer, uint32_t duration)
{
    timer->start_time = timer->get_ticks();
    timer->duration = duration;
}

int Timer_IsRunning(const timer_t* timer)
{
    return timer->duration > timer->get_ticks() - timer->start_time;
}
