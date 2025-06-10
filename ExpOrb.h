#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class ExpOrb : public sf::Drawable {
public:
    ExpOrb(sf::Vector2f position, int amount);

    void update(float dt);
    sf::Vector2f getPosition() const;
    int getAmount() const;
    sf::FloatRect getBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape _shape;
    sf::Vector2f _position;
    int _amount;
};
