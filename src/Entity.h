#ifndef GUARD_SIMLIB_ENTITY_H
#define GUARD_SIMLIB_ENTITY_H

#include "Model.h"
#include "Time.h"

#include "Module.h"
#include "QueueMngr.h"

#include <list>
#include <memory>
#include <unordered_map>

namespace SimLib
{
    typedef unsigned int ModelOrder;
    typedef std::list< std::pair< Model*, ModelOrder > > ModelList;
    typedef std::list< PubSub::Module* > AppList;

    class Entity
    {
      private:

        enum class EntityState
        {
            BOOT,
            INITIALIZE,
            STARTED,
            UPDATE,
            PAUSED,
            STOPPED,
            FINALIZE
        };

      public:

        Entity() = delete;
        explicit Entity( const double runRate );
        virtual ~Entity();

        void addModel( Model* model, const ModelOrder order );
        void removeModel( Model* model );

        void addSwApp( PubSub::Module* app );
        void removeSwApp( PubSub::Module* app );

        virtual void createEntity() = 0;
        void initialize();
        void update();
        void stop( bool over_ride = false );
        void finalize();

      protected:

        std::shared_ptr< PubSub::QueueMngr > m_queueMngr;

      private:

        EntityState m_entityState;

        ModelList m_models;
        AppList   m_apps;

        std::shared_ptr< Time > m_worldTime;

        unsigned int m_counter;

        const unsigned int m_runRate;

        void getWorldTime( std::shared_ptr< Time >& worldTime );

        void passReferences();
        void passQueueMngr();

        void run( const EntityState threadState );
        void runSW();
        void runSim();

        static bool compareModelOrder( const std::pair< Model*, ModelOrder >& lhs,
                                       const std::pair< Model*, ModelOrder >& rhs );

        Entity( const Entity& ) = delete;
        Entity& operator=( const Entity& ) = delete;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_ENTITY_H */
