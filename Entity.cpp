#include "Entity.h"
#include <vector>
#include <string>
#include <memory>

Entity::Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position)
    : _health(health), _speed(speed), _position(position), _texturePath(texturePath) {

    _texture = std::make_shared<sf::Texture>();
    _texture->loadFromFile(texturePath);
    _sprite.setTexture(*_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}


Entity::~Entity() {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const { 
    target.draw(_sprite, states);
}

void Entity::move(float desplazamientoX, float desplazamientoY)
{
	_prevPosition = _position; 
	_position.x += desplazamientoX;
    _position.y += desplazamientoY;
	_sprite.setPosition(_position); 

}

void Entity::pushBack(sf::Vector2f dir, float fuerza)
{
    _position += dir * fuerza;
    _sprite.setPosition(_position);
}

void Entity::takeDamage(float cantidad)
{
    _health -= cantidad;
}

void Entity::setTexture(const std::string& texturePath) {
    _texture = std::make_shared<sf::Texture>();
    if (_texture->loadFromFile(texturePath)) {
        _texturePath = texturePath;
        _sprite.setTexture(*_texture);
    }
}