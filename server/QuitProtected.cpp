#include "QuitProtected.h"
#include "common/commonThread.h"

QuitProtected::QuitProtected() {
    this->quit = false;
}

void QuitProtected::switch_to_true() {
    Lock l(this->m);
    this->quit = true;
}

bool QuitProtected::operator()() {
    Lock l(this->m);
    return this->quit;
}

QuitProtected::~QuitProtected() {}