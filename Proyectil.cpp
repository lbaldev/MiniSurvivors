#include "Proyectil.h"
#include <cmath>

// Constructor del proyectil
Proyectil::Proyectil(sf::Vector2f position, sf::Vector2f direction, float speed, float lifetime)
    : _position(position), direccionProyectil(direction), velocidadProyectil(speed), _lifetime(lifetime)
{
    // Si la dirección no es cero, la normalizamos
    if (direccionProyectil.x != 0 || direccionProyectil.y != 0) {
        float length = std::sqrt(direccionProyectil.x * direccionProyectil.x + direccionProyectil.y * direccionProyectil.y);
        direccionProyectil /= length; // normalización
    }

    // Configuramos la forma visual del proyectil
    _shape.setRadius(5.f); // Radio del círculo (tamaño)
    _shape.setFillColor(sf::Color::Yellow); // Color del proyectil
    _shape.setOrigin(5.f, 5.f); // Lo centramos (el origen será el centro)
    _shape.setPosition(_position); // Lo colocamos en la posición inicial
}

// Método de actualización por frame
void Proyectil::update(float dt) {
    // Movemos el proyectil en la dirección con la velocidad establecida
    _position += direccionProyectil * velocidadProyectil * dt;

    // Actualizamos la posición visual del sprite
    _shape.setPosition(_position);

    // Reducimos el tiempo de vida restante
    _lifetime -= dt;
}

// Devuelve la posición actual del proyectil
sf::Vector2f Proyectil::getPosition() const {
    return _position;
}

// Dibuja el proyectil en pantalla
void Proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_shape, states);
}
