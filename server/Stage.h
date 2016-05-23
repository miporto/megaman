#ifndef STAGE_H
#define STAGE_H

#include <vector>

#include "common/Thread.h"
#include "model/Player.h"
#include "common/StageInfo.h"
#include "common/Packet.h"
#include "model/Object.h"
#include "model/Enemy.h"
#include "model/Factory.h"

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
