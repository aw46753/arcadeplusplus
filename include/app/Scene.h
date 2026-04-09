#ifndef ARCADE_APP_SCENE_H
#define ARCADE_APP_SCENE_H

#include "app/WindowConfig.h"

namespace arcade {

class Scene {
    public:
        virtual ~Scene() = default;

        virtual void onEnter() {}
        virtual void onExit() {}

        virtual void update(float dt) = 0;
        virtual void render() = 0;
        virtual WindowConfig getWindowConfig() const = 0;
};

}

#endif
