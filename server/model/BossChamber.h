#ifndef BOSSCHAMBER_H
#define BOSSCHAMBER_H

class BossChamber {
    public:
        explicit BossChamber(const char boss_id);
        void run();
        bool beated();
        ~BossChamber();
};

#endif //BOSSCHAMBER_H
