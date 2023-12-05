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
    typedef std::list< std::pair< std::shared_ptr< Model >, ModelOrder > > ModelList;
    typedef std::list< std::shared_ptr< PubSub::Module > > AppList;

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
        virtual ~Entity() = default;

        void addModel( std::shared_ptr< Model >& model, const ModelOrder order );
        void removeModel( std::shared_ptr< Model >& model );

        void addSwApp( std::shared_ptr< PubSub::Module >& app );
        void removeSwApp( std::shared_ptr< PubSub::Module >& app );

        void initialize();
        void start();
        void stop( bool over_ride = false );
        void finalize();

        void run( const EntityState threadState );

      private:

        EntityState m_entityState;

        ModelList m_models;
        AppList   m_apps;

        std::shared_ptr< PubSub::QueueMngr > m_queueMngr;

        std::shared_ptr< Time > m_time;

        unsigned int m_counter;

        const unsigned int m_runRate; 

        void runSW();
        void runSim();

        static bool compareModelOrder( const std::pair< std::shared_ptr< Model >, ModelOrder >& lhs,
                                       const std::pair< std::shared_ptr< Model >, ModelOrder >& rhs );

        Entity( const Entity& ) = delete;
        Entity& operator=( const Entity& ) = delete;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_ENTITY_H */
