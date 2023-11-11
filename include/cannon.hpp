#pragma once

#include "entity.hpp"

namespace iron_dome_game
{
struct Cannon : public Entity
{
    Cannon();
    ~Cannon() = default;

    Pos pos() override{ return trajectory.initialState.pos; };

    void drawOnGrid(Grid &grid) override;

    EntityType type() override { return EntityType::CANNON; }

private:
    bool isStatic() { return true; }
};

}