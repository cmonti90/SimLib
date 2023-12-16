
#include "Entity.h"
#include "ForceEffector.h"

#include <algorithm>

namespace SimLib
{

    Entity::Entity( const double runRate )
        : m_forceEffector( new ForceEffector( runRate ) )
        , m_models       ()
        , m_apps         ()
        , m_worldTime    ( nullptr )
        , m_queueMngr    ( new PubSub::QueueMngr() )
        , m_counter      ( 0u )
        , m_runRate      ( runRate )
    {
        addModel( m_forceEffector.get(), runRate );
    }

    Entity::~Entity()
    {
    }

    void Entity::addModel( Model* model, const ModelOrder order )
    {
        m_models.push_back( std::pair< Model*, ModelOrder >( model, order ) );

        m_models.sort( compareModelOrder );
    }

    void Entity::removeModel( Model* model )
    {
        for ( auto& modelIdx : m_models )
        {
            if ( modelIdx.first == model )
            {
                m_models.remove( modelIdx );
            }
        }
    }

    void Entity::addSwApp( PubSub::Module* app )
    {
        m_apps.push_back( app );

        m_apps.unique();
    }

    void Entity::removeSwApp( PubSub::Module* app )
    {
        m_apps.remove( app );
    }

    void Entity::initialize()
    {
        run( EntityState::INITIALIZE );
    }

    void Entity::update()
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

    void Entity::getWorldTime( std::shared_ptr< Time >& worldTime )
    {
        m_worldTime = worldTime;
    }

    void Entity::run( const EntityState entityState )
    {
        m_entityState = entityState;

        runSW();
        runSim();
    }

    void Entity::runSW()
    {
        if ( m_entityState == EntityState::UPDATE )
        {
            for ( auto& app : m_apps )
            {
                app->iterate();
            }
        }
        else if ( m_entityState == EntityState::INITIALIZE )
        {

            for ( auto& app : m_apps )
            {
                app->launch();
                app->initialize();
            }
        }
        else if ( m_entityState == EntityState::FINALIZE )
        {
            for ( auto& app : m_apps )
            {
                app->finalize();
            }
        }
    }

    void Entity::runSim()
    {
        if ( m_entityState == EntityState::UPDATE )
        {
            for ( auto& model : m_models )
            {
                if ( ( m_counter % static_cast< unsigned int >( m_runRate / static_cast< unsigned int >( model.first->getModelRate() ) ) ) == 0 )
                {
                    model.first->update();
                }
            }

            m_queueMngr->dispatch();
        }
        else if ( m_entityState == EntityState::INITIALIZE )
        {
            passReferences();
            passQueueMngr();

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

    void Entity::passReferences()
    {
        ReferenceRequest refReq;

        for ( auto& model : m_models )
        {
            refReq.reset();

            model.first->requestReferences( refReq );

            for ( auto& refReqIdx : refReq.m_referenceRequests )
            {
                for ( auto& modelIdx : m_models )
                {
                    if ( modelIdx.first->getModelLabel() == refReqIdx.first )
                    {
                        *( refReqIdx.second ) = modelIdx.first;
                        
                        break;
                    }
                }
            }
        }
    }

    void Entity::passQueueMngr()
    {
        for ( auto& model : m_models )
        {
            model.first->receiveQueueMngr( m_queueMngr );
        }
    }

    bool Entity::compareModelOrder( const std::pair< Model*, ModelOrder >& lhs,
                                    const std::pair< Model*, ModelOrder >& rhs )
    {
        return lhs.second < rhs.second;
    }

} // namespace SimLib
