#pragma once

class Application
{
public:

    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:

    void ProcessInput();
    void PhysicsUpdate();
    void Update(double);
    void Render();

    int i_PHYSICS_UPDATE_RATE_ = 60;

    bool b_isRunning_;

    double f_targetTimeStep_;
    double f_accumulator_;
};