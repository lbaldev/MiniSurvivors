#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>


#include "Game.h"
#include <random> 


//probando git

Game::Game(sf::RenderWindow& window)
    : _window(window),dt(0),
    _player(100.0f, 200.0f, "assets/mago.png"),
    _shouldExitToMenu(false) 
{

	_font.loadFromFile("assets/font.otf");
    _backgroundTexture.loadFromFile("assets/fondo.png");
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setOrigin(
        _backgroundTexture.getSize().x / 2.f,
        _backgroundTexture.getSize().y / 2.f
    );
    _backgroundSprite.setPosition(0.f, 0.f); // posición del centro del mapa

    // Mariano - Agregando la barra de experiencia y nivel
    _levelText.setFont(_font);
    _levelText.setCharacterSize(20);
    _levelText.setFillColor(sf::Color::White);

    float barWidth = 300.f;
    float barHeight = 20.f;
    float centerX = WINDOW_WIDTH / 2.f;

    _expBarBackground.setSize(sf::Vector2f(barWidth, barHeight));
    _expBarBackground.setFillColor(sf::Color(50, 50, 50));
    _expBarBackground.setPosition(centerX - barWidth / 2.f, WINDOW_HEIGHT - 60.f);

    _expBarFill.setSize(sf::Vector2f(0.f, barHeight));
    _expBarFill.setFillColor(sf::Color::Green);
    _expBarFill.setPosition(_expBarBackground.getPosition());

    _levelText.setString("Nivel: 1");
    // Centrados
    sf::FloatRect textBounds = _levelText.getLocalBounds();
    _levelText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    _levelText.setPosition(centerX, _expBarBackground.getPosition().y - 25.f);

    //pantalla game over
    _gameOverText.setFont(_font);
    _gameOverText.setCharacterSize(48);
    _gameOverText.setFillColor(sf::Color::Red);
    _gameOverText.setString("            GAME OVER\n Nombre de jugador: Pepe \n Puntuacion: 1234");
    _gameOverBackground.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    _gameOverBackground.setFillColor(sf::Color::Black);
    _gameOverBackground.setPosition(0.f, 0.f);

    _gameOverPrompt.setFont(_font);
    _gameOverPrompt.setCharacterSize(20);
    _gameOverPrompt.setFillColor(sf::Color::White);
    _gameOverPrompt.setString("\n Presiona cualquier tecla para volver al menu");

    sf::FloatRect promptBounds = _gameOverPrompt.getLocalBounds();
    _gameOverPrompt.setOrigin(promptBounds.width / 2.f, promptBounds.height / 2.f);
    _gameOverPrompt.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + 100.f);



    sf::FloatRect bounds = _gameOverText.getLocalBounds();
    _gameOverText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    _gameOverText.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

}


void Game::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (_state == GameState::GameOver && event.type == sf::Event::KeyPressed) {
            _shouldExitToMenu = true;  
            return;  
        }
    }
}

void Game::run() {
    sf::Clock clock;

    while (_window.isOpen() && !_shouldExitToMenu) {
        dt = clock.restart().asSeconds();
        processEvents();

        if (_shouldExitToMenu) break; 

        update(dt);
        render();
    }
}


void Game::update(float dt)
{
    if (_state == GameState::GameOver) return;

    if (_player.getHealth() <= 0 && _state != GameState::GameOver) {
        _state = GameState::GameOver;
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

    // Mariano Actualizar HUD
    int exp = _player.getExp();
    int expToLevel = _player.getExpToNextLevel();
    float fillRatio = static_cast<float>(exp) / expToLevel;
    fillRatio = std::min(fillRatio, 1.f); // evitar que se pase

    _expBarFill.setSize(sf::Vector2f(300.f * fillRatio, 20.f));

    _levelText.setString("Nivel: " + std::to_string(_player.getLevel()));


    static int ultimoNivel = _player.getLevel();
    if (_player.getLevel() > ultimoNivel) {
        ultimoNivel = _player.getLevel();

        int mejora = (rand() % 5) + 1;

        switch (mejora) {
        case 1:
            _player.incrementarDanioBase(5.0f);
            std::cout << "+5 de danio base" << std::endl;
            break;
        case 2:
            _player.incrementarVelocidad(50.0f);
            std::cout << "+50 de velocidad" << std::endl;
            break;
        case 3:
            _player.reducirCooldownDisparo(0.05f);
            std::cout << "-0.05s cooldown de disparo" << std::endl;
            break;
        case 4:
            _player.aumentarRangoProyectil(0.1f);
            std::cout << "+0.5s duracion del proyectil" << std::endl;
            break;
        case 5:
            _player.aumentarVelocidadProyectil(50.f);
            std::cout << "+50 de velocidad del proyectil" << std::endl;
            break;
        }
    }


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

    _window.setView(_window.getDefaultView()); // HUD en pantalla, no en mundo
    _window.draw(_expBarBackground);
    _window.draw(_expBarFill);
    _window.draw(_levelText);

    if (_state == GameState::GameOver) {
        _window.draw(_gameOverBackground);
        _window.draw(_gameOverText);
        _window.draw(_gameOverPrompt);
        _window.display();
        return;
    }



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
    // Ema
    // 3. Colisiones Proyectil-Enemigo
    const float radioProyectil = 5.f;  // El radio del proyectil
    const float radioEnemigo = 20.f;   // Aproximado para el sprite del enemigo

    auto& projectiles = _player.getProjectiles();  // Ahora podemos modificarlos

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [this, radioProyectil, radioEnemigo](Proyectil& proyectil) {
                // Verificar si se agotó el tiempo de vida
                if (proyectil.getLifetime() <= 0) {
                    return true; // eliminar por tiempo
                }

                for (auto& enemy : _enemies) {
                    float dx = proyectil.getPosition().x - enemy.getPosition().x;
                    float dy = proyectil.getPosition().y - enemy.getPosition().y;
                    float distancia = std::sqrt(dx * dx + dy * dy);
                    if (distancia < (radioProyectil + radioEnemigo)) {
                        enemy.takeDamage(100);
                        return true; // eliminar por colisión
                    }
                }

                return false; // no eliminar
            }),
        projectiles.end()
    );



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