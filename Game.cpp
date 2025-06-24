#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>  // Para std::stringstream
#include <iomanip>  // Para std::fixed y std::setprecision  ambos usados para stats en pantalla
#include "Game.h"
#include <random> 


//probando git

Game::Game(sf::RenderWindow& window)
    : _window(window),dt(0),
    _player(100.0f, 200.0f, "assets/mago.png"),

    _shouldExitToMenu(false),
	_puntuacion(0),
	_timer(0.f),
    _pauseMenu(WINDOW_WIDTH, WINDOW_HEIGHT),
	_fileManager("save.txt", "puntajes.txt")
{
    _font.loadFromFile("assets/font.otf");
    // Música de fondo
    musicaFondo.openFromFile("assets/MusicaFondo.ogg");
    musicaFondo.setLoop(true);
    musicaFondo.setVolume(10);

    // Sonido de ataque
    bufferAtaque.loadFromFile("assets/Hit.ogg");
    sonidoAtaque.setBuffer(bufferAtaque);
    sonidoAtaque.setVolume(100);

    //Icono de jugador
    _playerIconTexture.loadFromFile("assets/player_icon.png");
    _playerIcon.setTexture(_playerIconTexture); 
    _playerIcon.setPosition(20.f, 20.f);

    ;
    _backgroundTexture.loadFromFile("assets/fondo2noche.png");
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
    _expBarBackground.setOutlineThickness(2.f);
    _expBarBackground.setOutlineColor(sf::Color::Black);

    _expBarFill.setSize(sf::Vector2f(0.f, barHeight));
    _expBarFill.setFillColor(sf::Color::Yellow);
    _expBarFill.setPosition(_expBarBackground.getPosition());

    _levelText.setString("Nivel: 1");
    // Centrados
    sf::FloatRect textBounds = _levelText.getLocalBounds();
    _levelText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    _levelText.setPosition(centerX, _expBarBackground.getPosition().y - 25.f);


	// Timer
    _timerTexto.setFont(_font);
    _timerTexto.setCharacterSize(24);
    _timerTexto.setFillColor(sf::Color::Green);
    _timerTexto.setPosition(600.f, 20.f);

    // Puntuacion
    _textoPuntuacion.setFont(_font);
    _textoPuntuacion.setCharacterSize(24);
    _textoPuntuacion.setFillColor(sf::Color::Red);
    _textoPuntuacion.setPosition(900.f, 20.f);

    // Icono jugador
    _playerIcon.setTexture(_playerIconTexture);
    _playerIcon.setPosition(20.f, 20.f); 
    _playerIcon.setScale(90.f / _playerIcon.getLocalBounds().width,
        90.f / _playerIcon.getLocalBounds().height); 

    // Fondo semitransparente para las stats
    _statsBackground.setSize(sf::Vector2f(200.f, 180.f));
    _statsBackground.setFillColor(sf::Color(0, 0, 0, 150)); 
    _statsBackground.setPosition(10.f, 120.f); 

    // Texto de estadísticas
    _statsText.setFont(_font);
    _statsText.setCharacterSize(18);
    _statsText.setFillColor(sf::Color::White);
    _statsText.setPosition(20.f, 125.f);

    //Bordes de textos
    _levelText.setOutlineThickness(2.f);
    _levelText.setOutlineColor(sf::Color::Black);

    _timerTexto.setOutlineThickness(2.f);
    _timerTexto.setOutlineColor(sf::Color::Black);

    _textoPuntuacion.setOutlineThickness(2.f);
    _textoPuntuacion.setOutlineColor(sf::Color::Black);

    updatePlayerStatsDisplay();

    //pantalla game over
    _gameOverText.setFont(_font);
    _gameOverText.setCharacterSize(48);
    _gameOverText.setFillColor(sf::Color::Red);
    _gameOverText.setString("            GAME OVER\n\nPuntuacion: 0"); 
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
    _gameOverText.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 3.f);

}

