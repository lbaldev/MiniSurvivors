#include "FileManager.h"
#include <fstream>
#include <cstring>
#include <iostream>

FileManager::FileManager(const std::string& archivoPartida, const std::string& archivoPuntajes)
    : _archivoPartida(archivoPartida), _archivoPuntajes(archivoPuntajes) {
}

bool FileManager::guardarPartida(const Player& jugador, const std::vector<Enemy>& enemigos) {
    FILE* pArchivo;
    errno_t err = fopen_s(&pArchivo, _archivoPartida.c_str(), "wb");
    if (err != 0 || pArchivo == NULL) return false;

    sf::Vector2f pos = jugador.getPosition();
    int vida = jugador.getHealth();
    int nivel = jugador.getLevel();
    int exp = jugador.getExp();
    float daño = jugador.getBaseDamage();

    fwrite(&pos, sizeof(pos), 1, pArchivo);
    fwrite(&vida, sizeof(vida), 1, pArchivo);
    fwrite(&nivel, sizeof(nivel), 1, pArchivo);
    fwrite(&exp, sizeof(exp), 1, pArchivo);
    fwrite(&daño, sizeof(daño), 1, pArchivo);

    int cantidadEnemigos = enemigos.size();
    fwrite(&cantidadEnemigos, sizeof(int), 1, pArchivo);

    for (const auto& enemigo : enemigos) {
        sf::Vector2f ePos = enemigo.getPosition();
        float eVida = enemigo.getHealth();
        fwrite(&ePos, sizeof(ePos), 1, pArchivo);
        fwrite(&eVida, sizeof(eVida), 1, pArchivo);
    }

    fclose(pArchivo);
    return true;
}

bool FileManager::cargarPartida(Player& jugador, std::vector<Enemy>& enemigos) {
    FILE* pArchivo;
    errno_t err = fopen_s(&pArchivo, _archivoPartida.c_str(), "wb");
    if (err != 0 || pArchivo == NULL) return false;

    sf::Vector2f pos;
    int vida, nivel, exp;
    float damage;
    std::string textura;

    fread(&pos, sizeof(pos), 1, pArchivo);
    fread(&vida, sizeof(vida), 1, pArchivo);
    fread(&nivel, sizeof(nivel), 1, pArchivo);
    fread(&exp, sizeof(exp), 1, pArchivo);
    fread(&damage, sizeof(damage), 1, pArchivo);
	fread(&textura, sizeof(char) * 256, 1, pArchivo);

    jugador.setPosition(pos);
    jugador.setHealth(vida);
    jugador.setLevel(nivel);
    jugador.setExp(exp);
    jugador.setBaseDamage(damage);
	 // Asumiendo que Player tiene un método setTexture

    int cantidadEnemigos;
    fread(&cantidadEnemigos, sizeof(int), 1, pArchivo);
    enemigos.clear();
    for (int i = 0; i < cantidadEnemigos; ++i) {
        sf::Vector2f ePos;
        float eVida;
        fread(&ePos, sizeof(ePos), 1, pArchivo);
        fread(&eVida, sizeof(eVida), 1, pArchivo);
        enemigos.emplace_back(eVida, 20.0f, 1.0f, "assets/mago.png", ePos);
    }

    fclose(pArchivo);
    return true;
}

bool FileManager::guardarPuntaje(const ScoreEntry& entry) {
    FILE* pArchivo;
    errno_t err = fopen_s(&pArchivo, _archivoPuntajes.c_str(), "wb");
    if (err != 0 || pArchivo == NULL) return false;

    fwrite(&entry, sizeof(ScoreEntry), 1, pArchivo);
    fclose(pArchivo);
    return true;
}

std::vector<ScoreEntry> FileManager::leerPuntajes() {
    std::vector<ScoreEntry> resultados;
    FILE* pArchivo;
    errno_t err = fopen_s(&pArchivo, _archivoPuntajes.c_str(), "wb");
    if (err != 0 || pArchivo == NULL) return resultados;

    ScoreEntry temp;
    while (fread(&temp, sizeof(ScoreEntry), 1, pArchivo)) {
        resultados.push_back(temp);
    }

    fclose(pArchivo);
    return resultados;
}