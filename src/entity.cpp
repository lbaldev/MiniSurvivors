#include "Entity.h"

Entity::Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position)
    : _health(health), _speed(speed), _position(position) {
    _texture.loadFromFile(texturePath);
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}

Entity::Entity(float health, float speed, const std::string& texturePath)
    : _health(health), _speed(speed) {
    _texture.loadFromFile(texturePath);
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}

Entity::~Entity() {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

sf::Vector2f Entity::getPosition() const {
    return _position;
}

void Entity::setPosition(sf::Vector2f pos) {
    _position = pos;
    _sprite.setPosition(pos);
}
