#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float health, float speed, float damage, const std::string& texturePath, sf::Vector2f startPosition)
    : Entity(health, speed, texturePath, startPosition), _damage(damage) {}

void Enemy::update(float dt) {
    // Placeholder; actual logic will go in chase()
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f dir = target - _position;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;
    _position += dir * _speed * dt;
    _sprite.setPosition(_position);
}
