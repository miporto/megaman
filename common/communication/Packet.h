#ifndef PACKET_H
#define PACKET_H

#include <queue>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <common/SystemError.h>

#include "server/model/Position.h"
#include "common/Thread.h"

typedef enum _packet_id {
    NEW_PLAYER = 1,
    STAGE_PICK,
    STAGE_INFO,
    CHAMBER_INFO,
    UPDATE,
    FLOAT_UPDATE,
    ENEMY_FLOAT_UPDATE,
    MEGAMAN_FLOAT_UPDATE,
    BOSS_FLOAT_UPDATE,
    DECEASED,
    ACTION
} packet_id_t;

typedef enum _action_packet_id {
    AMMO_0,
    AMMO_1,
    AMMO_2,
    AMMO_3,
    AMMO_4,
    AMMO_5,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    SHOOT
} action_packet_id_t;

typedef enum _stage_id {
    BOMBMAN = 1,
    FIREMAN,
    SPARKMAN,
    MAGNETMAN,
    RINGMAN
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
        const std::string stage_info;

    public:
        explicit StageInfo(const std::string& stage_info);
        char get_id() const;
        std::string get_str() const;
        const std::string& get_info() const;
        ~StageInfo();
};

class Update : public Packet {
    private:
        static const char id = UPDATE;
        const std::string name;
        const std::string update_info;

    public:
        Update(const std::string& name, const std::string& update_info);
        char get_id() const;
        const std::string& get_name() const;
        std::string get_str() const;
        const std::string& get_update_info() const;
        ~Update();
};

class FloatUpdate : public Packet {
    private:
        static const char id = FLOAT_UPDATE;

    protected:
        const std::string name;
        const int object_id;
        const float x;
        const float y;

    public:
        FloatUpdate(const std::string& name, const int object_id,
                    const float x, const float y);
        virtual char get_id() const;
        const std::string& get_name() const;
        int get_object_id() const;
        float get_x() const;
        float get_y() const;
        virtual std::string get_str() const;
        virtual ~FloatUpdate();
};

class EnemyFloatUpdate : public FloatUpdate {
    private:
        static const char id = ENEMY_FLOAT_UPDATE;
        bool covered;

    public:
        EnemyFloatUpdate(const std::string& name, const int object_id,
                    const float x, const float y, bool covered);
        EnemyFloatUpdate(const std::string& name, const int object_id,
                         const float x, const float y, const char pressed);
        char get_id() const;
        char is_covered();
        std::string get_str() const;
        ~EnemyFloatUpdate();
};


class MegaManFloatUpdate : public FloatUpdate {
    private:
        static const char id = MEGAMAN_FLOAT_UPDATE;
        const std::string player_name;
        const float energy;
        const int direction_x;
        const int direction_y;

    public:
        MegaManFloatUpdate(const std::string& name,
                           const std::string& player_name,
                           const int object_id,
                           const float x, const float y,
                           const int direction_x,
                           const int direction_y,
                           const float energy);
        char get_id() const;
        const std::string& get_player_name() const;
        float get_energy() const;
        int get_direction_x() const;
        int get_direction_y() const;
        std::string get_str() const;
        ~MegaManFloatUpdate();
};

class BossFloatUpdate : public FloatUpdate {
    private:
        static const char id = BOSS_FLOAT_UPDATE;
        const float energy;
        const int direction_x;
        const int direction_y;

    public:
        BossFloatUpdate(const std::string& name,
                           const int object_id,
                           const float x, const float y,
                           const int direction_x,
                           const int direction_y,
                           const float energy);
        char get_id() const;
        float get_energy() const;
        int get_direction_x() const;
        int get_direction_y() const;
        std::string get_str() const;
        ~BossFloatUpdate();
};

class Deceased : public Packet {
    private:
        static const char id = DECEASED;
        const int object_id;

    public:
        explicit Deceased(const int object_id);
        char get_id() const;
        std::string get_str() const;
        int get_object_id() const;
        ~Deceased();
};

class ChamberInfo : public Packet {
    private:
        static const char id = CHAMBER_INFO;
        const std::string chamber_info;

    public:
        explicit ChamberInfo(const std::string& chamber_info);
        char get_id() const;
        std::string get_str() const;
        const std::string& get_info() const;
        ~ChamberInfo();
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

    public:
        bool is_empty(const char id);
        Packet* pop(const char id);
        void push(Packet* packet);
        ~ReceivedPacketsProtected();
};

class PacketError : public SystemError {
    public:
        explicit PacketError(const std::string error_msg) throw();
};

#endif  // PACKET_H
