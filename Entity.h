#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Drawable {
protected:
    float _health;
    float _speed;
	sf::Vector2f _position; // posici�n de la entidad
	sf::Texture _texture;   // textura de la entidad
	sf::Sprite _sprite;     // sprite que representa la entidad

	sf::Vector2f _prevPosition; // posici�n anterior de la entidad, �til para detectar cambios de posici�n

public:
	Entity(float health, float speed, const std::string& texturePath); // Constructor sin posici�n, se usar� la posici�n por defecto (0, 0)
	Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position); // Constructor con posici�n
	virtual ~Entity(); // Destructor virtual para permitir la limpieza de recursos en clases derivadas

	virtual void update(float deltaTime) = 0; // M�todo virtual puro para actualizar la entidad, debe ser implementado por las clases derivadas

	sf::Vector2f getPosition() const; // M�todo para obtener la posici�n de la entidad
	void setPosition(sf::Vector2f pos); // M�todo para establecer la posici�n de la entidad
	sf::FloatRect getGlobalBounds() const; // M�todo para obtener los l�mites globales del sprite de la entidad

	void move(float desplazamientoX, float desplazamientoY); // M�todo para mover la entidad en el espacio 2D
	sf::Vector2f getPrevPosition() const;



protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // M�todo protegido para dibujar la entidad, se implementa en la clase base
};

#endif
