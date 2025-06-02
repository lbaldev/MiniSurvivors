#include "Player.h"
#include <cmath>


Player::Player(float health, float speed, const std::string& texturePath) // El constructor inicializa al jugador con salud, velocidad y textura
	: Entity(health, speed, texturePath), _level(1), _exp(0), _baseDamage(10.0f), _defense(0.1f) { // Inicializa el nivel, experiencia, daño base y defensa del jugador
}

void Player::handleInput(float dt) {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.f;
    
	if (direction.x != 0 || direction.y != 0) // Verifica si hay movimiento
		direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normaliza la dirección para que el jugador se mueva a una velocidad constante
    move(direction.x * _speed * dt, direction.y * _speed * dt);
    //_position += direction * _speed * dt;
    //_sprite.setPosition(_position);
}

void Player::update(float dt) {
    handleInput(dt);
}
