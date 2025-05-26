#include "Game.h"


Game::Game()
    : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini Survivors"),
    _player(100.0f, 200.0f, "assets/mago.png")
{
    //_enemies.emplace_back(50.0f, 20.0f, 1.0f, "assets/mago.png");
}

void Game::run()
{
    sf::Clock clock;

    while (_window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        _spawner.spawnEnemies(_enemies);
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

    for (auto& enemy : _enemies)
        enemy.chase(_player.getPosition(), dt);
}

void Game::render()
{
    _window.clear();
    _window.draw(_player);

    for (const auto& enemy : _enemies)
        _window.draw(enemy);

    _window.display();
}
