#ifndef MEGAMAN_TIMER_H
#define MEGAMAN_TIMER_H


class Timer {
public:
    Timer();
    void start();
    void stop();
    unsigned int get_ticks();
    ~Timer() {}
private:
    unsigned int ticks;
};


#endif //MEGAMAN_TIMER_H
