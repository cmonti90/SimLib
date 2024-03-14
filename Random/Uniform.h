
#ifndef GUARD_RAND_UNIFORM_H
#define GUARD_RAND_UNIFORM_H

#include <cstdlib>

namespace SimLib
{

    class Uniform
    {
      public:
        Uniform();
        Uniform( const double min, const double max );
        virtual ~Uniform();

        double draw();
        double draw( const double min, const double max );

      private:
        friend class World;
        void SetSeed( const int seed );

        static int m_seed;

        double m_min;
        double m_max;
    };

} // namespace SimLib

#endif // GUARD_RAND_UNIFORM_H