#include "application.hpp"
#include "vortex/core/input/input_manager.hpp"
#include "vortex/renderer/renderer_backend.hpp"
#include "vortex/renderer/render_queue.hpp"
#include "vortex/core/utilities/vortex_time.hpp"
#include "entity_factory.hpp"

using namespace vortex;

Application::Application()
    : m_isRunning(true), m_targetTimeStep(1.0 / m_physicsUpdateRate), m_accumulator(0.0)
{
    renderer::backend::initWindow(800, 600, "Project-Momentum");
}

Application::~Application()
{
    m_isRunning = false;
    // CloseAudioDevice();
    renderer::backend::closeWindow();
}

void Application::run()
{
    utils::VxTime::init();

    while (m_isRunning && !renderer::backend::shouldClose())
    {
        utils::VxTime::update();
        double dt = utils::VxTime::getDeltaTime();

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
    input::VxInputManager &input = input::VxInputManager::getInstance();

    if (input.isActionPressed(input::EInputAction::Quit))
    {
        m_isRunning = false;
    }

    if (input.isActionPressed(input::EInputAction::Jump))
    {
        // DrawText("Jump Pressed", 500, 500, 20, WHITE); // TODO: Reimplement Text Rendering in Queue
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
    renderer::backend::beginFrame();
    
    // Clear Screen Command
    renderer::VxRenderQueue queue;
    renderer::RenderCommand clearCmd;
    clearCmd.type = renderer::ERenderCommandType::ClearScreen;
    clearCmd.data.clear.color = {0, 0, 0, 255}; // BLACK
    queue.submit(clearCmd);

    // TODO: Iterate over VxSpriteComponent and generate commands here, then push to queue

    queue.sort();
    renderer::backend::executeQueue(queue);

    // DrawFPS(400, 500); // TODO: Wrap Time and Debug text

    renderer::backend::endFrame();
}