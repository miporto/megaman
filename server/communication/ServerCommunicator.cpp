#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

#include "server/Logger.h"
#include "server/model/Player.h"
#include "ServerCommunicator.h"

#define WAIT_TIME_MICROSECONDS 10000

NameWaiter::NameWaiter(Player& player,
                       ReceivedPacketsProtected& packets_received)
        : player(player), packets_received(packets_received) {
    this->start();
}

void NameWaiter::run() {
    while (this->packets_received.is_empty(NEW_PLAYER))
        usleep(WAIT_TIME_MICROSECONDS);
    NewPlayer* packet = (NewPlayer*)this->packets_received.pop(NEW_PLAYER);
    this->player.set_name(packet->get_name());
    delete packet;
}

NameWaiter::~NameWaiter() { this->join(); }

ServerCommunicator::ServerCommunicator(Socket* peer)
    : peer(peer),
      sender(this->peer, this->packets_to_send),
      receiver(this->peer, this->packets_received) {
    this->sender.start();
    this->receiver.start();
}

void ServerCommunicator::send_new_player_notification(const std::string& name) {
    Logger::instance()->out << INFO << "Sending player name: " << name;
    this->packets_to_send.push(new NewPlayer(name));
}

void ServerCommunicator::send_stage_pick(const char stage_id) {
    this->packets_to_send.push(new StagePick(stage_id));
}

void ServerCommunicator::receive_name() {
    NameWaiter waiter(this->player, this->packets_received);
}

const std::string& ServerCommunicator::name() {
    return this->player.get_name();
}

Player* ServerCommunicator::get_player() {
    return &this->player;
}

PacketsQueueProtected* ServerCommunicator::get_actions() {
    return this->packets_received.get_actions();
}

void ServerCommunicator::send_stage_info(const std::string& info) {
    this->packets_to_send.push(new StageInfo(info));
}

void ServerCommunicator::send_tick_info(const std::string& tick_info) {
    this->packets_to_send.push(new StageInfo(tick_info));
}

void ServerCommunicator::send_boss_chamber_info(const char boss_id) {
    this->packets_to_send.push(new ChamberInfo(boss_id));
}

void ServerCommunicator::shutdown() {
    this->peer->shutdown();
}

ServerCommunicator::~ServerCommunicator() {
    this->peer->shutdown();
    delete this->peer;
}

StageIDProtected::StageIDProtected() : stage_id(0) {}

void StageIDProtected::set_id(char stage_id) {
    Lock l(this->m);
    this->stage_id = stage_id;
}

char StageIDProtected::operator()() {
    Lock l(this->m);
    return this->stage_id;
}

StageIDProtected::~StageIDProtected() {}

StageIdWaiter::StageIdWaiter(ReceivedPacketsProtected& packets_received)
        : packets_received(packets_received) {}

void StageIdWaiter::run() {
    while (this->packets_received.is_empty(STAGE_PICK))
        usleep(WAIT_TIME_MICROSECONDS);
    StagePick* packet = (StagePick*)this->packets_received.pop(STAGE_PICK);
    this->stage_id.set_id(packet->get_stage_id());
    delete packet;
}

char StageIdWaiter::get_stage_id() {
    return this->stage_id();
}

void StageIdWaiter::reset_stage_id() {
    this->stage_id.set_id(0);
}

StageIdWaiter::~StageIdWaiter() {}

HostCommunicator::HostCommunicator(Socket* peer) :
        ServerCommunicator(peer),
        waiter(this->packets_received) {
    this->waiter.start();
}

char HostCommunicator::check_stage_id() {
    return this->waiter.get_stage_id();
}

char HostCommunicator::receive_stage_id() {
    this->waiter.join();
    return this->waiter.get_stage_id();
}

void HostCommunicator::reset_stage_id() {
    this->waiter.reset_stage_id();
    this->waiter.start();
}

HostCommunicator::~HostCommunicator() {}
