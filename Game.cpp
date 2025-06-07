#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>


#include "Game.h"



Game::Game(sf::RenderWindow& window)
    : _window(window),
    _player(100.0f, 200.0f, "assets/mago.png")
{
    //Mariano - Agregando el fondo
    _backgroundTexture.loadFromFile("assets/fondo.png"); 
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setOrigin(
        _backgroundTexture.getSize().x / 2.f,
        _backgroundTexture.getSize().y / 2.f
    );
    _backgroundSprite.setPosition(0.f, 0.f); // posición del centro del mapa

    if (!_font.loadFromFile("assets/font.otf")) {
        std::cout << "Error: no se pudo cargar la fuente.\n";
    }

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

    // Mariano - centrar y lockear camara al borde del mapa
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

    // Recentrar el texto cada vez que cambia (opcional si el número cambia mucho)
    sf::FloatRect textBounds = _levelText.getLocalBounds();
    _levelText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    _levelText.setPosition(WINDOW_WIDTH / 2.f, _expBarBackground.getPosition().y - 25.f);



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

    //HUD
    _window.setView(_window.getDefaultView()); // HUD en pantalla, no en mundo
    _window.draw(_expBarBackground);
    _window.draw(_expBarFill);
    _window.draw(_levelText);


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
