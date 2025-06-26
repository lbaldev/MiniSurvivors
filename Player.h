#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
#include <string>
// Ema
#include "Proyectil.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
//****************


class Player : public Entity {
private:
    std::string _name;
    int _level;
    int _exp;
    float _baseDamage;
    float _defense;
    float pickupRadius;
    std::vector<Proyectil> Proyectiles;  // Lista de proyectiles activos
    sf::Clock _cooldownAtaque;         
    float CDataque = 1.0;     
    float _rangoProyectil = 0.5;
    float velocidadProyectil = 300.f; 
    sf::Vector2f ultima_direccion;
    float tiempoInmune = 0.5f;
    sf::RectangleShape _healthBarBackground;
    sf::RectangleShape _healthBarFill;
    sf::Clock relojIntervaloDamage;
    //Skills
    bool _autoAim = true;
    /**
    int _piercing;
    bool _dash;
    bool _shield;
    bool _recovery;
    */
	//****************
    void handleInput(float deltaTime);
    sf::SoundBuffer _levelUpBuffer;
    sf::Sound _levelUpSound;
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
    std::vector<Proyectil>& getProjectiles();
	float getCooldownAtaque() const { return CDataque; }
	float getRangoProyectil() const { return _rangoProyectil; }
	float getVelocidadProyectil() const { return velocidadProyectil; }
	float getTiempoInmune() const { return tiempoInmune; }
    std::string getName() const { return _name; }
    bool isAutoAimEnabled() const { return _autoAim; }
    //Setters
	void setLevel(int level) { _level = level; }
	void setExp(int exp) { _exp = exp; }
	void setBaseDamage(float damage) { _baseDamage = damage; }
	void setDefense(float defense) { _defense = defense; }  
    void setName(const std::string& name) { _name = name; }
	void setPickupRadius(float radius) { pickupRadius = radius; }
    void setCooldownAtaque(float cooldown) { CDataque = cooldown; }
    void setRangoProyectil(float rango) { _rangoProyectil = rango; }
    void setVelocidadProyectil(float velocidad) { velocidadProyectil = velocidad; }
    void setTiempoInmune(float tiempo) { tiempoInmune = tiempo; }
    void setAutoAim(bool autoAim) { _autoAim = autoAim; }
	void setName(std::string& name) { _name = name; }

	//*****************

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void addExp(int amount);

    bool justLeveledUp();
    void incrementarDanioBase(float extra) { _baseDamage += extra; }
    void incrementarVelocidad(float extra) { _speed += extra; }
    void reducirCooldownDisparo(float cantidad) {
        CDataque = std::max(0.05f, CDataque - cantidad); 
    }
    void aumentarRangoProyectil(float extra) { _rangoProyectil += extra; }
    void aumentarVelocidadProyectil(float extra) { velocidadProyectil += extra; }

    void attack(sf::Vector2f position);

    virtual void takeDamage(float damage);


};

#endif