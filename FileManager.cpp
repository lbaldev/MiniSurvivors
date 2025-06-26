#include "FileManager.h"
#include <cstring>
#include <iostream>

FileManager::FileManager(const std::string& archivoPartida, const std::string& archivoPuntajes)
    : _archivoPartida(archivoPartida), _archivoPuntajes(archivoPuntajes) {
}

bool FileManager::guardarPartida(const Player& jugador, const std::vector<Enemy>& enemigos, const std::vector<ExpOrb>& orbes, float& tiempo, int& puntuacion) {
    FILE* pArchivo = nullptr;  
    errno_t err = fopen_s(&pArchivo, _archivoPartida.c_str(), "wb");  
    if (err != 0 || pArchivo == nullptr) return false;

    // Guardar datos del jugador
    sf::Vector2f pos = jugador.getPosition();
    int vida = jugador.getHealth();
    int nivel = jugador.getLevel();
    int exp = jugador.getExp();
    float damage = jugador.getBaseDamage();
    float speed = jugador.getSpeed();
    float cooldown = jugador.getCooldownAtaque();
    float rango = jugador.getRangoProyectil();
    float velocidadProy = jugador.getVelocidadProyectil();
    bool autoAim = jugador.isAutoAimEnabled();
    std::string tex = jugador.getTexturePath();
    int lenTex = tex.size();
	std::string nombre = jugador.getName();
    int lenName = nombre.size();

	fwrite(&puntuacion, sizeof(int), 1, pArchivo); 
    fwrite(&tiempo, sizeof(tiempo), 1, pArchivo);
    fwrite(&pos, sizeof(pos), 1, pArchivo);
    fwrite(&vida, sizeof(vida), 1, pArchivo);
    fwrite(&nivel, sizeof(nivel), 1, pArchivo);
    fwrite(&exp, sizeof(exp), 1, pArchivo);
    fwrite(&damage, sizeof(damage), 1, pArchivo);
    fwrite(&speed, sizeof(speed), 1, pArchivo);
    fwrite(&cooldown, sizeof(cooldown), 1, pArchivo);
    fwrite(&rango, sizeof(rango), 1, pArchivo);
    fwrite(&velocidadProy, sizeof(velocidadProy), 1, pArchivo);
    fwrite(&autoAim, sizeof(autoAim), 1, pArchivo);
    fwrite(&lenTex, sizeof(int), 1, pArchivo);
    fwrite(tex.c_str(), sizeof(char), lenTex, pArchivo);
    fwrite(&lenName, sizeof(int), 1, pArchivo);
    fwrite(nombre.c_str(), sizeof(char), lenName, pArchivo);

    // Guardar enemigos
    int cantidadEnemigos = enemigos.size();
    fwrite(&cantidadEnemigos, sizeof(int), 1, pArchivo);
    for (const auto& enemigo : enemigos) {
        sf::Vector2f ePos = enemigo.getPosition();
        float eVida = enemigo.getHealth();
        float eSpeed = enemigo.getSpeed();
        float eDamage = enemigo.getDamage();
        std::string eTex = enemigo.getTexturePath();
        int lenETex = eTex.size();

        fwrite(&ePos, sizeof(ePos), 1, pArchivo);
        fwrite(&eVida, sizeof(eVida), 1, pArchivo);
        fwrite(&eSpeed, sizeof(eSpeed), 1, pArchivo);
        fwrite(&eDamage, sizeof(eDamage), 1, pArchivo);
        fwrite(&lenETex, sizeof(int), 1, pArchivo);
        fwrite(eTex.c_str(), sizeof(char), lenETex, pArchivo);
    }

    // Guardar orbes de experiencia
    int cantidadOrbes = orbes.size();
    fwrite(&cantidadOrbes, sizeof(int), 1, pArchivo);
    for (const auto& orb : orbes) {
        sf::Vector2f oPos = orb.getPosition();
        int amount = orb.getAmount();
        fwrite(&oPos, sizeof(oPos), 1, pArchivo);
        fwrite(&amount, sizeof(amount), 1, pArchivo);
    }

    fclose(pArchivo);
    return true;
}


