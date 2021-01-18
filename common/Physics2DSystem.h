#pragma once

#include <IteratingEntitySystem.h>
#include "Player.h"

class Physics2DSystem : public astu::IteratingEntitySystem
{
public:
    Physics2DSystem(int priority = 0);

protected:
    // Inherited via IteratingEntitySystem
    virtual void OnStartup() override;
    virtual void OnShutdown() override;
    virtual void ProcessEntity(astu::Entity &e) override;

private:
    /** A constant describing the family of entities this system processes. */
    static const astu::EntityFamily FAMILY;
};
