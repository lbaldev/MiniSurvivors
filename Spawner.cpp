#include "Spawner.h"

Spawner::Spawner()
{

}

Spawner::~Spawner()
{
    //dtor
}
//Se le agrego aumentoDanio y aumentoVelocidad para que los enemigos puedan escalar por tiempo
void Spawner::spawnEnemies(std::vector<Enemy>& enemigos, sf::Vector2f playerPosition, float timer) {
    if (enemigos.size() < MAX_ENEMIES &&
        relojGeneracionEnemigos.getElapsedTime().asSeconds() >= ENEMY_INTERVAL)
    {
        float radius = 700.f;
        float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159265f;
        float x = playerPosition.x + std::cos(angle) * radius;
        float y = playerPosition.y + std::sin(angle) * radius;

        int tipo = std::rand() % 3;  // 0, 1 o 2

        float vida, velocidad, daño;
        std::string sprite;

        switch (tipo) {
        case 0: // Fantasma
            vida = 50.0f * (1 + timer / 60.0f);
            velocidad = 40.0f * (1 + timer / 60.0f);
            daño = 10.0f * (1 + timer / 60.0f);
            sprite = "assets/fantasma.png";
            break;
        case 1: // Araña
            vida = 30.0f * (1 + timer / 90.0f);
            velocidad = 30.0f;
            daño = 15.0f * (1 + timer / 45.0f);
            sprite = "assets/araña.png";
            break;
        case 2: // Bruto
            vida = 100.0f * (1 + timer / 45.0f);
            velocidad = 20.0f;
            daño = 25.0f * (1 + timer / 45.0f);
            sprite = "assets/bruto.png";
            break;
        }

        enemigos.emplace_back(vida, velocidad, daño, sprite, sf::Vector2f(x, y));
        relojGeneracionEnemigos.restart();
    }
}


