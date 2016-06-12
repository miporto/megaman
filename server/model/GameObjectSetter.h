#ifndef SERVERSTAGESETTER_H
#define SERVERSTAGESETTER_H

#include <vector>
#include <string>

#include "GameObjectHandler.h"
#include "GameObjectParser.h"

class GameObjectSetter {
    private:
        void to_classes(GameObjectParserInfo& positions,
                        GameObjectHandler* handler);

    public:
        GameObjectSetter(const std::string& info, GameObjectHandler* handler);
        ~GameObjectSetter();
};

#endif //SERVERSTAGESETTER_H
