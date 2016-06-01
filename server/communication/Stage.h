#ifndef STAGE_H
#define STAGE_H

#include <vector>

#include "common/Thread.h"
#include "server/model/MegaMan.h"
#include "common/communication/Packet.h"
#include "server/model/Object.h"
#include "server/model/Enemy.h"
#include "server/model/Factory.h"

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
