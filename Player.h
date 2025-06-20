#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
#include <string>
// Ema
#include "Proyectil.h"
#include <SFML/System/Clock.hpp>
//****************


class Player : public Entity {
private:
    int _level;
    int _exp;
    float _baseDamage;
    float _defense;
    float pickupRadius;
	float _rangoAtaque;
    void handleInput(float deltaTime);
    // Ema
    std::vector<Proyectil> Proyectiles;  // Lista de proyectiles activos
    sf::Clock _cooldownAtaque;         
    float CDataque = 1.0;     // Tiempo mínimo entre disparos (en segundos)
    //mariano   
    float rangoProyectil = 3;
    float velocidadProyectil = 50.f; 


    //******************************************
    // Mariano - Barra de salud 
    sf::RectangleShape _healthBarBackground;
    sf::RectangleShape _healthBarFill;
    
    //Skills
    bool _autoAim = false;
    /**
    bool _auraDamage;
    int _piercing;
    bool _dash;
    bool _shield;
    bool _recovery;
    */

public:
    Player(float health, float speed, const std::string& texturePath);

    void update(float deltaTime) override;

    // Ema
    sf::Vector2f ultima_direccion;
    std::vector<Proyectil>& getProjectiles(); // Permite acceder a los proyectiles desde fuera
    void updateProjectiles(float dt);                      // Actualiza posición y vida de proyectiles
    //***************************************
    //Mariano - Getters para barra de exp y nivel

    int getLevel() const { return _level; }
    int getExp() const { return _exp; }
    int getExpToNextLevel() const { return _level * 100; } // ejemplo simple
    sf::Clock relojIntervaloDamage;
    float tiempoInmune = 0.5f;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void addExp(int amount);

    bool justLeveledUp();

    void incrementarDanioBase(float extra) { _baseDamage += extra; }
    void incrementarVelocidad(float extra) { _speed += extra; }
    void reducirCooldownDisparo(float cantidad) {
        CDataque = std::max(0.05f, CDataque - cantidad); 
    }
    void aumentarRangoProyectil(float extra) { rangoProyectil += extra; }
    void aumentarVelocidadProyectil(float extra) { velocidadProyectil += extra; }
    void attack(sf::Vector2f position);

    virtual void takeDamage(float damage);

};

#endif