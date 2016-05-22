#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <string>
#include <map>

/*
 * Contiene toda la informacion general del juego,
 * en el server se crea leyendo el .JSON
 * en el client se crea interpretando los paquetes de
 * informacion recibidos del server.
 */

class GameInfo {
    private:
        int initial_lives;
        int respawn_time;
        int cannon_ammo_max;
        std::map<std::string, int> velocities;
        std::map<std::string, int> initial_energy;
        std::map<std::string, int> damage;

    public:
    GameInfo(int initial_lives,
             int respawn_time,
             int cannon_ammo_max,
            //Todas las velocidades; MegaMan, Enemies, Ammos
             std::map<std::string, int> velocities,
            //Energias de MegaMan (esta sera la EnergyTank::max) y Enemies
             std::map<std::string, int> initial_energy,
             std::map<std::string, int> damage);
    //getters hasta morir
    ~GameInfo();
};


#endif //GAMEINFO_H
