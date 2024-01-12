#ifndef GUARD_SIMLIB_TIME_H
#define GUARD_SIMLIB_TIME_H

#include <mutex>
#include <condition_variable>

namespace SimLib
{
    class SimTime
    {
    public:
        SimTime();
        ~SimTime();
        SimTime(const SimTime &);

        void incrementTime();
        void finalize();
        void reset();

        double getTimeNow() const;
        unsigned int getCounter() const;
        static double getClockRate();

        static SimTime* GetInstance();

    protected:
    friend class World;
        static void setClockRate( const double rate );

    private:

        double timeNow;
        unsigned int counter;

        static double ClockRate;
        
        mutable std::mutex mtx;
        mutable std::condition_variable cv;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_TIME_H */
