#include "Proyectil.h"
#include <cmath>

sf::Texture Proyectil::_texture;

// Constructor del proyectil
Proyectil::Proyectil(sf::Vector2f position, sf::Vector2f direction, float speed, float lifetime, float damage)
    : _position(position), direccionProyectil(direction), velocidadProyectil(speed),
    _rangoProyectil(lifetime), _damage(damage)
{
    // Si la dirección no es cero, la normalizamos
    if (direccionProyectil.x != 0 || direccionProyectil.y != 0) {
        float length = std::sqrt(direccionProyectil.x * direccionProyectil.x + direccionProyectil.y * direccionProyectil.y);
        direccionProyectil /= length; // normalización
    }
    _texture.loadFromFile("assets/proyectil.png");
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
    _sprite.setOrigin(_texture.getSize().x / 2.f, _texture.getSize().y / 2.f);
    _sprite.setScale(0.025f, 0.025f);
}

// Método de actualización por frame
void Proyectil::update(float dt) {
    // Movemos el proyectil en la dirección con la velocidad establecida
    _position += direccionProyectil * velocidadProyectil * dt;

    // Actualizamos la posición visual del sprite
    _sprite.setPosition(_position);

    // Reducimos el tiempo de vida restante
    _rangoProyectil -= dt;
}

sf::Vector2f Proyectil::getPosition() const {
    return _position;
}

 float Proyectil::getLifetime() const {
     return _rangoProyectil;
}

// Dibuja el proyectil en pantalla
void Proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}
