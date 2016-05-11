#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:

    public:
        virtual ~Player();
};

// Ver si el comportamiento difiere de Player
class Host : public Player {
    private:

    public:
        ~Host();
};

#endif //PLAYER_H
