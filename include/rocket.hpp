#pragma once

#include "entity.hpp"

namespace iron_dome_game
{
struct Rocket : public Entity
{
    Rocket(Velocity velocity);
    ~Rocket() = default;

    Pos pos() override { return trajectory.calculatePosition(EntityType::ROCKET); };

    void drawOnGrid(Grid &grid) override;

    EntityType type() override { return EntityType::ROCKET; }

private:
    bool isStatic() { return false; }
};

}