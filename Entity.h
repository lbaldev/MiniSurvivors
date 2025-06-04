#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Drawable {
protected:
    float _health;
    float _speed;
	sf::Vector2f _position; // posición de la entidad
	sf::Texture _texture;   // textura de la entidad
	sf::Sprite _sprite;     // sprite que representa la entidad

	sf::Vector2f _prevPosition; // posición anterior de la entidad, útil para detectar cambios de posición

public:
	Entity(float health, float speed, const std::string& texturePath); // Constructor sin posición, se usará la posición por defecto (0, 0)
	Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position); // Constructor con posición
	virtual ~Entity(); // Destructor virtual para permitir la limpieza de recursos en clases derivadas

	virtual void update(float deltaTime) = 0; // Método virtual puro para actualizar la entidad, debe ser implementado por las clases derivadas

	sf::Vector2f getPosition() const; // Método para obtener la posición de la entidad
	void setPosition(sf::Vector2f pos); // Método para establecer la posición de la entidad
	sf::FloatRect getGlobalBounds() const; // Método para obtener los límites globales del sprite de la entidad

	void move(float desplazamientoX, float desplazamientoY); // Método para mover la entidad en el espacio 2D
	sf::Vector2f getPrevPosition() const;



protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Método protegido para dibujar la entidad, se implementa en la clase base
};

#endif
