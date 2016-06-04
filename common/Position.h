#ifndef POSITION_H
#define POSITION_H

#include <vector>
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
        Position(const int x, const int y);
        explicit Position(const std::vector<int>& position);
        void move(int x_amount, int y_amount);
        bool out_of_range();
        void reset();
        std::vector<int> get_position() const;

        bool operator==(const Position& other) const;
        std::string str() const;
        Position* clone() const;
        ~Position();
};

#endif //POSITION_H
