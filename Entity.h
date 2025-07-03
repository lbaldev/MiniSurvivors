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

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 

public:

	Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position); 
	virtual ~Entity(); 

	virtual void update(float deltaTime) = 0; 

	//Getters
	sf::Vector2f getPosition() const { return _position; } 
	sf::FloatRect getGlobalBounds() const { return _sprite.getGlobalBounds(); } 
	sf::Vector2f getPrevPosition() const { return _prevPosition; }
	std::string getTexturePath() const { return _texturePath; }
	float getHealth() const { return _health; } 
	float getSpeed() const { return _speed; } 
	sf::Sprite getSprite() const { return _sprite; } 
	//Setters
	void setPosition(sf::Vector2f pos) { _position = pos; } 
	void setHealth(float health) { _health = health; }
	void setSpeed(float speed) { _speed = speed; }
	void setTexture(const std::string& texturePath); 

	//*********************
	void move(float desplazamientoX, float desplazamientoY); 
	void pushBack(sf::Vector2f dir, float fuerza);
	virtual void takeDamage(float vida);

};

#endif
