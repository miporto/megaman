#include <SDL_timer.h>
#include "Timer.h"

Timer::Timer() : ticks(0){}

void Timer::start() {
    ticks = SDL_GetTicks();
}

void Timer::stop() {
    ticks = 0;
}
unsigned int Timer::get_ticks() {
    return SDL_GetTicks() - ticks;
}
