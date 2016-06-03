#include <vector>
#include <string>
#include <iostream>
#include <server/model/Player.h>

#include "ServerCommunicator.h"

NameWaiter::NameWaiter(Player* player,
                       ReceivedPacketsProtected& packets_received)
        : player(player), packets_received(packets_received) {
    this->start();
}

void NameWaiter::run() {
    while (this->packets_received.is_empty(NEW_PLAYER)) {}
    NewPlayer* packet = (NewPlayer*)this->packets_received.pop(NEW_PLAYER);
    this->player->set_name(packet->get_name());
    delete packet;
}

NameWaiter::~NameWaiter() { this->join(); }

ServerCommunicator::ServerCommunicator(Player* player, int fd)
    : player(player),
      peer(fd),
      sender(this->peer, this->packets_to_send),
      receiver(this->peer, this->packets_received) {
    this->sender.start();
    this->receiver.start();
}

void ServerCommunicator::send_new_player_notification(const std::string& name) {
    std::cout << "Sending player name: "<< name << std::endl;
    this->packets_to_send.push(new NewPlayer(name));
}

void ServerCommunicator::send_stage_pick(const char stage_id) {
    this->packets_to_send.push(new StagePick(stage_id));
}

void ServerCommunicator::receive_name() {
    NameWaiter waiter(this->player, this->packets_received);
}

const std::string& ServerCommunicator::name() {
    return this->player->get_name();
}

PacketsQueueProtected* ServerCommunicator::get_actions() {
    return this->packets_received.get_actions();
}

void ServerCommunicator::send_stage_info(const std::string& info) {
    this->packets_to_send.push(new Stage(info));
}

void ServerCommunicator::send_tick_info(const std::string& tick_info) {
    this->packets_to_send.push(new Stage(tick_info));
}

void ServerCommunicator::shutdown() {
    this->peer.shutdown();
}

ServerCommunicator::~ServerCommunicator() {
    this->peer.shutdown();
}

StageIdWaiter::StageIdWaiter(ReceivedPacketsProtected& packets_received)
        : packets_received(packets_received) {}

void StageIdWaiter::run() {
    while (this->packets_received.is_empty(STAGE_PICK)) {}
    StagePick* packet = (StagePick*)this->packets_received.pop(STAGE_PICK);
    this->stage_id.set_id(packet->get_stage_id());
    std::cout << "Stage id received: " << packet->get_stage_id() << std::endl;
    delete packet;
}

char StageIdWaiter::get_stage_id() {
    return this->stage_id();
}

StageIdWaiter::~StageIdWaiter() {}

HostCommunicator::HostCommunicator(Player* player, int fd) :
        ServerCommunicator(player, fd),
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

HostCommunicator::~HostCommunicator() {}
