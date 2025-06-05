#include "Proyectil.h"
#include <cmath>

// Constructor del proyectil
Proyectil::Proyectil(sf::Vector2f position, sf::Vector2f direction, float speed, float lifetime)
    : _position(position), direccionProyectil(direction), velocidadProyectil(speed), _lifetime(lifetime)
{
    // Si la direcci�n no es cero, la normalizamos
    if (direccionProyectil.x != 0 || direccionProyectil.y != 0) {
        float length = std::sqrt(direccionProyectil.x * direccionProyectil.x + direccionProyectil.y * direccionProyectil.y);
        direccionProyectil /= length; // normalizaci�n
    }

    // Configuramos la forma visual del proyectil
    _shape.setRadius(5.f); // Radio del c�rculo (tama�o)
    _shape.setFillColor(sf::Color::Yellow); // Color del proyectil
    _shape.setOrigin(5.f, 5.f); // Lo centramos (el origen ser� el centro)
    _shape.setPosition(_position); // Lo colocamos en la posici�n inicial
}

// M�todo de actualizaci�n por frame
void Proyectil::update(float dt) {
    // Movemos el proyectil en la direcci�n con la velocidad establecida
    _position += direccionProyectil * velocidadProyectil * dt;

    // Actualizamos la posici�n visual del sprite
    _shape.setPosition(_position);

    // Reducimos el tiempo de vida restante
    _lifetime -= dt;
}

// Devuelve la posici�n actual del proyectil
sf::Vector2f Proyectil::getPosition() const {
    return _position;
}

// Dibuja el proyectil en pantalla
void Proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_shape, states);
}
