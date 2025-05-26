#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Drawable {
protected:
    float _health;
    float _speed;
    sf::Vector2f _position;
    sf::Texture _texture;
    sf::Sprite _sprite;

public:
    Entity(float health, float speed, const std::string& texturePath);
    Entity(float health, float speed, const std::string& texturePath, sf::Vector2f position);
    virtual ~Entity();

    virtual void update(float deltaTime) = 0;

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
