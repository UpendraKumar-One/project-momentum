#include "game/application.hpp"
#include "engine/core/input_manager.hpp"
#include "raylib.h"
#include "engine/ecs/registry.hpp"
#include "game/entity_factory.hpp"

Application::Application()
    : b_isRunning_(true), f_targetTimeStep_(1.0f / i_PHYSICS_UPDATE_RATE_), f_accumulator_(0.0f)
{
    SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);

    InitAudioDevice();
    InitWindow(800, 600, "Project-Momentum");

    int i_monitor = GetCurrentMonitor();
    int i_screenWidth = GetMonitorWidth(i_monitor);
    int i_screenHeight = GetMonitorHeight(i_monitor);
    int i_refreshRate = GetMonitorRefreshRate(i_monitor);

    SetWindowSize(i_screenWidth, i_screenHeight);
    SetWindowPosition(0, 0);

    ClearWindowState(FLAG_WINDOW_HIDDEN);

    SetWindowState(FLAG_FULLSCREEN_MODE);

    if (i_refreshRate > 0)
        SetTargetFPS(i_refreshRate);
    else
        SetTargetFPS(60);
}

Application::~Application()
{
    b_isRunning_ = false;
    CloseAudioDevice();
    CloseWindow();
}

void Application::run()
{
    double f_prevTime = GetTime();

    while (b_isRunning_ && !WindowShouldClose())
    {
        double f_currentTime = GetTime();
        double dt = f_currentTime - f_prevTime;
        f_prevTime = f_currentTime;

        if (dt > 0.25f)
            dt = 0.25;

        f_accumulator_ += dt;

        ProcessInput();

        while (f_accumulator_ > f_targetTimeStep_)
        {
            PhysicsUpdate();
            f_accumulator_ -= f_targetTimeStep_;
        }

        Update(dt);
        Render();
    }
}

void Application::ProcessInput()
{
    InputManager &input = InputManager::GetInstance();

    if (input.IsActionPressed(InputAction::QUIT))
    {
        b_isRunning_ = false;
    }

    if (input.IsActionPressed(InputAction::JUMP))
    {
        DrawText("Jump Pressed", 500, 500, 20, WHITE);
    }
}

void Application::PhysicsUpdate()
{
}

void Application::Update(double dt)
{
}

void Application::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(400, 500);
    EndDrawing();
}