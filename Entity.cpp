#include "Entity.h"
#include <vector>
#include <string>




Entity::Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position) // Constructor de la clase Entity
    : _health(health), _speed(speed), _position(position) {

    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(texturePath);

    //_texture.loadFromFile(texturePath);
    _sprite.setTexture(*texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}

Entity::Entity(float health, float speed, const std::string& texturePath) // Constructor de la clase Entity con posición por defecto
    : _health(health), _speed(speed) {

    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(texturePath);
    

	//_texture.loadFromFile(texturePath); 
    _sprite.setTexture(*texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2); // Establece el origen del sprite al centro de su bounding box
}

Entity::~Entity() {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const { // Método para dibujar la entidad en la ventana de renderizado
    target.draw(_sprite, states);
}

sf::Vector2f Entity::getPosition() const { // Método para obtener la posición de la entidad
    return _position;   
}

void Entity::setPosition(sf::Vector2f pos) { // Método para establecer la posición de la entidad
	_position = pos; // Actualiza la posición interna
	_sprite.setPosition(pos); // Actualiza la posición del sprite
}

sf::FloatRect Entity::getGlobalBounds() const {
    return _sprite.getGlobalBounds();
}

void Entity::move(float desplazamientoX, float desplazamientoY)
{
	_prevPosition = _position; // Guarda la posición anterior antes de mover
	_position.x += desplazamientoX;
    _position.y += desplazamientoY;
	_sprite.setPosition(_position); // Actualiza la posición del sprite

}

sf::Vector2f Entity::getPrevPosition() const
{
    return _prevPosition;
}
