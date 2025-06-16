#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>


#include "Game.h"
#include <random> 


//probando git

Game::Game(sf::RenderWindow& window)
    : _window(window),dt(0),
    _player(100.0f, 200.0f, "assets/mago.png")
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
        //std::cout << "Game Over!" << std::endl;
        //_window.close();
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

    // Mariano Actualizar HUD
    int exp = _player.getExp();
    int expToLevel = _player.getExpToNextLevel();
    float fillRatio = static_cast<float>(exp) / expToLevel;
    fillRatio = std::min(fillRatio, 1.f); // evitar que se pase

    _expBarFill.setSize(sf::Vector2f(300.f * fillRatio, 20.f));

    _levelText.setString("Nivel: " + std::to_string(_player.getLevel()));

    // Detectar si el jugador subió de nivel
    static int ultimoNivel = _player.getLevel();
    if (_player.getLevel() > ultimoNivel) {
        ultimoNivel = _player.getLevel();

        // Pool de mejoras
        std::vector<std::string> mejoras = { "danio", "velocidad", "cadencia" };

        // Elegir una mejora aleatoria
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, mejoras.size() - 1);
        std::string mejora = mejoras[dist(gen)];

        // Aplicar la mejora al jugador
        if (mejora == "danio") {
            _player.incrementarDanioBase(5.0f);
            std::cout << "Mejora: +5 de danio base" << std::endl;
        }
        else if (mejora == "velocidad") {
            _player.incrementarVelocidad(50.0f);
            std::cout << "Mejora: +50 de velocidad" << std::endl;
        }
        else if (mejora == "cadencia") {
            _player.reducirCooldownDisparo(0.05f); 
            std::cout << "Mejora: -0.05s cooldown de disparo" << std::endl;
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
            [this, radioProyectil, radioEnemigo](const Proyectil& proyectil) {
                for (auto& enemy : _enemies) {
                    float dx = proyectil.getPosition().x - enemy.getPosition().x;
                    float dy = proyectil.getPosition().y - enemy.getPosition().y;
                    float distancia = std::sqrt(dx * dx + dy * dy);
                    if (distancia < (radioProyectil + radioEnemigo)) {
                        enemy.takeDamage(100);
                        return true; // Eliminar este proyectil
                    }
                }
                return false;
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