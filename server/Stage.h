#ifndef STAGE_H
#define STAGE_H

#include <vector>

#include "common/Thread.h"
#include "common/model/Player.h"
#include "common/StageInfo.h"
#include "common/Packet.h"
#include "common/model/Object.h"
#include "common/model/Enemy.h"
#include "Factory.h"

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

#endif  // STAGE_H
