#pragma once

#include "entity.hpp"

namespace iron_dome_game
{
struct Plate : public Entity
{
    Plate(Velocity velocity);
    ~Plate() = default;

    Pos pos() override { return trajectory.calculatePosition(EntityType::PLATE); };

    void drawOnGrid(Grid &grid) override;

    EntityType type() override { return EntityType::PLATE; }

private:
    bool isStatic() { return false; }
};

}