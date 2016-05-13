#ifndef PACKET_H
#define PACKET_H

#include <queue>
#include <string>
#include <sstream>
#include <string>
#include <vector>

#include "common/Thread.h"

typedef enum _packet_id {
    NEW_PLAYER = 1,
    STAGE_PICK,
    STAGE_INFO
} packet_id_t;

class Packet {
    public:
        virtual char get_id() const = 0;
        virtual std::string get_str() const = 0;
        virtual ~Packet();
};

class NewPlayer : public Packet {
    private:
        static const char id = NEW_PLAYER;
        const std::string name;

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

class StageInfo : public Packet {
    private:
        static const char id = STAGE_INFO;
        const char type;
        const char position;

    public:
        explicit StageInfo(const char position);
        StageInfo(const char type, const char position);
        char get_id() const;
        std::string get_str() const;
        ~StageInfo();
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
