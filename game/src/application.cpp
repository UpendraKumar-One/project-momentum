#include "game/application.hpp"
#include "vortex/core/input_manager.hpp"
#include "raylib.h"
#include "vortex/ecs/registry.hpp"
#include "game/entity_factory.hpp"

Application::Application()
    : m_isRunning(true), m_targetTimeStep(1.0 / m_physicsUpdateRate), m_accumulator(0.0)
{
    SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);

    InitAudioDevice();
    InitWindow(800, 600, "Project-Momentum");

    int monitor = GetCurrentMonitor();
    int screen_width = GetMonitorWidth(monitor);
    int screen_height = GetMonitorHeight(monitor);
    int refresh_rate = GetMonitorRefreshRate(monitor);

    SetWindowSize(screen_width, screen_height);
    SetWindowPosition(0, 0);

    ClearWindowState(FLAG_WINDOW_HIDDEN);

    SetWindowState(FLAG_FULLSCREEN_MODE);

    if (refresh_rate > 0)
        SetTargetFPS(refresh_rate);
    else
        SetTargetFPS(60);
}

Application::~Application()
{
    m_isRunning = false;
    CloseAudioDevice();
    CloseWindow();
}

void Application::run()
{
    double prev_time = GetTime();

    while (m_isRunning && !WindowShouldClose())
    {
        double current_time = GetTime();
        double dt = current_time - prev_time;
        prev_time = current_time;

        if (dt > 0.25)
            dt = 0.25;

        m_accumulator += dt;

        processInput();

        while (m_accumulator > m_targetTimeStep)
        {
            physicsUpdate();
            m_accumulator -= m_targetTimeStep;
        }

        update(dt);
        render();
    }
}

void Application::processInput()
{
    vortex::core::InputManager &input = vortex::core::InputManager::getInstance();

    if (input.isActionPressed(vortex::core::InputAction::Quit))
    {
        m_isRunning = false;
    }

    if (input.isActionPressed(vortex::core::InputAction::Jump))
    {
        DrawText("Jump Pressed", 500, 500, 20, WHITE);
    }
}

void Application::physicsUpdate()
{
}

void Application::update(double dt)
{
}

void Application::render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(400, 500);
    EndDrawing();
}