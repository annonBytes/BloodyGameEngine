/*  ____          _____          _____          
 * |  _ \   /\   / ____|   /\   / ____|   /\    
 * | |_) | /  \ | |  __   /  \ | |  __   /  \   
 * |  _ < / /\ \| | |_ | / /\ \| | |_ | / /\ \  
 * | |_) / ____ \ |__| |/ ____ \ |__| |/ ____ \ 
 * |____/_/    \_\_____/_/    \_\_____/_/    \_\
 *
 * Bagaga - Bloody Amazing Game Architecture Game
 * Copyright 2020 Bagaga Development Team. All rights reserved.                                             
 */

#pragma once

#include <EntityService.h>
#include <Vector2.h>

class Physics2D : public astu::EntityComponent
{
public:
    astu::Vector2<double> vel;
    astu::Vector2<double> force;
    double mass;

    Physics2D(double velX = 0, double velY = 0, double forceX = 0, double forceY = 0, double _mass = 0)
        : vel(velX, velY), force(forceX, forceY), mass(_mass)
    {
        // Intentionally left empty.
    }

    Physics2D(const astu::Vector2<double> &v, const astu::Vector2<double> &f, double _mass = 0)
        : vel(v), force(f), mass(_mass)
    {
        // Intentionally left empty.
    }
};