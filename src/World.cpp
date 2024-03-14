

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

    World::World( const unsigned int runRate )
        : m_time    ( SimTime::GetInstance() )
        , m_entities()
    {
        SimTime::setClockRate( static_cast< double >( runRate ) );

        // register signal SIGINT and signal handler
        signal( SIGINT, signalHandler );
        signal( SIGABRT, signalHandler );
        signal( SIGFPE, signalHandler );
        signal( SIGILL, signalHandler );
        signal( SIGSEGV, signalHandler );
        signal( SIGTERM, signalHandler );

    }

    World::~World()
    {
    }

    void World::addEntity( Entity* entity )
    {
        m_entities.push_back( entity );

        m_entities.unique();
    }

    void World::removeEntity( Entity* entity )
    {
        m_entities.remove( entity );
    }

    void World::go()
    {
        createWorld();

        for ( auto& entity : m_entities )
        {
            entity->createEntity();
        }

        initialize();

        for ( int i{0}; i < 1e5; ++i )
        {
            iterate();
        }

        finalize();
    }

    void World::initialize()
    {
        std::cout << "World::initialize" << std::endl;

        for ( auto& entity : m_entities )
        {
            entity->initialize();
        }
    }

    void World::iterate()
    {
        m_time->incrementTime();

        for ( auto& entity : m_entities )
        {
            entity->update();
        }
    }

    void World::finalize()
    {
        std::cout << "World::finalize" << std::endl;

        for ( auto& entity : m_entities )
        {
            entity->finalize();
        }
    }

} // namespace SimLib