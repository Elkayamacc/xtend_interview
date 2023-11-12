#include <iostream>
#include "grid.hpp"
#include "entity.hpp"

namespace iron_dome_game
{

void Grid::draw() 
{
    for (int i = GRID_ROWS - 1; i >= 0; --i)
    {
        for (int j = 0; j < GRID_COLUMNS; ++j)
        {
            std::cout << m_grid[i][j];
        }
        std::cout << std::endl;
    }
}

//============================================================================//

void Grid::refresh() 
{
    // Draw background
    forEveryPixel(
        [this](int row, int col)
        {
            m_grid[row][col] = ' ';
        }
    );

    // Draw ground
    forEveryPixel(
        [this](int row, int col)
        {
            m_grid[row][col] = '_';
        },
        1
    );

    for (auto entity = m_entities.begin() ; entity != m_entities.end(); )
    {
        if ((*entity)->isActive())
        {
            (*entity)->drawOnGrid(*this);
            entity++;
        }
        else
        {
            entity = m_entities.erase(entity);        
        }
            
    }
}

//============================================================================//

bool Grid::drawPixel(uint16_t row, uint16_t col, char pixel) 
{
    if (row >= 0 && row < rows() && col >= 0 && col < columns() && pixel != ' ')
    {
        m_grid[row][col] = pixel;
        return true;
    }
    return false;
}

//============================================================================//

void Grid::forEveryPixel(std::function<void(int row, int col)> function, const int rowCount, const int columnCount) 
{
    for (int i = 0; i < rowCount; ++i)
    {
        for (int j = 0; j < columnCount; ++j)
        {
            function(i, j);
        }
    }
}

//============================================================================//

uint16_t Grid::checkHits() 
{
    return m_Hits;
}

//============================================================================//
void Grid::searchForIntersects(const bool& gameIsActive)
{
    while(gameIsActive)
    {
        for (auto Rocket : m_entities)
        {
            if (Rocket->isActive() && Rocket->type() == EntityType::ROCKET)
            {
                for(auto Plate : m_entities)
                {
                    if (Plate->isActive() && Plate->type() == EntityType::PLATE)
                    {
                        if (intersects(Rocket, Plate))
                        {
                            Plate->setIsActive(false);
                            Rocket->setIsActive(false);
                            m_Hits++;
                            break;
                        }
                    }
                }
            }
        }
    }
}

//============================================================================//

bool Grid::intersects(const std::shared_ptr<Entity> first, const std::shared_ptr<Entity> second) 
{
    if (areOverlapping(first->boundingBox(), second->boundingBox()))
        return true;
    return false;
}

//============================================================================//

const bool Grid::areOverlapping(const BoundingBox& boundingBox1, const BoundingBox& boundingBox2)
{
    // Check if one box is to the left of the other
    if (boundingBox1.p2.x < boundingBox2.p1.x || boundingBox2.p2.x < boundingBox1.p1.x) {
        return false;
    }
    
    // Check if one box is above the other
    if (boundingBox1.p2.y < boundingBox2.p1.y || boundingBox2.p2.y < boundingBox1.p1.y) {
        return false;
    }

    return true; // If the above conditions are not met, the boxes are overlapping
}

}