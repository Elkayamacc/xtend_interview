#include "rocket.hpp"

namespace iron_dome_game
{
Rocket::Rocket(Velocity velocity)
{
    trajectory.initialState.pos.x = 10;
    trajectory.initialState.pos.y = 5;
    trajectory.initialState.velocity.x = velocity.x;
    trajectory.initialState.velocity.y = velocity.y;

    width   = 4;
    height  = 4;
}

//============================================================================//

void Rocket::drawOnGrid(Grid &grid)
{
    if(pos().isOutOfBoundry())
    {
        m_isActive = false;
        return;
    }

    auto col = pos().x;
    auto row = pos().y;

    grid.drawPixel(row, col,   '/');
    grid.drawPixel(row, col+1, '_');
    grid.drawPixel(row, col+2, '/');

    grid.drawPixel(row+1, col+1, '/');
    grid.drawPixel(row+1, col+2, ' ');
    grid.drawPixel(row+1, col+3, '/');

    grid.drawPixel(row+2, col+2, '/');
    grid.drawPixel(row+2, col+3, ' ');
    grid.drawPixel(row+2, col+4, '/');

    grid.drawPixel(row+3, col+3, ' ');
    grid.drawPixel(row+3, col+4, '^');
    grid.drawPixel(row+3, col+5, ' ');
}

}