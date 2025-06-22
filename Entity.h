#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Drawable {
protected:
    float _health;
    float _speed;
    sf::Vector2f _position;
	std::shared_ptr<sf::Texture> _texture;
    sf::Sprite _sprite;
    sf::Vector2f _prevPosition;
	std::string _texturePath;

public:

	Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position); // Constructor con posici�n
	virtual ~Entity(); // Destructor virtual para permitir la limpieza de recursos en clases derivadas

	virtual void update(float deltaTime) = 0; // M�todo virtual puro para actualizar la entidad, debe ser implementado por las clases derivadas

	//Getters
	sf::Vector2f getPosition() { return _position; } // M�todo para obtener la posici�n de la entidad
	sf::FloatRect getGlobalBounds() { return _sprite.getGlobalBounds(); } // M�todo para obtener los l�mites globales del sprite de la entidad
	sf::Vector2f getPrevPosition() { return _prevPosition; }
	std::string getTexturePath() { return _texturePath; } // M�todo para obtener la ruta de la textura de la entidad
	float getHealth() { return _health; } // M�todo para verificar si la entidad est� viva (salud > 0)

	//Setters
	void setPosition(sf::Vector2f pos) { _position = pos; } // M�todo para establecer la posici�n de la entidad
	void setHealth(float health) { _health = health; }
	void setSpeed(float speed) { _speed = speed; }
	void setTexture(const std::string& texturePath); // M�todo para establecer la textura de la entidad, carga la textura desde el archivo

	//*********************
	void move(float desplazamientoX, float desplazamientoY); // M�todo para mover la entidad en el espacio 2D
	void pushBack(sf::Vector2f dir, float fuerza);
	virtual void takeDamage(float vida);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // M�todo protegido para dibujar la entidad, se implementa en la clase base
};

#endif