void Game::processEvents() {  
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (_state == GameState::GameOver && event.key.code == sf::Keyboard::Escape) {
            _shouldExitToMenu = true;
            return;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (_state == GameState::Paused) {
                    _state = GameState::Playing;
                }
                else {
                    _state = GameState::Paused;
                }
            }
            if (_state == GameState::Paused) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                    _pauseMenu.moveUp();
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                    _pauseMenu.moveDown();
                if (event.key.code == sf::Keyboard::Enter) {
                    int selected = _pauseMenu.getSelectedIndex();
                    switch (selected) {
                    case 0:
                        _state = GameState::Playing; // Continuar juego
                        break;
                    case 1:
                        _fileManager.guardarPartida(_player, _enemies, _expOrbs);
                        std::cout << "[INFO] guardando partida..." << std::endl;
                        _shouldExitToMenu = true;
                        break;
                    case 2:
                        _shouldExitToMenu = true; // Volver al menú principal
                        break;
                    }
                }
            }
        }
    }
}


void Game::run() {
    sf::Clock clock;
    musicaFondo.play();
    while (_window.isOpen() && !_shouldExitToMenu) {

        dt = clock.restart().asSeconds();
        processEvents();

        if (_shouldExitToMenu) break; 

        update(dt);
        render();
    }
}

void Game::updatePlayerStatsDisplay() {
    std::stringstream stats;
    stats << std::fixed << std::setprecision(1); // cantidad de decimales

    stats << "Ataque: " << _player.getBaseDamage() << "\n"
        << "Velocidad: " << _player.getSpeed() << "\n"
        << "Cadencia: " << (1.0f / _player.getCooldownAtaque()) << "/s\n"
        << "Rango: " << _player.getRangoProyectil() << "\n"
        << "Vel. Disparo: " << _player.getVelocidadProyectil();

    _statsText.setString(stats.str());
}

void Game::update(float dt)
{


    if (_state == GameState::GameOver) return;

    if (_player.getHealth() <= 0 && _state != GameState::GameOver) {
        _state = GameState::GameOver;
        _gameOverText.setString("    GAME OVER\n\nJugador: "+ _player.getName() + "\n\nPuntuacion: " + std::to_string(_puntuacion));
		// Guardar puntaje en el archivo
        ScoreEntry nuevaPuntuacion;
        strncpy_s(nuevaPuntuacion.nombre, _player.getName().c_str(), sizeof(nuevaPuntuacion.nombre) - 1);
        nuevaPuntuacion.nombre[sizeof(nuevaPuntuacion.nombre) - 1] = '\0'; // Asegurar null-termination

        nuevaPuntuacion.puntuacion = _puntuacion;

        if (_fileManager.guardarPuntaje(nuevaPuntuacion)) {
            std::cout << "Puntuacion guardada al morir: " << nuevaPuntuacion.nombre << " - " << nuevaPuntuacion.puntuacion << std::endl;
        }
        else {
            std::cerr << "Error al guardar la puntuacion al morir." << std::endl;
        }

    }
  
    if(_state == GameState::Paused) {
        return;
	}
    updatePlayerStatsDisplay();

    _timer = _timer + dt;
      int tiempoSeg = _timer; // Tiempo de juego en segundos
    _timerTexto.setString("Tiempo: " + std::to_string(tiempoSeg) + "s");

    int minutos = tiempoSeg / 60;
    tiempoSeg %= 60;
    _timerTexto.setString(
        (minutos < 10 ? "0" : "") + std::to_string(minutos) + ":" +
        (tiempoSeg < 10 ? "0" : "") + std::to_string(tiempoSeg)
    );



	_player.update(dt);
    _player.attack(getClosestEnemy());
    _spawner.spawnEnemies(_enemies, _player.getPosition(), _timer);

    for (auto& enemy : _enemies) {
        enemy.chase(_player.getPosition(), dt);
    }

    checkHitpoints();
    checkCollisions();

	// Bloquea la camara al jugador y limita su movimiento al mapa
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
	_textoPuntuacion.setString("Score: " + std::to_string(_puntuacion));


    // Pool de mejoras al azar al subir de nivel
    static int ultimoNivel = _player.getLevel();
    if (_player.getLevel() > ultimoNivel) {
        ultimoNivel = _player.getLevel();

        int mejora = (rand() % 5) + 1;  //sacamos el multidisparo

        switch (mejora) {
        case 1:
            _player.incrementarDanioBase(5.0f);
            std::cout << "+5 de danio base" << std::endl;
            break;
        case 2:
            _player.incrementarVelocidad(100.0f);
            std::cout << "+100 de velocidad" << std::endl;
            break;
        case 3:
            _player.reducirCooldownDisparo(0.2f);
            std::cout << "-0.2s cooldown de disparo" << std::endl;
            break;
        case 4:
            _player.aumentarRangoProyectil(0.1f);
            std::cout << "+0.5s duracion del proyectil" << std::endl;
            break;
        case 5:
            _player.aumentarVelocidadProyectil(100.f);
            std::cout << "+100 de velocidad del proyectil" << std::endl;
            break;
        }
    }

    // Boss
    MAX_ENEMIES = (int)_timer % 120;
    if (!_bossAparecio && !_bossSpawned &&  _timer > 1 && ((int)_timer % 120 == 0)){
        _enemies.clear();
        _enemies.emplace_back(1000.f,                   // vida
            120.f,                     // velocidad
            80.f,                     // daño
            "assets/boss.png",       // textura del boss
			sf::Vector2f(600.f, 400.f), // posición donde aparece el boss
            1000 // puntaje por matar al boss
        );
        _bossSpawned = true;
        _bossAparecio = true;
        std::cout << "Boss aparecio!" << std::endl;
    }

    
 }

