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

#define NAME_LENGTH 8
#define INFO_LENGTH 1024

typedef enum _packet_id {
    NEW_PLAYER = 1,
    STAGE_PICK,
    STAGE,
    ACTION
} packet_id_t;

typedef enum _action_packet_id {
    RIGHT = 1,
    LEFT,
    UP,
    SHOOT
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

class Stage : public Packet {
    private:
        static const char id = STAGE;
        std::string stage_info;

    public:
        explicit Stage(const std::string stage_info);
        char get_id() const;
        std::string get_str() const;
        std::string get_info() const;
        ~Stage();
};

class Action : public Packet {
    private:
        static const char id = ACTION;
        std::string name;
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
