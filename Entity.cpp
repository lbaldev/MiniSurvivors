#include "Entity.h"
#include <vector>
#include <string>
#include <memory>

Entity::Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position)
    : _health(health), _speed(speed), _position(position) {

    _texture = std::make_shared<sf::Texture>();
    _texture->loadFromFile(texturePath);
    _sprite.setTexture(*_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}


Entity::~Entity() {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const { // M�todo para dibujar la entidad en la ventana de renderizado
    target.draw(_sprite, states);
}

sf::Vector2f Entity::getPosition() const { // M�todo para obtener la posici�n de la entidad
    return _position;   
}

void Entity::setPosition(sf::Vector2f pos) { // M�todo para establecer la posici�n de la entidad
	_position = pos; // Actualiza la posici�n interna
	_sprite.setPosition(pos); // Actualiza la posici�n del sprite
}

sf::FloatRect Entity::getGlobalBounds() const {
    return _sprite.getGlobalBounds();
}

void Entity::move(float desplazamientoX, float desplazamientoY)
{
	_prevPosition = _position; // Guarda la posici�n anterior antes de mover
	_position.x += desplazamientoX;
    _position.y += desplazamientoY;
	_sprite.setPosition(_position); // Actualiza la posici�n del sprite

}

sf::Vector2f Entity::getPrevPosition() const
{
    return _prevPosition;
}

float Entity::getHealth() const { 
    return _health;
}

void Entity::receiveDamage(float damage) {
    _health -= damage;
    if (_health < 0) {
        _health = 0; // Evita que la salud sea negativa
    }
}
