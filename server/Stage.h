#ifndef STAGE_H
#define STAGE_H

#include <vector>

#include "common/Thread.h"
#include "Player.h"

class StageIDProtected {
private:
    Mutex m;
    char stage_id;

public:
    StageIDProtected();
    void set_id(char stage_id);
    char operator()();
    ~StageIDProtected();
};

class StageFactory {
    private:
        char id;

    public:
        StageFactory(char id);
        ~StageFactory();
};

class Stage {
    private:
        StageFactory factory;
        std::vector<Player*>& players;

public:
    Stage(char id, std::vector<Player*>& players);
    ~Stage();
};

#endif //STAGE_H
