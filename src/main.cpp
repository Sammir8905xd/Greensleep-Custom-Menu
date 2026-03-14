#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <vector>
#include <string>
#include <sstream>

using namespace geode::prelude;

/**
 * Función auxiliar para procesar la cadena de texto de los ajustes
 * y convertirla en una lista de números (IDs).
 */
std::vector<int> getCustomIDs() {
    std::vector<int> ids;
    std::string s = Mod::get()->getSettingValue<std::string>("custom-level-ids");
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ',')) {
        try {
            // Eliminamos espacios en blanco accidentales
            item.erase(0, item.find_first_not_of(" "));
            item.erase(item.find_last_not_of(" ") + 1);
            if (!item.empty()) {
                ids.push_back(std::stoi(item));
            }
        } catch (...) {
            // Si no es un número válido, lo ignoramos
        }
    }
    return ids;
}

class $modify(MyLevelManager, GameLevelManager) {
    /**
     * Hook para interceptar la carga de niveles principales.
     * Si el ID solicitado está en nuestra lista personalizada, devolvemos el nivel guardado.
     */
    GJGameLevel* getMainLevel(int levelID, bool store) {
        auto customIDs = getCustomIDs();
        
        // Verificamos si el nivel solicitado (1, 2, 3...) existe en nuestra lista
        if (levelID >= 1 && levelID <= static_cast<int>(customIDs.size())) {
            int targetID = customIDs[levelID - 1];
            auto level = GameLevelManager::sharedState()->getSavedLevel(targetID);
            
            if (level) {
                return level;
            }
        }

        // Si no hay reemplazo, cargar el nivel original del juego
        return GameLevelManager::getMainLevel(levelID, store);
    }
};

class $modify(MyLevelSelectLayer, LevelSelectLayer) {
    /**
     * Hook visual para dar el toque de OrangyDev al menú.
     */
    bool init(int page) {
        if (!LevelSelectLayer::init(page)) return false;

        if (Mod::get()->getSettingValue<bool>("orange-mode")) {
            auto background = this->getChildByID("background");
            if (background) {
                // Color Naranja vibrante para el multiverso
                static_cast<CCSprite*>(background)->setColor({ 255, 150, 0 });
            }
        }
        return true;
    }
};
