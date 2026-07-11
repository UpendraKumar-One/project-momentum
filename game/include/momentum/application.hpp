#pragma once

namespace vortex::renderer { class VxRenderQueue; }

class Application
{
public:

    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:

    void processInput();
    void physicsUpdate();
    void update(double dt);
    void render(vortex::renderer::VxRenderQueue& queue);

    int m_physicsUpdateRate = 60;

    bool m_isRunning;

    double m_targetTimeStep;
    double m_accumulator;
};