#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
#include <string>
// Ema
#include "Proyectil.h"
#include <SFML/System/Clock.hpp>
//****************




struct Skill {
    std::string name;
    float damage;
    float cooldown;
    float area;
};

class Player : public Entity {
private:
    int _level;
    int _exp;
    float _baseDamage;
    float _defense;
    void handleInput(float deltaTime);
    // Ema
    std::vector<Proyectil> Proyectiles;  // Lista de proyectiles activos
    sf::Clock _cooldownAtaque;                // Reloj para medir cooldown entre disparos
    const float CDataque = 0.3;     // Tiempo mínimo entre disparos (en segundos)
    //******************************************


public:
    Player(float health, float speed, const std::string& texturePath);

    void update(float deltaTime) override;

    // Ema
    sf::Vector2f ultima_direccion;
    const std::vector<Proyectil>& getProjectiles() const; // Permite acceder a los proyectiles desde fuera
    void updateProjectiles(float dt);                      // Actualiza posición y vida de proyectiles
    //***************************************
};

#endif