#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float health, float speed, float damage, const std::string& texturePath, sf::Vector2f startPosition)
    : Entity(health, speed, texturePath, startPosition), _damage(damage) {
}

void Enemy::update(float dt) {
	// Placeholder; actual logic will go in chase() // espa�ol // L�gica de actualizaci�n del enemigo
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f dir = target - _position;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;

	move(dir.x * _speed * dt, dir.y * _speed * dt); // Mueve el enemigo hacia el objetivo

	//_position += dir * _speed * dt; //  
	//_sprite.setPosition(_position); // Actualiza la posici�n del sprite
}
void Enemy::quieto(float x, float y) {
	_speed = 0; // Detiene el enemigo
	_position.x = x; // Actualiza la posici�n del sprite
	_position.y = y; // Actualiza la posici�n del sprite
	_sprite.setPosition(_position); // Actualiza la posici�n del sprite
}


