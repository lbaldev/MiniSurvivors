#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
private:
    float _damage;

public:
    Enemy(float health, float speed, float damage, const std::string& texturePath, sf::Vector2f startPosition);
    void update(float dt) override;
    void chase(sf::Vector2f target, float dt);

    void pushBack(sf::Vector2f dir, float fuerza);

};

#endif
