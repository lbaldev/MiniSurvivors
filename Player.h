#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
#include <string>

struct Skill {
    std::string name;
    float damage;
    float cooldown;
    float area;
};

class Player : public Entity {
private:
    int _level;
    int _exp;
    float _baseDamage;
    float _defense;
    std::vector<Skill> _skills;
    void handleInput(float deltaTime);

public:
    Player(float health, float speed, const std::string& texturePath);

    void update(float deltaTime) override;
    void move(sf::Vector2f direction);

    void addSkill(const Skill& skill);
};

#endif
