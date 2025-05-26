#ifndef SPAWNER_H
#define SPAWNER_H

#include "Enemy.h"
#include "Globals.h"

class Spawner
{
public:
    Spawner();
    virtual ~Spawner();
    void spawnEnemies(std::vector<Enemy>& enemigos);

private:
    sf::Clock relojGeneracionEnemigos;
};

#endif // SPAWNER_H
