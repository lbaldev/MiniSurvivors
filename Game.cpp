#include "Game.h"


Game::Game()
    : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini Survivors"),
    _player(100.0f, 200.0f, "assets/mago.png")
{
    _camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT); // tamaño de la ventana
    _camera.setCenter(_player.getPosition());     // empieza centrado en el jugador

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

    _camera.setCenter(_player.getPosition());
    _window.setView(_camera);
}

void Game::render()
{
    _window.clear();
    _window.draw(_player);

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