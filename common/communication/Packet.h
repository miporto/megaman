#ifndef PACKET_H
#define PACKET_H

#include <queue>
#include <string>
#include <sstream>
#include <string>
#include <vector>

#include "common/Position.h"
#include "common/Thread.h"

#define NAME_LENGTH 8

typedef enum _packet_id {
    NEW_PLAYER = 1,
    STAGE_PICK,
    STAGE_ELEMENT
} packet_id_t;

typedef enum _stage_info_type_t {
    MET = 1,
    BUMBY,
    SNIPER,
    JUMPING_SNIPER,
    BLOCK,
    STAIRS,
    SPIKE,
    CLIFF
} stage_info_type_t;

class Packet {
    public:
        virtual char get_id() const = 0;
        virtual std::string get_str() const = 0;
        virtual ~Packet();
};

class NewPlayer : public Packet {
    private:
        static const char id = NEW_PLAYER;
        std::string name;

    public:
        explicit NewPlayer(const std::string name);
        const std::string get_name() const;
        char get_id() const;
        std::string get_str() const;
        ~NewPlayer();
};

class StagePick : public Packet {
    private:
        static const char id = STAGE_PICK;
        const char stage_id;

    public:
        explicit StagePick(const char stage_id);
        char get_stage_id() const;
        char get_id() const;
        std::string get_str() const;
        ~StagePick();
};

class StageElement : public Packet {
    private:
        static const char id = STAGE_ELEMENT;
        const char type;
        Position* position;

    public:
        explicit StageElement(Position* position);
        StageElement(const char type, Position* position);
        char get_id() const;
        char get_type() const;
        Position* get_position() const;
        std::string get_str() const;
        ~StageElement();
};

class PacketsProtected {
    private:
        Mutex m;
        std::vector<Packet*> packets;

    public:
        Packet* pop();
        void push(Packet* packet);
        bool is_empty();
        ~PacketsProtected();
};

#endif  // PACKET_H
