#ifndef ARCADE_APP_GAMEMANAGER_H
#define ARCADE_APP_GAMEMANAGER_H

#include <memory>

#include "app/Scene.h"
#include "app/SceneId.h"
#include "app/WindowConfig.h"

namespace arcade {

class GameManager {
	public:
		GameManager() = default;

		void switchTo(SceneId sceneId);
		void update(float dt);
		void render();
		WindowConfig getWindowConfig() const;

	private:
		std::unique_ptr<Scene> createScene(SceneId sceneId) const;
		std::unique_ptr<Scene> currentScene_;
};

}

#endif
