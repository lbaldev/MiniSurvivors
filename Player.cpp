#include "Player.h"
#include <cmath>


Player::Player(float health, float speed, const std::string& texturePath)
    : Entity(health, speed, texturePath), _level(1), _exp(0), _baseDamage(10.0f), _defense(0.1f)
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

    if (direction.x != 0 || direction.y != 0)
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    // Ema
    //***************************************************************
    // Actualiza la dirección si se está moviendo
    if (direction.x != 0 || direction.y != 0)
        ultima_direccion = direction;

    //***************************************************************   
    _position += direction * velocidadProyectil * dt;
    _sprite.setPosition(_position);
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

const std::vector<Proyectil>& Player::getProjectiles() const {
    return Proyectiles;
}

//***************************************************************
