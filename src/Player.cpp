#include "Player.h"
#include <cmath>


Player::Player(float health, float speed, const std::string& texturePath)
    : Entity(health, speed, texturePath), _level(1), _exp(0), _baseDamage(10.0f), _defense(0.1f) {}

void Player::handleInput(float dt) {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.f;

    if (direction.x != 0 || direction.y != 0)
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);

    _position += direction * _speed * dt;
    _sprite.setPosition(_position);
}

void Player::update(float dt) {
    handleInput(dt);
}

void Player::move(sf::Vector2f direction) {
    _position += direction * _speed;
    _sprite.setPosition(_position);
}

void Player::addSkill(const Skill& skill) {
    _skills.push_back(skill);
}
