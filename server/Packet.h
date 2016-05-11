#ifndef PACKET_H
#define PACKET_H

#include <queue>
#include <string>
#include <sstream>
#include <string>
#include <vector>

#include "common/Thread.h"

class Packet {
   private:
    const char id;
    std::string str;

   public:
    explicit Packet(char id);
    char get_id() const;
    virtual std::string get_str() const;
    virtual ~Packet();
};

class StagePick : public Packet {
   private:
    const char stage_id;
    std::string str;

   public:
    StagePick(char id, char stage_id);
    char get_stage_id() const;
    std::string get_str() const;
    ~StagePick();
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
