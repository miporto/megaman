#ifndef PACKET_H
#define PACKET_H

#include <queue>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "common/Position.h"
#include "common/Thread.h"

typedef enum _packet_id {
    NEW_PLAYER = 1,
    STAGE_PICK,
    STAGE_INFO,
    DECEASED,
    ACTION
} packet_id_t;

typedef enum _action_packet_id {
    RIGHT = 1,
    LEFT,
    UP,
    SHOOT,
    END
} action_packet_id_t;

typedef enum _stage_id {
    BOMBMAN = 1,
    SPARKMAN,
    FIREMAN,
    RINGMAN,
    MAGNETMAN
} stage_id_t;

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
        std::string stage_info;

    public:
        explicit StageInfo(const std::string& stage_info);
        char get_id() const;
        std::string get_str() const;
        const std::string& get_info() const;
        ~StageInfo();
};

class Deceased : public Packet {
    private:
        static const char id = DECEASED;
        const char object_id;

    public:
        explicit Deceased(const char object_id);
        char get_id() const;
        std::string get_str() const;
        char get_object_id() const;
        ~Deceased();
};

class Action : public Packet {
    private:
        static const char id = ACTION;
        const std::string name;
        const char action_id;
        const bool pressed;

    public:
        Action(const std::string& name,
               const char action_id, const bool pressed);
        Action(const std::string& name,
               const char action_id, const char pressed);
        char get_id() const;
        char get_action() const;
        const std::string& get_name() const;
        bool is_pressed() const;
        std::string get_str() const;
        virtual ~Action();
};

class Right : public Action {
    public:
        explicit Right(const std::string& name, const bool pressed);
};

class Left : public Action {
    public:
        explicit Left(const std::string& name, const bool pressed);
};

class Up : public Action {
    public:
        explicit Up(const std::string& name, const bool pressed);
};

class Shoot : public Action {
    public:
        explicit Shoot(const std::string& name, const bool pressed);
};

class PacketsQueueProtected {
    private:
        Mutex m;
        std::vector<Packet*> packets;

    public:
        bool is_empty();
        Packet* pop();
        void push(Packet* packet);
        ~PacketsQueueProtected();
};

class ReceivedPacketsProtected {
    private:
        Mutex m;
        std::map<char, std::vector<Packet*>> packets;
        PacketsQueueProtected actions;

    public:
        bool is_empty(const char id);
        Packet* pop(const char id);
        void push(Packet* packet);
        PacketsQueueProtected* get_actions();
        ~ReceivedPacketsProtected();
};

#endif  // PACKET_H
