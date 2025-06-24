#ifndef SPAWNER_H
#define SPAWNER_H

#include "Enemy.h"
#include "Globals.h"

class Spawner
{
public:
    Spawner(); 
    virtual ~Spawner(); 
	//Se le agregó aumentoDanio y aumentoVelocidad para que los enemigos puedan escalar por tiempo

    void spawnEnemies(std::vector<Enemy>& enemigos, sf::Vector2f _position, float timer);

private:
    sf::Clock relojGeneracionEnemigos;
};

#endif // SPAWNER_H
