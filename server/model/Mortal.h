#ifndef MORTAL_H
#define MORTAL_H

class Mortal {
    public:
        virtual void decrease_energy(int amount) = 0;
        virtual bool is_dead() = 0;
        virtual ~Mortal() {}
};

#endif //MORTAL_H
