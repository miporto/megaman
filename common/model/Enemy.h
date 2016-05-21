#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
    private:
        char position;

    public:
        explicit Enemy(const char initial_position);
        virtual ~Enemy();
};

#endif //ENEMY_H
