#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>


#include "Game.h"



Game::Game(sf::RenderWindow& window)
    : _window(window),dt(0),
    _player(100.0f, 200.0f, "assets/mago.png")
{
    _backgroundTexture.loadFromFile("assets/fondo.png");
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setOrigin(
        _backgroundTexture.getSize().x / 2.f,
        _backgroundTexture.getSize().y / 2.f
    );
    _backgroundSprite.setPosition(0.f, 0.f); // posición del centro del mapa
}

void Game::run()
{
    sf::Clock clock;

    //_camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //_camera.setCenter(_player.getPosition());


    while (_window.isOpen())
    {
        dt = clock.restart().asSeconds();
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
    if (_player.getHealth() <= 0) {
        std::cout << "Game Over!" << std::endl;
        _window.close();
		//Aca faltan cosas como mostrar un mensaje de Game Over, reiniciar el juego, etc.
    }
	_player.update(dt);
	_spawner.spawnEnemies(_enemies, _player.getPosition()); 

    
    for (auto& enemy : _enemies) {
        enemy.chase(_player.getPosition(), dt);
    }
	
    checkHitpoints();
	checkCollisions(); 

    // Deseamos que el centro de la cámara esté dentro del mapa
    sf::Vector2f center = _player.getPosition();

    float halfW = _camera.getSize().x / 2.f;
    float halfH = _camera.getSize().y / 2.f;

    float minX = MAP_MIN_X + halfW;
    float maxX = MAP_MAX_X - halfW;
    float minY = MAP_MIN_Y + halfH;
    float maxY = MAP_MAX_Y - halfH;

    center.x = std::max(minX, std::min(center.x, maxX));
    center.y = std::max(minY, std::min(center.y, maxY));

    _camera.setCenter(center);
    _window.setView(_camera);



}

void Game::render()
{
    _window.clear(); 
    _window.draw(_backgroundSprite);
	_window.draw(_player); // Dibujar el jugador

    // Ema
    // Dibujar todos los proyectiles activos del jugador
    for (const auto& projectile : _player.getProjectiles()) {
        _window.draw(projectile);
    }
    //**************************************

    for (const auto& enemy : _enemies)
        _window.draw(enemy);

    for (const auto& orb : _expOrbs)
        _window.draw(orb);

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

void Game::checkHitpoints() {

    for (auto it = _enemies.begin(); it != _enemies.end(); ) {
        if (it->getHealth() <= 0) {
            _expOrbs.emplace_back(it->getPosition(), 10);
            it = _enemies.erase(it); 
        }
        else {
            it->chase(_player.getPosition(), dt);
            ++it;
        }
    }

}