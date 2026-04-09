#include "app/Application.h"
#include "app/SceneId.h"

#include "raylib.h"

namespace arcade {

Application::Application() = default;

Application::~Application() {
    shutdown();
}

void Application::run() {
    initialize();

    while (!WindowShouldClose()) {
        gameManager_.update(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        gameManager_.render();
        EndDrawing();
    }
}

void Application::initialize() {
    if (initialized_) {
        return;
    }

    InitWindow(800, 800, "arcade++");
    SetTargetFPS(60);

    gameManager_.switchTo(SceneId::Pong);
    applyWindowConfig(gameManager_.getWindowConfig());
    initialized_ = true;
}

void Application::applyWindowConfig(const WindowConfig& config) const {
    SetWindowSize(config.width, config.height);
    SetWindowTitle(config.title);
}

void Application::shutdown() {
    if (!initialized_) {
        return;
    }

    CloseWindow();
    initialized_ = false;
}

}
