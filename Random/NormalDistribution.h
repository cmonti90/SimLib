
#ifndef GUARD_RAND_NORMALDISTRIBUTION_H
#define GUARD_RAND_NORMALDISTRIBUTION_H

#include <cstdlib>

namespace SimLib
{

    class NormalDistribution
    {
      public:
        NormalDistribution();
        NormalDistribution( const double mean, const double stdDev );
        virtual ~NormalDistribution();

        double draw();
        double draw( const double mean, const double stdDev );

      private:
        friend class World;
        void SetSeed( const int seed );

        static int m_seed;

        double m_mean;
        double m_stdDev;
    };

} // namespace SimLib

#endif // GUARD_RAND_NORMALDISTRIBUTION_H