void Game::render()
{
    _window.clear();

    if (_state == GameState::GameOver) {
        _window.setView(_window.getDefaultView());
        _window.draw(_gameOverBackground);
        _window.draw(_gameOverText);
        _window.draw(_gameOverPrompt);
        _window.display();
        return;
    }

    if( _state == GameState::Paused) {
        _pauseMenu.draw(_window);
        _window.display();
        return;
	}

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
    _window.draw(_timerTexto);
	_window.draw(_textoPuntuacion);

    //stats a la izq
    _window.draw(_statsBackground);
    _window.draw(_playerIcon);
    _window.draw(_statsText);

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
    // 3. Colisiones Jugador-Orbe de EXP
    for (auto it = _expOrbs.begin(); it != _expOrbs.end(); ) {
        if (_player.getGlobalBounds().intersects(it->getBounds())) {
            _player.addExp(50);  // Sumar EXP
            it = _expOrbs.erase(it);          // Eliminar el orbe y actualizar el iterador
        }
        else {
            ++it;  // Solo avanzar si no se eliminó el orbe
        }
    }

    // Ema
    // 4. Colisiones Proyectil-Enemigo/Boss
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
                        sonidoAtaque.play();
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
			_puntuacion += it->getScoreValue(); // Se suma la puntuacion por eliminar al enemigo
			_expOrbs.emplace_back(it->getPosition(), 10); //Tira el orbe de experiencia al morir
            it = _enemies.erase(it); // Ripea el enemigo y desaparece
        }

        else {
            it->chase(_player.getPosition(), dt);
            ++it;
        }
    }


}

sf::Vector2f Game::getClosestEnemy() {
    float minDistance = std::numeric_limits<float>::max();
    sf::Vector2f closestEnemyPosition;
    // Enemigos
    for (Enemy& enemy : _enemies) {
        float distance = std::hypot(enemy.getPosition().x - _player.getPosition().x,
            enemy.getPosition().y - _player.getPosition().y);
        if (distance < minDistance) {
            minDistance = distance;
            closestEnemyPosition = enemy.getPosition();
        }
    }
    
    return closestEnemyPosition;
}


bool Game::loadSave() {
    return _fileManager.cargarPartida(_player, _enemies, _expOrbs);
}
