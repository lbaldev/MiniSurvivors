#include "Player.h"
#include "Globals.h"
#include <cmath>



Player::Player(float health, float speed, const std::string& texturePath) // El constructor inicializa al jugador con salud, velocidad y textura
	: Entity(health, speed, texturePath, sf::Vector2f(0,0)), _level(1), _exp(0), _baseDamage(10.0f), _defense(0.1f)  // Inicializa el nivel, experiencia, daño base y defensa del jugador
{
    // Ema
    ultima_direccion = sf::Vector2f(0.f, -1.f); // Dirección inicial hacia arriba
    //***************************************************************
}

void Player::handleInput(float dt) {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1.f;
    
	if (direction.x != 0 || direction.y != 0) // Verifica si hay movimiento
		direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normaliza la dirección para que el jugador se mueva a una velocidad constante
  
    if (direction.x != 0 || direction.y != 0) {
        ultima_direccion = direction;
		_sprite.setScale(direction.x > 0 ? 1.f : -1.f, 1.f); // Cambia la dirección del sprite según la dirección del movimiento
    }
    
    //_position += direction * _speed * dt;
    //_sprite.setPosition(_position);


// Nueva posición tentativa
    sf::Vector2f newPos = _position + direction * _speed * dt;
    

    // Límites del mundo
    const float minX = MAP_MIN_X, maxX = MAP_MAX_X;
	const float minY = MAP_MIN_Y, maxY = MAP_MAX_Y;

    if (newPos.x >= minX && newPos.x <= maxX && newPos.y >= minY && newPos.y <= maxY) {
        move(direction.x * _speed * dt, direction.y * _speed * dt);
    }
    
}
 
void Player::update(float dt) {
    handleInput(dt);         // Movimiento del jugador
    // Ema
    updateProjectiles(dt);   // Actualizar proyectiles activos

    // Disparo automático si pasó el cooldown
    if (_cooldownAtaque.getElapsedTime().asSeconds() >= CDataque) {
        if (ultima_direccion.x != 0 || ultima_direccion.y != 0) {
            Proyectiles.emplace_back(_position, ultima_direccion);
            _cooldownAtaque.restart();
        }
    }

}
// ******************************


// Ema
void Player::updateProjectiles(float dt) {
    // Actualizamos cada proyectil
    for (auto& p : Proyectiles)
        p.update(dt);

}

std::vector<Proyectil>& Player::getProjectiles() {
    return Proyectiles;
}

//***************************************************************
