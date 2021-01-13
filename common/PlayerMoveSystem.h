#pragma once

#include <UpdateService.h>
#include <EntityService.h>
#include <SignalService.h>
#include "Player.h"

class PlayerEvent final
{
public:
    std::shared_ptr<astu::Entity> entityA;
    std::shared_ptr<astu::Entity> entityB;

    PlayerEvent(std::shared_ptr<astu::Entity> a, std::shared_ptr<astu::Entity> b)
        : entityA(a), entityB(b)
    {
        // Intentionally left empty.
    }

    astu::Entity &GetEntityA() const
    {
        return *entityA;
    }

    astu::Entity &GetEntityB() const
    {
        return *entityB;
    }
};

using PlayerEventService = astu::SignalService<PlayerEvent>;
using PlayerListener = astu::ISignalListener<PlayerEvent>;

class PlayerMoveSystem : public astu::UpdatableBaseService
{
public:
    PlayerMoveSystem(int priority = 0);

private:
    /** The view to the entities to be processed. */
    std::shared_ptr<astu::EntityView> entityView;

    /** Used to report movements. */
    std::shared_ptr<PlayerEventService> playerEventService;

    // Inherited via Base Service
    virtual void OnStartup() override;
    virtual void OnShutdown() override;
    virtual void OnUpdate() override;

    bool IsMoving(astu::Entity &a, astu::Entity &b);
    void DistanceFromCursor(std::shared_ptr<astu::Entity> a, std::shared_ptr<astu::Entity> b);
};
