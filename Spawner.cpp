#include "Spawner.h"

Spawner::Spawner()
{

}

Spawner::~Spawner()
{
    //dtor
}

void Spawner::spawnEnemies(std::vector<Enemy>& enemigos, sf::Vector2f playerPosition) {
    if (enemigos.size() < MAX_ENEMIES &&
        relojGeneracionEnemigos.getElapsedTime().asSeconds() >= ENEMY_INTERVAL) 
    {
        float radius = 700.f;  // Distancia a la que aparecen los enemigos desde el jugador

        // Ángulo aleatorio en radianes
        float angle = (float)(std::rand()) / RAND_MAX * 2 * 3.14159265f;

        float x = playerPosition.x + std::cos(angle) * radius;
        float y = playerPosition.y + std::sin(angle) * radius;

		enemigos.emplace_back(50.0f, 40.0f, 1.0f, "assets/fantasma.png", sf::Vector2f(x, y)); // Crear un nuevo enemigo en una posición aleatoria alrededor del jugador
        relojGeneracionEnemigos.restart();
    }
}

