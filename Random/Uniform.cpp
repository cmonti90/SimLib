
#include "Uniform.h"

namespace SimLib
{
        int Uniform::m_seed = 0; // default seed
    
        Uniform::Uniform( const double min, const double max )
            : m_min( min )
            , m_max( max )
        {
        }
    
        Uniform::~Uniform()
        {
        }

        void Uniform::SetSeed( const int seed )
        {
            m_seed = seed;
            std::srand( m_seed );
        }
    
        double Uniform::draw()
        {
            return ( ( static_cast< double > ( std::rand() ) / static_cast< double > ( RAND_MAX ) ) * ( m_max - m_min ) ) + m_min;
        }

        double Uniform::draw( const double min, const double max )
        {
            return ( ( static_cast< double > ( std::rand() ) / static_cast< double > ( RAND_MAX ) ) * ( max - min ) ) + min;
        }


} // namespace SimLib