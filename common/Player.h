#pragma once

#include <EntityService.h>
#include <Vector2.h>

class Player : public astu::EntityComponent
{
public:
    /** The radius of the circle collider. */
    double radius;

    /**
     * Constructor.
     * 
     * @param r the radius
     */
    Player(double r = 1.0)
        : radius(r)
    {
        // Intentionally left empty.
    }
};
