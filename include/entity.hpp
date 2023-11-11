#pragma once

#include "config.hpp"
#include "grid.hpp"
#include "trajectory.hpp"
#include "types.hpp"

namespace iron_dome_game
{
struct Entity
{
    Trajectory trajectory;
    
    virtual EntityType type() { return EntityType::NONE; }

    virtual Pos pos() = 0;

    BoundingBox boundingBox();

    virtual void drawOnGrid(Grid &grid) = 0;
    
    bool isActive() { return m_isActive; }
    void setIsActive(bool isActive) { m_isActive = isActive; }

protected:
    bool m_isActive = true;
    uint16_t width = 0;
    uint16_t height = 0;
    virtual bool isStatic() = 0;    
};

}