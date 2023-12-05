
#include "Entity.h"

#include <algorithm>

#include <csignal>
#include <iostream>

void signalHandler( int signum )
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    // cleanup and close up stuff here
    // terminate program

    exit( signum );
}

namespace SimLib
{

    Entity::Entity( const double runRate )
        : m_models   ()
        , m_apps     ()
        , m_queueMngr( nullptr )
        , m_time     ( new Time() )
        , m_counter  ( 0u )
        , m_runRate  ( runRate )
    {
        signal( SIGINT, signalHandler );
        signal( SIGABRT, signalHandler );
    }

    void Entity::addModel( std::shared_ptr< Model >& model, const ModelOrder order )
    {
        m_models.push_back( std::pair< std::shared_ptr< Model >, ModelOrder >( model, order ) );

        m_models.sort( compareModelOrder );
    }

    void Entity::removeModel( std::shared_ptr< Model >& model )
    {
        for ( auto& modelIdx : m_models )
        {
            if ( modelIdx.first == model )
            {
                m_models.remove( modelIdx );
            }
        }
    }

    void Entity::addSwApp( std::shared_ptr< PubSub::Module >& app )
    {
        m_apps.push_back( app );

        m_apps.unique();
    }

    void Entity::removeSwApp( std::shared_ptr< PubSub::Module >& app )
    {
        m_apps.remove( app );
    }

    void Entity::initialize()
    {
        run( EntityState::INITIALIZE );
    }

    void Entity::start()
    {
        run( EntityState::UPDATE );
    }

    void Entity::stop( bool over_ride )
    {
        m_entityState = EntityState::STOPPED;

        if ( !over_ride )
        {
            finalize();
        }
    }

    void Entity::finalize()
    {
        run( EntityState::FINALIZE );
    }

    void Entity::run( const EntityState entityState )
    {
        m_entityState = entityState;

        runSW();

        m_time->incrementTime();

        runSim();
    }

    void Entity::runSW()
    {
        for ( auto& app : m_apps )
        {
            app.get()->iterate();
        }
    }

    void Entity::runSim()
    {
        if ( m_entityState == EntityState::STARTED )
        {
            for ( auto& model : m_models )
            {
                if ( ( m_counter % static_cast< unsigned int >( m_runRate / static_cast< unsigned int >( model.first.get()->getModelRate() ) ) ) == 0 )
                {
                    model.first->update();
                }
            }
        }
        else if ( m_entityState <= EntityState::INITIALIZE )
        {
            for ( auto& model : m_models )
            {
                model.first->requestReferences();
            }

            for ( auto& model : m_models )
            {
                model.first->initialize();
            }
        }
        else if ( m_entityState == EntityState::FINALIZE )
        {
            for ( auto& model : m_models )
            {
                model.first->finalize();
            }
        }

        m_counter++;
    }

    bool Entity::compareModelOrder( const std::pair< std::shared_ptr< Model >, ModelOrder >& lhs,
                                    const std::pair< std::shared_ptr< Model >, ModelOrder >& rhs )
    {
        return lhs.second < rhs.second;
    }

} // namespace SimLib
