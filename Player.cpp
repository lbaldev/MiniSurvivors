#include "Player.h"
#include "Globals.h"
#include <cmath>



Player::Player(float health, float speed, const std::string& texturePath) 


	: Entity(health, speed, texturePath, sf::Vector2f(0,0)), _level(1), _exp(0), _baseDamage(50.0f), _defense(0.1f), pickupRadius(20.0f), _rangoProyectil(0.7)  // Inicializa el nivel, experiencia, daño base y defensa del jugador
{   
    ultima_direccion = sf::Vector2f(0.f, -1.f); 
    //barra de vida
    _healthBarBackground.setSize(sf::Vector2f(40.f, 6.f));
    _healthBarBackground.setFillColor(sf::Color(70, 70, 70, 200));
    _healthBarBackground.setOutlineThickness(2.f);
    _healthBarBackground.setOutlineColor(sf::Color::Black);

    _healthBarFill.setSize(sf::Vector2f(40.f, 6.f));
    _healthBarFill.setFillColor(sf::Color(255, 50, 50));

    _levelUpBuffer.loadFromFile("assets/levelup.ogg");
    _levelUpSound.setBuffer(_levelUpBuffer);
    _levelUpSound.setVolume(40);
}

void Player::handleInput(float dt) {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction.x += 1.f;

    if (direction.x != 0 || direction.y != 0)
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); 

    if (direction.x != 0 || direction.y != 0) {
        ultima_direccion = direction;
        _sprite.setScale(direction.x > 0 ? 1.f : -1.f, 1.f); 
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
    updateProjectiles(dt);   // Actualizar proyectiles activos

    //barra vida bajo el jugador
    sf::Vector2f spritePos = _sprite.getPosition();
    _healthBarBackground.setPosition(spritePos.x - 20.f, spritePos.y + _sprite.getGlobalBounds().height / 2.f + 5.f);
    _healthBarFill.setPosition(_healthBarBackground.getPosition());

    float vidaRatio = _health / 100.f; // cambiar numero por la salud maxima del jugador
    vidaRatio = std::max(0.f, std::min(vidaRatio, 1.f));

    _healthBarFill.setSize(sf::Vector2f(40.f * vidaRatio, 6.f));

    if (relojIntervaloDamage.getElapsedTime().asSeconds() >= tiempoInmune) {
		_sprite.setColor(sf::Color::White);
    }
}

void Player::attack(sf::Vector2f EnemyPosition) {
    sf::Vector2f direccion = ultima_direccion;

    if (_cooldownAtaque.getElapsedTime().asSeconds() >= CDataque) {
        if (_autoAim) {
            sf::Vector2f delta = EnemyPosition - _position;
            float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            if (distance < _rangoProyectil*velocidadProyectil*2 && distance > 0.01f) {
                direccion = delta / distance;
                ultima_direccion = direccion;
            }
        }

        if (direccion.x != 0.f || direccion.y != 0.f) {
       
            Proyectiles.emplace_back(_position, direccion, velocidadProyectil, _rangoProyectil, _baseDamage);
            _cooldownAtaque.restart();
        }
    }
}

void Player::updateProjectiles(float dt) {
    for (auto& p : Proyectiles)
        p.update(dt);
}

std::vector<Proyectil>& Player::getProjectiles() {
    return Proyectiles;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
    target.draw(_healthBarBackground, states);
    target.draw(_healthBarFill, states);
}

void Player::takeDamage(float damage) {

    if (relojIntervaloDamage.getElapsedTime().asSeconds() >= tiempoInmune) {
         
        _health -= damage;
        relojIntervaloDamage.restart(); 
    }
    else {
		_sprite.setColor(sf::Color::Red); 
    }
    
}

bool _leveledUp = false;

void Player::addExp(int cantidad) {
    _exp += cantidad;
    while (_exp >= getExpToNextLevel()) {
        _exp -= getExpToNextLevel();
        _level++;
        _leveledUp = true;
        _levelUpSound.play(); 
    }
}

bool Player::justLeveledUp() {
    bool result = _leveledUp;
    _leveledUp = false;
    return result;
}