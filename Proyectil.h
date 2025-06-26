#pragma once
#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <SFML/Graphics.hpp>

class Proyectil : public sf::Drawable {
private:
    sf::Vector2f _position;     
    sf::Vector2f direccionProyectil;   
    float velocidadProyectil;   
    float _lifetime;    

    sf::Sprite _sprite;
    static sf::Texture _texture;
    float _rangoProyectil;   
    float _damage; 


public:
    
    Proyectil(sf::Vector2f position, sf::Vector2f direction, float speed, float lifetime, float damage);

    float getDamage() const { return _damage; };
    void update(float dt);
    sf::Vector2f getPosition() const;
    float getLifetime() const;


protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
#pragma once
