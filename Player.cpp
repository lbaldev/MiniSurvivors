#include "Player.h"
#include "Globals.h"
#include <cmath>



Player::Player(float health, float speed, const std::string& texturePath) // El constructor inicializa al jugador con salud, velocidad y textura
	: Entity(health, speed, texturePath, sf::Vector2f(0,0)), _level(1), _exp(0), _baseDamage(10.0f), _defense(0.1f), pickupRadius(20.0f), _rangoAtaque(300.f)  // Inicializa el nivel, experiencia, daño base y defensa del jugador
{   
    // Ema
    ultima_direccion = sf::Vector2f(0.f, -1.f); // Dirección inicial hacia arriba
    //***************************************************************
    //Mariano barra de vida
    _healthBarBackground.setSize(sf::Vector2f(40.f, 6.f));
    _healthBarBackground.setFillColor(sf::Color(50, 50, 50));

    _healthBarFill.setSize(sf::Vector2f(40.f, 6.f)); // llena al inicio
    _healthBarFill.setFillColor(sf::Color::Red);
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
    //Para testear el incremento de experincia
    //if (direction.x != 0 || direction.y != 0) {
    //    addExp(1);
    //}
}
 
void Player::update(float dt) {
    handleInput(dt);         // Movimiento del jugador
    // Ema
    updateProjectiles(dt);   // Actualizar proyectiles activos

    // Disparo automático si pasó el cooldown
    // Posicionarla debajo del sprite
    sf::Vector2f spritePos = _sprite.getPosition();
    _healthBarBackground.setPosition(spritePos.x - 20.f, spritePos.y + _sprite.getGlobalBounds().height / 2.f + 5.f);
    _healthBarFill.setPosition(_healthBarBackground.getPosition());

    // Escalar el tamaño según la salud actual
    float vidaRatio = _health / 100.f; // suponiendo 100 es la salud máxima
    vidaRatio = std::max(0.f, std::min(vidaRatio, 1.f));

    _healthBarFill.setSize(sf::Vector2f(40.f * vidaRatio, 6.f));
}

void Player::attack(sf::Vector2f EnemyPosition) {
    sf::Vector2f direccion = ultima_direccion;

    if (_cooldownAtaque.getElapsedTime().asSeconds() >= CDataque) {
        if (_autoAim) {
            sf::Vector2f delta = EnemyPosition - _position;
            float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            if (distance < _rangoAtaque && distance > 0.01f) {
                direccion = delta / distance;
                ultima_direccion = direccion;
            }
        }

        if (direccion.x != 0.f || direccion.y != 0.f) {
            Proyectiles.emplace_back(_position, direccion, velocidadProyectil, rangoProyectil);
            _cooldownAtaque.restart();
        }
    }
}





// Ema
void Player::updateProjectiles(float dt) {
    // Actualizamos cada proyectil
    for (auto& p : Proyectiles)
        p.update(dt);

}

std::vector<Proyectil>& Player::getProjectiles() {
    return Proyectiles;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dibujar sprite del jugador
    target.draw(_sprite, states);

    // Dibujar la barra de salud
    target.draw(_healthBarBackground, states);
    target.draw(_healthBarFill, states);
}

void Player::takeDamage(float damage) {

    if (relojIntervaloDamage.getElapsedTime().asSeconds() >= tiempoInmune) {
         
        _health -= damage;
        relojIntervaloDamage.restart(); // Reinicia el reloj para el pr��ximo ataque
    }
    
}

bool _leveledUp = false;

void Player::addExp(int cantidad) {
    _exp += cantidad;
    while (_exp >= getExpToNextLevel()) {
        _exp -= getExpToNextLevel();
        _level++;
        _leveledUp = true;
    }
}

bool Player::justLeveledUp() {
    bool result = _leveledUp;
    _leveledUp = false;
    return result;
}
