#include "ExpOrb.h"

ExpOrb::ExpOrb(sf::Vector2f position, int amount) 
    : _position(position), _amount(amount)
{
    _shape.setRadius(5.0f);
    _shape.setFillColor(sf::Color::Yellow);
    _shape.setOrigin(_shape.getRadius(), _shape.getRadius());
    _shape.setPosition(_position);
}

sf::Vector2f ExpOrb::getPosition() const {
    return _position;
}

int ExpOrb::getAmount() const {
    return _amount;
}

sf::FloatRect ExpOrb::getBounds() const {
    return _shape.getGlobalBounds();
}

void ExpOrb::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_shape, states);
}
