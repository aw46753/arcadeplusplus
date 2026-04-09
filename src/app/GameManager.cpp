#include "app/GameManager.h"
#include "games/pong/PongScene.h"

namespace arcade {

void GameManager::switchTo(SceneId sceneId) {
    if (currentScene_) {
        currentScene_->onExit();
    }

    currentScene_ = createScene(sceneId);

    if (currentScene_) {
        currentScene_->onEnter();
    }
}

void GameManager::update(float dt) {
    if (currentScene_) {
        currentScene_->update(dt);
    }
}

void GameManager::render() {
    if (currentScene_) {
        currentScene_->render();
    }
}

WindowConfig GameManager::getWindowConfig() const {
    if (currentScene_) {
        return currentScene_->getWindowConfig();
    }

    return {};
}

std::unique_ptr<Scene> GameManager::createScene(SceneId sceneId) const {
    switch (sceneId) {
        case SceneId::Pong:
            return std::make_unique<PongScene>();
        default:
            return nullptr;
    }
}

}
