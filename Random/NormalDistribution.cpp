
#include "NormalDistribution.h"

#include "myMathConstants.h"

#include <algorithm>
#include <limits>
#include <cmath>

namespace SimLib
{

    int NormalDistribution::m_seed = 0;

    NormalDistribution::NormalDistribution()
        : m_mean  ( 0.0 )
        , m_stdDev( 1.0 )
    {
    }

    NormalDistribution::NormalDistribution( const double mean, const double stdDev )
        : m_mean  ( mean )
        , m_stdDev( stdDev )
    {
    }

    NormalDistribution::~NormalDistribution()
    {
    }

    void NormalDistribution::SetSeed( const int seed )
    {
        m_seed = seed;
        std::srand( m_seed );
    }

    double NormalDistribution::draw()
    {
        double u1 = 0.0;
        double u2 = 0.0;

        do
        {
            u1 = static_cast< double > ( std::rand() ) / static_cast< double > ( RAND_MAX );
            u2 = static_cast< double > ( std::rand() ) / static_cast< double > ( RAND_MAX );
        } while ( u1 <= std::numeric_limits< double >::epsilon() );

        const double z0 = std::sqrt( -2.0 * std::log( u1 ) ) * std::cos( 2.0 * myMath::Constants::PI * u2 );
        return z0 * m_stdDev + m_mean;
    }

    double NormalDistribution::draw( const double mean, const double stdDev )
    {
        double u1 = 0.0;
        double u2 = 0.0;

        do
        {
            u1 = static_cast< double > ( std::rand() ) / static_cast< double > ( RAND_MAX );
            u2 = static_cast< double > ( std::rand() ) / static_cast< double > ( RAND_MAX );
        } while ( u1 <= std::numeric_limits< double >::epsilon() );

        const double z0 = std::sqrt( -2.0 * std::log( u1 ) ) * std::cos( 2.0 * myMath::Constants::PI * u2 );
        return z0 * stdDev + mean;
    }

} // namespace SimLib