#ifndef GUARD_WORLD_H
#define GUARD_WORLD_H

#include "Entity.h"
#include "SimTime.h"

#include <memory>
#include <list>

namespace SimLib
{
    class World
    {
      public:
        World();
        virtual ~World();

        void addEntity( Entity* entity );
        void removeEntity( Entity* entity );

        virtual void createWorld() = 0;

        void initialize();
        void go();
        void iterate();
        void finalize();

      private:
        typedef std::list< Entity* > EntityList;

        SimTime* m_time;

        EntityList m_entities;

    };
} // namespace SimLib

#endif /* GUARD_WORLD_H */
