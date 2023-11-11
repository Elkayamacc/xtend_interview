#pragma once
#include <stdint.h>
#include <chrono>
#include <math.h>
#include "config.hpp"
#include <syslog.h>
#include "types.hpp"

namespace iron_dome_game
{
struct Pos
{
    int x;
    int y;

    bool isOutOfBoundry()
    {
        if(y < 0 || y > GRID_ROWS)
            return true;
        if(x < 0 || x > GRID_COLUMNS)
            return true;
        return false;
    }
};

struct Velocity
{
    int16_t x;
    int16_t y;
};

struct InitialState
{
    Pos pos;
    Velocity velocity;
    std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
};

struct Trajectory
{
    InitialState initialState;

        std::chrono::duration<float> duration() { return  std::chrono::steady_clock::now() - initialState.t0; }
        
        Pos calculatePosition(EntityType type = EntityType::NONE , std::chrono::steady_clock::time_point = std::chrono::steady_clock::now())
        {
            Pos pos;
            float time = duration().count();
            if(type == EntityType::PLATE)
            {
                pos.x = round(initialState.pos.x + initialState.velocity.x * time);
                pos.y = round(initialState.pos.y + initialState.velocity.y * time + 0.5 * GRAVITY * pow(time, 2));
                syslog(LOG_INFO, "Plate calculated position: x=%d, y=%d", pos.x, pos.y);
            }            
            else // type rocket
            {
                pos.x = round(initialState.pos.x + initialState.velocity.x*time);
                pos.y = round(initialState.pos.y + 0.5*initialState.velocity.y*time);
                syslog(LOG_INFO, "Rocket calculated position: x=%d, y=%d", pos.x, pos.y);
            }
            return pos;
        }
};

}