#ifndef C59815DA_39FC_4C7E_9D4B_7DCAEE2442F5
#define C59815DA_39FC_4C7E_9D4B_7DCAEE2442F5

#include "EOM.h"

#include "mathlib.h"

namespace SimLib
{
    class EOMEcef : public EOM
    {
      public:
        explicit EOMEcef( const ModelRate rate, const ModelLabel str );
        virtual ~EOMEcef();

      protected:

        void RungeKutta4thOrder( myMath::Vector3d& posEcef, myMath::Vector3d& velEcef, myMath::Vector3d& accelEcef,
                                 myMath::Vector3d& angRatesBody, myMath::Vector3d& angAccelBody, const myMath::Matrix3d& rotInertia,
                                 myMath::QuaternionD& q_nedToBody, myMath::Vector3d& specificForceEcef, const myMath::Vector3d& netMomentBody );

      private:

        myMath::Vector3d ComputeGravityJ2( const myMath::Vector3d& posEcef );

        myMath::Vector3d AccelerationEcef( const myMath::Vector3d& posEcef, const myMath::Vector3d& velEcef, const myMath::Vector3d& specificForceEcef );

        myMath::Vector3d angularRatesDerivative( const myMath::Matrix3d& rotInertia, const double p, const double q, const double r, const myMath::Vector3d& netMomentBody );
        myMath::Matrix4d QuaterionRKrotationMatrix( const double scalar, const myMath::Vector3d& rotRates );

    };
} // namespace SimLib

#endif /* C59815DA_39FC_4C7E_9D4B_7DCAEE2442F5 */
