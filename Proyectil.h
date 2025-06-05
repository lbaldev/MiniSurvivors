#pragma once
#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <SFML/Graphics.hpp>

// Clase que representa un proyectil disparado por el jugador
class Proyectil : public sf::Drawable {
private:
    sf::Vector2f _position;     // Posición actual del proyectil
    sf::Vector2f direccionProyectil;    // Dirección normalizada en la que se mueve
    float velocidadProyectil;               // Velocidad de movimiento (pixeles por segundo)
    float _lifetime;            // Tiempo de vida
    sf::CircleShape _shape;     // Representación gráfica del proyectil

public:
    // Constructor del proyectil
    // - position: posición inicial
    // - direccionProyectil: dirección en la que se moverá 
    // - velocidadProyectil: velocidad del proyectil 
    // - lifetime: tiempo de vida en segundos 
    Proyectil(sf::Vector2f position, sf::Vector2f direction, float speed = 500.f, float lifetime = 3.f);

    // Actualiza la posición del proyectil y reduce su tiempo de vida
    void update(float dt);

    // Devuelve la posición actual del proyectil
    sf::Vector2f getPosition() const;

protected:
    // Método para dibujar el proyectil
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
#pragma once
