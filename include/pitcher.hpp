#pragma once

#include "entity.hpp"

namespace iron_dome_game
{
struct Pitcher : public Entity
{
    Pitcher();
    ~Pitcher() = default;

    Pos pos() override{ return trajectory.initialState.pos; };

    void drawOnGrid(Grid &grid) override;

    EntityType type() override { return EntityType::PITCHER; }

private:
    bool isStatic() { return true; }
};

}