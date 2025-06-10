#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Enemy::Enemy(float health, float speed, float damage, const std::string& texturePath, sf::Vector2f startPosition)
    : Entity(health, speed, texturePath, startPosition), _damage(damage) {
}

void Enemy::update(float dt) {
	
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f dir = target - _position;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;
	move(dir.x * _speed * dt, dir.y * _speed * dt); // Mueve el enemigo hacia el objetivo

	//_position += dir * _speed * dt; //  
	//_sprite.setPosition(_position); // Actualiza la posici�n del sprite
}

void Enemy::pushBack(sf::Vector2f dir, float fuerza)
{
    _position += dir * fuerza;
    _sprite.setPosition(_position); 
}
