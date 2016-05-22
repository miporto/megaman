#ifndef POSITION_H
#define POSITION_H

#include <string>

class Clonable {
    public:
        virtual Clonable* clone() const = 0;
        virtual ~Clonable() {}
};

class Position : public Clonable {
    private:
        int x, y;

    public:
        Position(int x, int y);
        void move(int x_amount, int y_amount);
        void reset();
        bool operator==(const Position& other) const;
        std::string str() const;
        Position* clone() const;
        ~Position();
};

#endif //POSITION_H
