
#include "SimTime.h"

namespace SimLib
{
    SimTime::SimTime() : timeNow( 0.0 ), counter( 0u ), mtx(), cv()
    {
    }

    SimTime::SimTime( const SimTime& obj ) : timeNow( obj.timeNow ), counter( obj.counter ), mtx(), cv()
    {
    }

    SimTime::~SimTime()
    {
    }

    void SimTime::incrementTime()
    {
        std::unique_lock<std::mutex> lck( mtx );

        timeNow += 1.0 / static_cast<double>( SimulationRunRate );

        counter++;

        lck.unlock();
        cv.notify_one();
    }

    void SimTime::reset()
    {
        std::unique_lock<std::mutex> lck( mtx );

        timeNow = 0.0;
        counter = 0u;

        lck.unlock();
        cv.notify_one();
    }

    void SimTime::finalize()
    {
    }

    double SimTime::getTimeNow() const
    {
        std::lock_guard<std::mutex> lck( mtx );

        return timeNow;
    }

    unsigned int SimTime::getCounter() const
    {
        std::lock_guard<std::mutex> lck( mtx );

        return counter;
    }

    SimTime* SimTime::GetInstance()
    {
        static SimTime timeInstance;

        return &timeInstance;
    }

} // namespace SimLib