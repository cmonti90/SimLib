
#include "Host.h"

#include <csignal>

void signalHandler( int signum )
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    // cleanup and close up stuff here
    // terminate program

    exit( signum );
}

namespace SimLib
{

    Host::Host()
        : m_models   ()
        , apps       ()
        , m_queueMngr( nullptr )
        , m_time     ( new Time() )
    {
        signal( SIGINT, signalHandler );
        signal( SIGABRT, signalHandler );
    }

    void Host::addModel( std::shared_ptr< Model >& model )
    {
        m_models.push_back( model );

        std::sort( m_models.begin(), m_models.end(), Host::compareModelOrder );
    }

    void Host::addSwApp( std::shared_ptr< Module >& app )
    {
        m_apps.push_back( app );

        m_apps.unique();
    }

    void Host::initialize()
    {
        run( HostState::INITIALIZE );
    }

    void Host::start()
    {
        run( HostState::UPDATE );
    }

    void Host::stop( bool over_ride )
    {
        m_hostState = HostState::STOPPED;

        if ( !over_ride )
        {
            finalize();
        }
    }

    void Host::finalize()
    {
        run( HostState::FINALIZE );
    }

    void Host::run( const HostState hostState )
    {
        m_hostState = hostState;

        runSW( m_hostState );

        m_time->incrementTime();

        runSim( m_hostState );
    }

    void Host::runSW( const HostState hostState )
    {
        for ( unsigned int procIdx{0u}; procIdx < maxProcCount; procIdx++ )
        {

            for ( unsigned int threadIdx{0u}; threadIdx < m_threads.size(); threadIdx++ )
            {
                m_threads[threadIdx].run( hostState );
            }

            for ( unsigned int threadIdx{0u}; threadIdx < m_threads.size(); threadIdx++ )
            {
                m_threads[threadIdx].join();
            }

            dispatchMessages( hostState );
        }

        for ( unsigned int threadIdx{0u}; threadIdx < m_threads.size(); threadIdx++ )
        {
            m_threads[threadIdx].resetProcessCount();
        }
    }

    void Host::runSim( const HostState hostState )
    {
        for ( unsigned int procIdx{0u}; procIdx < m_simThread.getProcessCount(); procIdx++ )
        {
            m_simThread.run( hostState, m_time->getCounter() );

            dispatchMessages( hostState );
        }

        m_simThread.resetProcessCount();
    }

    void Host::dispatchMessages( const HostState hostState )
    {
        if ( hostState == HostState::UPDATE )
        {
            m_queueMngr->dispatch();
        }
    }

    bool Host::compareModelOrder( const std::pair< std::shared_ptr< Model >, ModelOrder >& lhs,
                                  const std::pair< std::shared_ptr< Model >, ModelOrder >& rhs )
    {
        return lhs.second < rhs.second;
    }

} // namespace SimLib
