

#include "World.h"

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

    World::World()
        : m_time    ( new Time() )
        , m_entities()
    {
        signal( SIGINT, signalHandler );
        signal( SIGABRT, signalHandler );
    }

    World::~World()
    {
    }

    void World::addEntity( Entity* entity )
    {
        std::cout << "World::addEntity" << std::endl;

        m_entities.push_back( entity );

        m_entities.unique();
    }

    void World::removeEntity( Entity* entity )
    {
        m_entities.remove( entity );
    }

    void World::initialize()
    {
        std::cout << "World::initialize" << std::endl;

        for ( auto& entity : m_entities )
        {
            entity->initialize();
        }
    }

    void World::go()
    {
        std::cout << "World::go" << std::endl;
        
        createWorld();

        for ( auto& entity : m_entities )
        {
            entity->createEntity();
        }

        initialize();

        for ( int i{0}; i < 100; ++i )
        {
            iterate();
        }

        finalize();
    }

    void World::iterate()
    {
        std::cout << "World::iterate : incrementTime" << std::endl;
        
        m_time.get()->incrementTime();

        std::cout << "World::iterate" << std::endl;
        
        for ( auto& entity : m_entities )
        {
            entity->update();
        }
    }

    void World::finalize()
    {
        for ( auto& entity : m_entities )
        {
            entity->finalize();
        }
    }

} // namespace SimLib