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

#include <UpdateService.h>
#include <Events.h>
#include <memory>
#include <Service.h>
#include "Polyline.h"
#include <IteratingEntitySystem.h>

class PlayerTestService : public astu::IteratingEntitySystem, public astu::MouseButtonListener
{
public:
    /**
     * Constructor.
     */
    PlayerTestService(int priority = 0);

protected:
    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void ProcessEntity(astu::Entity &player) override;
    virtual void OnShutdown() override;
    virtual void OnSignal(const astu::MouseButtonEvent &signal) override;

private:
    std::shared_ptr<Polyline::Polygon> shape1;
    std::shared_ptr<Polyline::Polygon> shape2;
    static const astu::EntityFamily FAMILY;

    /**
     * Adds a test entity at a certain position.
     * 
     * @param t the type of the entity to create
     * @param p the position of the test entity in world space
     * @param s the rotation speed in degrees per seconds
     * @param c the color of the test entity
     */
    void AddTestEntity(const astu::Vector2<double> &p, double s, const astu::Color &c);
};