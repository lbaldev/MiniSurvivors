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
    
    // Ema
    std::vector<Proyectil> Proyectiles;  // Lista de proyectiles activos
    sf::Clock _cooldownAtaque;         
    float CDataque = 1.0;     // Tiempo mínimo entre disparos (en segundos)
    //mariano   
    float rangoProyectil = 3;
    float velocidadProyectil = 300.f; 
    sf::Vector2f ultima_direccion;
    float tiempoInmune = 0.5f;
    sf::RectangleShape _healthBarBackground;
    sf::RectangleShape _healthBarFill;
    sf::Clock relojIntervaloDamage;
    //Skills
    bool _autoAim = true;
    /**
    bool _auraDamage;
    int _piercing;
    bool _dash;
    bool _shield;
    bool _recovery;
    */
	//****************
    void handleInput(float deltaTime);
public:
    Player(float health, float speed, const std::string& texturePath);

    void update(float deltaTime) override;

    // Ema
    
     // Permite acceder a los proyectiles desde fuera
    void updateProjectiles(float dt);                      // Actualiza posición y vida de proyectiles
    //***************************************
    //Getters

    int getLevel() const { return _level; }
    int getExp() const { return _exp; }
    int getExpToNextLevel() const { return _level * 100; } // ejemplo simple
	float getBaseDamage() const { return _baseDamage; }
	float getDefense() const { return _defense; }
	float getPickupRadius() const { return pickupRadius; }
	float getRangoAtaque() const { return _rangoAtaque; }
    std::vector<Proyectil>& getProjectiles();
	float getCooldownAtaque() const { return CDataque; }
	float getRangoProyectil() const { return rangoProyectil; }
	float getVelocidadProyectil() const { return velocidadProyectil; }
	float getTiempoInmune() const { return tiempoInmune; }
    bool isAutoAimEnabled() const { return _autoAim; }

    //Setters
	void setLevel(int level) { _level = level; }
	void setExp(int exp) { _exp = exp; }
	void setBaseDamage(float damage) { _baseDamage = damage; }
	void setDefense(float defense) { _defense = defense; }
	void setPickupRadius(float radius) { pickupRadius = radius; }
    void setRangoAtaque(float rango) { _rangoAtaque = rango; }
    void setCooldownAtaque(float cooldown) { CDataque = cooldown; }
    void setRangoProyectil(float rango) { rangoProyectil = rango; }
    void setVelocidadProyectil(float velocidad) { velocidadProyectil = velocidad; }
    void setTiempoInmune(float tiempo) { tiempoInmune = tiempo; }
	//*****************

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void addExp(int amount);

    bool justLeveledUp();
    void toggleAutoAim() { _autoAim = !_autoAim; }
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