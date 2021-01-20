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

#include <stdexcept>
#include <cassert>
#include "Pose2D.h"
#include "Physics2D.h"
#include "Physics2DSystem.h"

using namespace astu;

const EntityFamily Physics2DSystem::FAMILY = EntityFamily::Create<Pose2D, Physics2D>();

Physics2DSystem::Physics2DSystem(int priority)
    : IteratingEntitySystem(FAMILY, priority, "Phsysics2D System")
{
    // Intentionally left empty.
}

void Physics2DSystem::OnStartup()
{
    // Intentionally left empty.
}

void Physics2DSystem::OnShutdown()
{
    // Intentionally left empty.
}

void Physics2DSystem::ProcessEntity(Entity &e)
{
    auto &pose = e.GetComponent<Pose2D>();
    auto &physics = e.GetComponent<Physics2D>();

    physics.vel.x += (physics.force.x * physics.mass) * GetDeltaTime();
    physics.vel.y += (physics.force.y * physics.mass) * GetDeltaTime();
    pose.pos += physics.vel * GetDeltaTime();
}
