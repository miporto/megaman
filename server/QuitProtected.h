#ifndef QUITPROTECTED_H
#define QUITPROTECTED_H

#include "common/commonThread.h"

class QuitProtected {
private:
    Mutex m;
    bool quit;

public:
    QuitProtected();
    void switch_to_true();
    bool operator()();
    ~QuitProtected();
};

#endif //QUITPROTECTED_H
