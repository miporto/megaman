#include "Receiver.h"

Receiver::Receiver(Socket* socket,
                   ReceivedPacketsProtected& packets)
        : socket(socket), packets(packets), started(false), quit(false) {}

void Receiver::start() {
    this->started = true;
    Thread::start();
}

void Receiver::receive_packet(const char id) {
    switch (id) {
        case NEW_PLAYER: {
            int length;
            this->socket->receive((char*)&length, sizeof(int));
            char* name = new char[length + 1];
            name[length] = '\0';
            this->socket->receive(name, sizeof(char) * length);
            this->packets.push(new NewPlayer(name));
            delete name;
            break;
        } case STAGE_PICK: {
            char stage_id;
            this->socket->receive(&stage_id, sizeof(char));
            this->packets.push(new StagePick(stage_id));
            break;
        } case STAGE_INFO: {
            int length;
            this->socket->receive((char *) &length, sizeof(int));
            char *info = new char[length + 1];
            info[length] = '\0';
            this->socket->receive(info, sizeof(char) * length);
            this->packets.push(new StageInfo(info));
            delete info;
            break;
        } case UPDATE: {
            int name_length;
            this->socket->receive((char *) &name_length, sizeof(int));
            char *name = new char[name_length + 1];
            name[name_length] = '\0';
            this->socket->receive(name, sizeof(char) * name_length);
            int length;
            this->socket->receive((char *) &length, sizeof(int));
            char *info = new char[length + 1];
            info[length] = '\0';
            this->socket->receive(info, sizeof(char) * length);
            this->packets.push(new Update(name, info));
            delete info;
            break;
        } case FLOAT_UPDATE: {
            int name_length;
            this->socket->receive((char *) &name_length, sizeof(int));
            char *name = new char[name_length + 1];
            name[name_length] = '\0';
            this->socket->receive(name, sizeof(char) * name_length);
            int object_id;
            this->socket->receive((char *) &object_id, sizeof(int));
            float x, y;
            this->socket->receive((char *) &x, sizeof(float));
            this->socket->receive((char *) &y, sizeof(float));
            this->packets.push(new FloatUpdate(name, object_id, x, y));
            delete name;
            break;
        } case MEGAMAN_FLOAT_UPDATE: {
            int name_length;
            this->socket->receive((char *) &name_length, sizeof(int));
            char *name = new char[name_length + 1];
            name[name_length] = '\0';
            this->socket->receive(name, sizeof(char) * name_length);
            int object_id;
            this->socket->receive((char *) &object_id, sizeof(int));
            float x, y;
            this->socket->receive((char *) &x, sizeof(float));
            this->socket->receive((char *) &y, sizeof(float));

            int player_name_length;
            this->socket->receive((char *) &player_name_length, sizeof(int));
            char *player_name = new char[player_name_length + 1];
            player_name[player_name_length] = '\0';
            this->socket->receive(player_name,
                                  sizeof(char) * player_name_length);
            float energy;
            this->socket->receive((char *) &energy, sizeof(float));
            int direction_x, direction_y;
            this->socket->receive((char *) &direction_x, sizeof(int));
            this->socket->receive((char *) &direction_y, sizeof(int));
            this->packets.push(new MegaManFloatUpdate(name,
                                                      player_name, object_id,
                                                      x, y,
                                                      direction_x, direction_y,
                                                      energy));
            delete name;
            delete player_name;
            break;
        } case BOSS_FLOAT_UPDATE: {
            int name_length;
            this->socket->receive((char *) &name_length, sizeof(int));
            char *name = new char[name_length + 1];
            name[name_length] = '\0';
            this->socket->receive(name, sizeof(char) * name_length);
            int object_id;
            this->socket->receive((char *) &object_id, sizeof(int));
            float x, y;
            this->socket->receive((char *) &x, sizeof(float));
            this->socket->receive((char *) &y, sizeof(float));
            float energy;
            this->socket->receive((char *) &energy, sizeof(float));
            int direction_x, direction_y;
            this->socket->receive((char *) &direction_x, sizeof(int));
            this->socket->receive((char *) &direction_y, sizeof(int));
            this->packets.push(new BossFloatUpdate(name, object_id, x, y,
                                                   direction_x, direction_y,
                                                   energy));
            delete name;
            break;
        } case DECEASED: {
            int object_id;
            this->socket->receive((char *) &object_id, sizeof(int));
            this->packets.push(new Deceased(object_id));
            break;
        } case CHAMBER_INFO: {
            int length;
            this->socket->receive((char *) &length, sizeof(int));
            char *info = new char[length + 1];
            info[length] = '\0';
            this->socket->receive(info, sizeof(char) * length);
            this->packets.push(new ChamberInfo(info));
            delete info;
            break;
        } default:
            // Si el ID es desconocido, es posible que el resto del
            // paquete quede en el pipe del socket, arruinando la comm
            break;
    }
}

void Receiver::run() {
    char packet_id = 0;
    while (!this->quit) {
        try {
            this->socket->receive(&packet_id, sizeof(char));
        }
        catch (const SocketError& e) {
            this->socket->disconnect();
            break;
        }
        this->receive_packet(packet_id);
    }
}

void Receiver::shutdown() {
    this->quit = true;
}

Receiver::~Receiver() {
    this->shutdown();
    if (started) this->join();
}
