#include "vortex/physics/hierarchical_grid.hpp"

vortex::physics::VxHGrid::VxHGrid(vortex::containers::VxArray<size_t> grid_data)
{
    m_levelGrid.resize(grid_data.size());
    for(size_t i = 0; i < grid_data.size(); ++i)
    {
        m_levelGrid[i].cell_size = grid_data[i];
    }
}

void vortex::physics::VxHGrid::clear()
{
    
}