bool FileManager::cargarPartida(Player& jugador, std::vector<Enemy>& enemigos, std::vector<ExpOrb>& orbes, float& tiempo, int& puntuacion) {
    FILE* pArchivo = nullptr;
    errno_t err = fopen_s(&pArchivo, _archivoPartida.c_str(), "rb");
    if (err != 0 || pArchivo == nullptr) return false;

    sf::Vector2f pos;
    int vida, nivel, exp, puntos;
    float damage, speed, cooldown, rango, velocidadProy, timer;
    bool autoAim;
    int lenTex,lenName;

	fread(&puntos, sizeof(int), 1, pArchivo);
	fread(&timer, sizeof(timer), 1, pArchivo);
    fread(&pos, sizeof(pos), 1, pArchivo);
    fread(&vida, sizeof(vida), 1, pArchivo);
    fread(&nivel, sizeof(nivel), 1, pArchivo);
    fread(&exp, sizeof(exp), 1, pArchivo);
    fread(&damage, sizeof(damage), 1, pArchivo);
    fread(&speed, sizeof(speed), 1, pArchivo);
    fread(&cooldown, sizeof(cooldown), 1, pArchivo);
    fread(&rango, sizeof(rango), 1, pArchivo);
    fread(&velocidadProy, sizeof(velocidadProy), 1, pArchivo);
    fread(&autoAim, sizeof(autoAim), 1, pArchivo);
    fread(&lenTex, sizeof(int), 1, pArchivo);
    std::string tex(lenTex, '\0');
    fread(&tex[0], sizeof(char), lenTex, pArchivo);
    fread(&lenName, sizeof(int), 1, pArchivo); 
    std::string nombre(lenName, '\0');
    fread(&nombre[0], sizeof(char), lenName, pArchivo); 

    jugador = Player(vida, speed, tex);
	jugador.setPosition(pos);
    jugador.setLevel(nivel);
    jugador.setExp(exp);
    jugador.setBaseDamage(damage);
    jugador.setCooldownAtaque(cooldown);
    jugador.setRangoProyectil(rango);
    jugador.setVelocidadProyectil(velocidadProy);
    jugador.setAutoAim(autoAim);
	jugador.setName(nombre);
	tiempo = timer;
    puntuacion = puntos;
    // Enemigos
    enemigos.clear();
    int cantidadEnemigos;
    fread(&cantidadEnemigos, sizeof(int), 1, pArchivo);
    for (int i = 0; i < cantidadEnemigos; ++i) {
        sf::Vector2f ePos;
        float eVida, eSpeed, eDamage;
        int lenETex;
        fread(&ePos, sizeof(ePos), 1, pArchivo);
        fread(&eVida, sizeof(eVida), 1, pArchivo);
        fread(&eSpeed, sizeof(eSpeed), 1, pArchivo);
        fread(&eDamage, sizeof(eDamage), 1, pArchivo);
        fread(&lenETex, sizeof(int), 1, pArchivo);
        std::string eTex(lenETex, '\0');
        fread(&eTex[0], sizeof(char), lenETex, pArchivo);
        enemigos.emplace_back(eVida, eSpeed, eDamage, eTex, ePos);
    }

    // Orbes
    orbes.clear();
    int cantidadOrbes;
    fread(&cantidadOrbes, sizeof(int), 1, pArchivo);
    for (int i = 0; i < cantidadOrbes; ++i) {
        sf::Vector2f oPos;
        int amount;
        fread(&oPos, sizeof(oPos), 1, pArchivo);
        fread(&amount, sizeof(amount), 1, pArchivo);
        orbes.emplace_back(oPos, amount);
    }

    fclose(pArchivo);
    return true;
}



bool FileManager::guardarPuntaje(const ScoreEntry& entry) {
    FILE* pArchivo;
    errno_t err = fopen_s(&pArchivo, _archivoPuntajes.c_str(), "ab"); // append binary
    if (err != 0 || pArchivo == NULL) {
        std::cerr << "Error al abrir el archivo de puntajes para escritura: " << _archivoPuntajes << std::endl;
        return false;
    }

    size_t written = fwrite(&entry, sizeof(ScoreEntry), 1, pArchivo);
    fclose(pArchivo);
    return written == 1;
}

std::vector<ScoreEntry> FileManager::leerPuntajes() {
    std::vector<ScoreEntry> scores;
    FILE* pArchivo;
    errno_t err = fopen_s(&pArchivo, _archivoPuntajes.c_str(), "rb"); 
    if (err != 0 || pArchivo == NULL) {
        std::cerr << "Advertencia: El archivo de puntajes no existe o no se pudo abrir: " << _archivoPuntajes << std::endl;
        return scores; // Retorna un vector vacío si el archivo no existe o hay error
    }

    fseek(pArchivo, 0, SEEK_END);
    long fileSize = ftell(pArchivo);
    fseek(pArchivo, 0, SEEK_SET);

    int cantidadRegistros = 0;
    if (sizeof(ScoreEntry) > 0) {
        cantidadRegistros = fileSize / sizeof(ScoreEntry);
    }

    scores.reserve(cantidadRegistros);

    ScoreEntry entry;
    for (int i = 0; i < cantidadRegistros; ++i) {
        if (fread(&entry, sizeof(ScoreEntry), 1, pArchivo) == 1) {
            scores.push_back(entry);
        }
        else {
            std::cerr << "Error al leer entrada de puntaje en la posicion " << i << std::endl;
            break;
        }
    }

    fclose(pArchivo);

    return scores;
}