#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>


#include "Game.h"



Game::Game(sf::RenderWindow& window)
    : _window(window),
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

    _window.display();
}


void Game::checkCollisions()
{
    // 1. Colisiones Jugador-Enemigo
    for (auto& enemy : _enemies)
    {
        if (_player.getGlobalBounds().intersects(enemy.getGlobalBounds()))
        {
            // Calcular dirección del empuje (desde jugador hacia enemigo)
            enemy.colisionesPlayerEnemy(_player);
        }
    }
    // 2. Colisiones Enemigo-Enemigo
    for (size_t i = 0; i < _enemies.size(); i++)
    {
        for (size_t j = i + 1; j < _enemies.size(); j++)
        {
            _enemies[i].colisionesEnemyEnemy(_enemies[j]);
        }
    }
}
