#include "Spawner.h"

Spawner::Spawner()
{

}

Spawner::~Spawner()
{
    //dtor
}

void Spawner::spawnEnemies(std::vector<Enemy>& enemigos){

    if (enemigos.size() < MAX_ENEMIES &&
                relojGeneracionEnemigos.getElapsedTime().asSeconds() >= ENEMY_INTERVAL)
        {

            // Posici�n aleatoria en los bordes de la pantalla
            float x, y;
            if (std::rand() % 2 == 0)    // Aparecer en los laterales (izq/der)
            {
                x = (std::rand() % 2 == 0) ? 0.f : WINDOW_WIDTH;
                y = std::rand() % WINDOW_HEIGHT;
            }
            else                         // Aparecer en la parte superior/inferior
            {
                x = std::rand() % WINDOW_WIDTH;
                y = (std::rand() % 2 == 0) ? 0.f : WINDOW_HEIGHT;
            }
            enemigos.emplace_back(50.0f, 20.0f, 1.0f, "assets/mago.png", sf::Vector2f(x, y));
            //enemigos.emplace_back(sf::Vector2f(x, y));  // A�ade el nuevo enemigo
            relojGeneracionEnemigos.restart();          // Reinicia el reloj
        }
}
