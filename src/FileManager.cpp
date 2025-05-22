#include "FileManager.h"
#include <fstream>
#include <cstring>

FileManager::FileManager(const std::string& saveFile, const std::string& scoreFile)
    : _saveFile(saveFile), _scoreFile(scoreFile) {}

bool FileManager::saveGame(const Player& player) {
    std::ofstream file(_saveFile, std::ios::binary);
    if (!file) return false;

    // Serialize player data (simplified)
    // TODO: Implement real serialization

    file.close();
    return true;
}

bool FileManager::loadGame(Player& player) {
    std::ifstream file(_saveFile, std::ios::binary);
    if (!file) return false;

    // TODO: Deserialize data into player

    file.close();
    return true;
}

bool FileManager::saveScores(const std::vector<ScoreEntry>& scores) {
    std::ofstream file(_scoreFile, std::ios::binary);
    if (!file) return false;

    for (const auto& s : scores) {
        file.write(reinterpret_cast<const char*>(&s), sizeof(ScoreEntry));
    }
    file.close();
    return true;
}

std::vector<ScoreEntry> FileManager::loadScores() {
    std::vector<ScoreEntry> result;
    std::ifstream file(_scoreFile, std::ios::binary);
    if (!file) return result;

    ScoreEntry s;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(ScoreEntry))) {
        result.push_back(s);
    }
    file.close();
    return result;
}
