#ifndef GUARD_SIMLIB_HOST_H
#define GUARD_SIMLIB_HOST_H

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
    typedef std::list< std::unique_ptr< Module > > AppList;

    class Host
    {
      private:
        enum class HostState
        {
            BOOT,
            INITIALIZED,
            STARTED,
            PAUSED,
            STOPPED,
            FINALIZED
        };

      public:
        Host();
        virtual ~Host() = default;

        void addModel( std::shared_ptr< Model >& model );
        void addSwApp( std::shared_ptr< Module >& app );

        void initialize();
        void start();
        void stop( bool over_ride = false );
        void finalize();

        void run( const HostState threadState );

      private:

        HostState m_hostState;

        ModelList m_models;
        AppList   m_apps;

        std::shared_ptr< QueueMngr > m_queueMngr;

        std::shared_ptr< Time > m_time;

        void runSW( const HostState threadState );
        void runSim( const HostState threadState );
        void dispatchMessages( const HostState threadState );

        static bool compareModelOrder( const std::pair< std::shared_ptr< Model >, ModelOrder >& lhs,
                                       const std::pair< std::shared_ptr< Model >, ModelOrder >& rhs );

        Host( const Host& ) = delete;
        Host& operator=( const Host& ) = delete;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_HOST_H */
