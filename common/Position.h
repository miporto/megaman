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
        float x, y;

    public:
        Position(const float x, const float y);
        explicit Position(const std::vector<float>& position);
        void move(float x_amount, float y_amount);
        bool out_of_range();
        void reset();
        std::vector<float> get_position() const;

        bool operator==(const Position& other) const;
        std::string str() const;
        Position* clone() const;
        ~Position();
};

#endif //POSITION_H
