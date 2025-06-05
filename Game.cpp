#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>


#include "Game.h"



Game::Game()
    : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini Survivors"),
    _player(100.0f, 200.0f, "assets/mago.png")
{
    _camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT); 
    _camera.setCenter(_player.getPosition());     

}

void Game::run()
{
    sf::Clock clock;

    while (_window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}


void Game::update(float dt)
{
	_player.update(dt);
	_spawner.spawnEnemies(_enemies, _player.getPosition()); 

	for (auto& enemy : _enemies) 
		enemy.chase(_player.getPosition(), dt); 

	checkCollisions(); 

    _camera.setCenter(_player.getPosition());
    _window.setView(_camera);
}

void Game::render()
{
    _window.clear(); 
	_window.draw(_player); // Dibujar el jugador

    // Ema
    // Dibujar todos los proyectiles activos del jugador
    for (const auto& projectile : _player.getProjectiles()) {
        _window.draw(projectile);
    }
    //**************************************


    for (const auto& enemy : _enemies)
        _window.draw(enemy);

    _window.display();
}


void Game::checkCollisions()
{
    // Constantes para ajustar el comportamiento
    const float EMPUJE_JUGADOR = 2.5f;      // Fuerza con la que el jugador empuja
    const float EMPUJE_ENEMIGO = 1.0f;      // Fuerza con la que se separan los enemigos
    const float DIST_MINIMA = 40.0f;        // Distancia mínima entre enemigos

    // 1. Colisiones Jugador-Enemigo
    for (auto& enemigo : _enemies)
    {
        if (_player.getGlobalBounds().intersects(enemigo.getGlobalBounds()))
        {
            // Calcular dirección del empuje (desde jugador hacia enemigo)
            sf::Vector2f direccion = enemigo.getPosition() - _player.getPosition();
            
            // Normalizar el vector (convertirlo en dirección unitaria)
            float distancia = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
            if (distancia > 0) // Evitar división por cero 
            {
				direccion.x /= distancia;
                direccion.y /= distancia;
                
                // Aplicar el empuje al enemigo
                enemigo.pushBack(direccion, EMPUJE_JUGADOR);
            }
        }
    }
    // 2. Colisiones Enemigo-Enemigo
    for (size_t i = 0; i < _enemies.size(); i++)
    {
        for (size_t j = i + 1; j < _enemies.size(); j++)
        {
            // Obtener posiciones
            sf::Vector2f pos1 = _enemies[i].getPosition(); 
            sf::Vector2f pos2 = _enemies[j].getPosition();

            // Calcular distancia entre enemigos
            sf::Vector2f diff = pos1 - pos2;
            float distancia = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            
            // Si están muy cerca o colisionando
            if (distancia < DIST_MINIMA)
            {
                // Calcular dirección de separación
                sf::Vector2f direccion;
                if (distancia > 0)
                {
                    direccion.x = diff.x / distancia; 
                    direccion.y = diff.y / distancia;
                }
                else // Si están exactamente en el mismo punto
                {
                    direccion.x = 1.0f; 
                    direccion.y = 0.0f;
                }

                // Separar ambos enemigos en direcciones opuestas
                _enemies[i].pushBack(direccion, EMPUJE_ENEMIGO);
                _enemies[j].pushBack(-direccion, EMPUJE_ENEMIGO);
            }
        }
    }
}
