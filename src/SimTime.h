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

        static constexpr unsigned int SimulationRunRate = 1000u;

        void incrementTime();
        void finalize();
        void reset();

        double getTimeNow() const;
        unsigned int getCounter() const;

        static SimTime* GetInstance();

    private:
        double timeNow{0.0};
        unsigned int counter = 0u;
        
        mutable std::mutex mtx;
        mutable std::condition_variable cv;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_TIME_H */