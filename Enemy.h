#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
private:
    float _damage;
    int _scoreValue;

public:
    Enemy(float health, float speed, float damage, const std::string& texturePath, sf::Vector2f startPosition, int scoreValue = 10);
    void update(float dt) override;
    void chase(sf::Vector2f target, float dt);

	void colisionesPlayerEnemy(Player& player);
	void colisionesEnemyEnemy(Entity& otro);
    void colisionesEnemyBoss(Entity& boss);

    int getScoreValue() const { return _scoreValue; }
    void setScoreValue(int value) { _scoreValue = value; }

	void setDamage(float damage) { _damage = damage; }
    float getDamage() const { return _damage; }

};

#endif
