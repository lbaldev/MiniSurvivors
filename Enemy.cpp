#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <cmath>


Enemy::Enemy(float health, float speed, float damage, const std::string& texturePath, sf::Vector2f startPosition, int scoreValue)
    : Entity(health, speed, texturePath, startPosition), _damage(damage), _scoreValue(scoreValue) {
}

void Enemy::update(float dt) {
	
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f dir = target - _position;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;
	move(dir.x * _speed * dt, dir.y * _speed * dt); // Mueve el enemigo hacia el objetivo

	//_position += dir * _speed * dt; //  
	//_sprite.setPosition(_position); // Actualiza la posici�n del sprite
}

void Enemy::colisionesPlayerEnemy(Player& player)
{
    const float EMPUJE_JUGADOR = 2.f;  // Fuerza del empuje al jugador

	sf::Vector2f direccion = _position - player.getPosition();

    // Normalizar el vector (convertirlo en dirección unitaria)
    float distancia = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
    if (distancia > 0) // Evitar división por cero 
    {
        direccion.x /= distancia;
        direccion.y /= distancia;
        // Aplicar el empuje al enemigo
        pushBack(direccion, EMPUJE_JUGADOR);
    }
	player.takeDamage(_damage); // El jugador recibe da��o
    
}

void Enemy::colisionesEnemyEnemy(Entity& otro)
{
    {
        const float EMPUJE_ENEMIGO = 1.0f;
        const float DIST_MINIMA = 40.0f;

        sf::Vector2f diff = _position - otro.getPosition();
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        if (dist < DIST_MINIMA)
        {
            sf::Vector2f dir;

            if (dist > 0.f)
            {
                dir = diff / dist; // Normaliza
            }
            else
            {
                dir = sf::Vector2f(1.f, 0.f); // Dirección arbitraria si están en el mismo lugar
            }

            pushBack(dir, EMPUJE_ENEMIGO);
            otro.pushBack(-dir, EMPUJE_ENEMIGO);
        }
    }
        
}
//Boss
void Enemy::colisionesEnemyBoss(Entity& boss) {
    const float EMPUJE_SOLO_ENEMIGO = 3.0f;
    const float DIST_MINIMA = 140.0f; 

    sf::Vector2f diff = _position - boss.getPosition();
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    if (dist < DIST_MINIMA && dist > 0.f) {
        sf::Vector2f dir = diff / dist;
        pushBack(dir, EMPUJE_SOLO_ENEMIGO); // solo empuja al enemigo
    }
}

