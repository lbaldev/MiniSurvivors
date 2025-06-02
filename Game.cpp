#include "Game.h"
#include <iostream>


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
	_player.update(dt); // Actualizar el jugador
	_spawner.spawnEnemies(_enemies, _player.getPosition()); // Generar enemigos cerca del jugador

	for (auto& enemy : _enemies) // Actualizar cada enemigo
		enemy.chase(_player.getPosition(), dt); // Enemigos persiguen al jugador

	checkCollisions(); // Verificar colisiones entre el jugador y los enemigos

    _camera.setCenter(_player.getPosition());
    _window.setView(_camera);
}

void Game::render()
{
    _window.clear(); 
	_window.draw(_player); // Dibujar el jugador

    for (const auto& enemy : _enemies)
        _window.draw(enemy);

    _window.display();
}

void Game::checkCollisions()
{
    for (auto& enemy : _enemies){ 
		if (_player.getGlobalBounds().intersects(enemy.getGlobalBounds())) { // Verificar colisiones entre el jugador y los enemigos
            //std::cout << "Colision" << std::endl;
			sf::Vector2f pushBack = enemy.getPrevPosition() - (enemy.getPosition() - enemy.getPrevPosition()) * 2.0f; // Calcular la posición de retroceso
            enemy.setPosition(pushBack); 
        }
        /*
        if (enemy.getGlobalBounds().intersects(enemy.getGlobalBounds())) { 


            std::cout << "Colision" << std::endl;

			//enemy.setPosition(enemy.getPrevPosition()); // Si colisiona consigo mismo, vuelve a la posición anterior
        }
        */
    }
	for (size_t i = 0; i < _enemies.size(); i++) // Verificar colisiones entre enemigos
    {
        for (size_t j = i + 1; j < _enemies.size(); j++) { // 
            if (_enemies[i].getGlobalBounds().intersects(_enemies[j].getGlobalBounds())) {
                std::cout << "Colision" << std::endl;
            }
        }
    }
}
