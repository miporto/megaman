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

class Stage {
    private:
        char id;
        std::vector<Player*>& players;
        //vector de enemigos

public:
    Stage(std::vector<Player*>& players);
    bool has_started();
    void operator()(char id);
    ~Stage();
};

#endif //STAGE_H
