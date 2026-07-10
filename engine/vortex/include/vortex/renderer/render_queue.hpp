#pragma once

#include "vortex/renderer/render_command.hpp"
#include "vortex/core/containers/vortex_array.hpp"
#include "vortex/core/utilities/algorithm.hpp"

namespace vortex::renderer
{
    class VxRenderQueue
    {
    public:
        VxRenderQueue(size_t max_commands = 10000)
            : m_commands(max_commands)
        {
        }

        void submit(const RenderCommand& cmd)
        {
            m_commands.push_back(cmd);
        }

        void sort()
        {
            // Sort by z_index. If z_index is equal, you would sort by texture ID to batch draw calls!
            utils::sort(m_commands.begin(), m_commands.end(), [](const RenderCommand& a, const RenderCommand& b) {
                return a.z_index < b.z_index;
            });
        }

        void clear()
        {
            m_commands.clear();
        }

        const containers::VxArray<RenderCommand>& getCommands() const
        {
            return m_commands;
        }

    private:
        containers::VxArray<RenderCommand> m_commands;
    };
}
