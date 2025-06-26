#ifndef SPAWNER_H
#define SPAWNER_H

#include "Enemy.h"
#include "Globals.h"

class Spawner
{
public:
    Spawner(); 
    virtual ~Spawner(); 
    void spawnEnemies(std::vector<Enemy>& enemigos, sf::Vector2f _position, float timer);

private:
    sf::Clock relojGeneracionEnemigos;
};

#endif 
