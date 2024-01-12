
#include "SimTime.h"

namespace SimLib
{
    double SimTime::ClockRate = 1000.0; // default clock rate is 1000 Hz

    SimTime::SimTime()
        : timeNow( 0.0 )
        , counter( 0u )
        , mtx()
        , cv()
    {
    }

    SimTime::SimTime( const SimTime& obj )
        : timeNow( obj.timeNow )
        , counter( obj.counter )
        , mtx()
        , cv()
    {
    }

    SimTime::~SimTime()
    {
    }

    void SimTime::incrementTime()
    {
        std::unique_lock<std::mutex> lck( mtx );

        timeNow += 1.0 / SimTime::ClockRate;

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
        std::lock_guard< std::mutex > lck( mtx );

        return timeNow;
    }

    unsigned int SimTime::getCounter() const
    {
        std::lock_guard< std::mutex > lck( mtx );

        return counter;
    }

    double SimTime::getClockRate()
    {
        return SimTime::ClockRate;
    }

    void SimTime::setClockRate( const double rate )
    {
        SimTime::ClockRate = rate;
    }

    SimTime* SimTime::GetInstance()
    {
        static SimTime timeInstance;

        return &timeInstance;
    }

} // namespace SimLib