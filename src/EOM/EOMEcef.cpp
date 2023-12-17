

#include "EOMEcef.h"

#include "Constants.h"

namespace SimLib
{
    EOMEcef::EOMEcef( const ModelRate rate, const ModelLabel str )
        : EOM( rate, str )
    {
    }

    EOMEcef::~EOMEcef()
    {
    }

    void EOMEcef::RungeKutta4thOrder( myMath::Vector3d& posEcef, myMath::Vector3d& velEcef, myMath::Vector3d& accelEcef,
                                      myMath::Vector3d& angRatesBody, myMath::Vector3d& angAccelBody, const myMath::Matrix3d& rotInertia,
                                      myMath::QuaternionD& q_bodyFromEcef, const myMath::Vector3d& gravityEcef,
                                      const myMath::Vector3d& specificForceEcef, const myMath::Vector3d& netMomentBody )
    {
        const double dt = 1.0 / m_rate;

        myMath::Vector3d dPosEcef[4];
        myMath::Vector3d dVelEcef[4];

        myMath::Matrix4d Kq[4];
        myMath::Vector3d dAngBodyRates[4];
        myMath::Vector3d dAngBodyRatesDot;

        // Instantaneous accelerations
        accelEcef           = AccelerationEcef( posEcef, velEcef, gravityEcef, specificForceEcef );
        angAccelBody        = angularRatesDerivative( rotInertia, angRatesBody[ROLL], angRatesBody[PITCH], angRatesBody[YAW], netMomentBody );

        // k1
        dVelEcef[0]         = dt * AccelerationEcef( posEcef, velEcef, gravityEcef, specificForceEcef );
        dPosEcef[0]         = dt * velEcef;
        dAngBodyRates[0]    = dt * angularRatesDerivative( rotInertia, angRatesBody[ROLL], angRatesBody[PITCH], angRatesBody[YAW], netMomentBody );
        Kq[0]               = QuaterionRKrotationMatrix( 1.0 / 6.0, angRatesBody );


        // k2
        dVelEcef[1]         = dt * AccelerationEcef( posEcef + dPosEcef[0] / 2.0, velEcef + dVelEcef[0] / 2.0, gravityEcef, specificForceEcef );
        dPosEcef[1]         = dt * ( velEcef + dVelEcef[0] / 2.0 );
        dAngBodyRatesDot    = dt * angularRatesDerivative( rotInertia, angRatesBody[ROLL] + dAngBodyRates[0][ROLL] / 2.0, angRatesBody[PITCH] + dAngBodyRates[0][PITCH] / 2.0, angRatesBody[YAW] + dAngBodyRates[0][YAW] / 2.0, netMomentBody );
        Kq[1]               = QuaterionRKrotationMatrix( 1.0 / 3.0, angRatesBody );

        // k3
        dVelEcef[2]         = dt * AccelerationEcef( posEcef + dPosEcef[1] / 2.0, velEcef + dVelEcef[1] / 2.0, gravityEcef, specificForceEcef );
        dPosEcef[2]         = dt * ( velEcef + dVelEcef[1] / 2.0 );
        dAngBodyRates[2]    = dt * angularRatesDerivative( rotInertia, angRatesBody[ROLL] + dAngBodyRates[1][ROLL] / 2.0, angRatesBody[PITCH] + dAngBodyRates[1][PITCH] / 2.0, angRatesBody[YAW] + dAngBodyRates[1][YAW] / 2.0, netMomentBody );
        Kq[2]               = QuaterionRKrotationMatrix( 1.0 / 3.0, angRatesBody );

        // k4
        dVelEcef[3]         = dt * AccelerationEcef( posEcef + dPosEcef[2], velEcef + dVelEcef[2], gravityEcef, specificForceEcef );
        dPosEcef[3]         = dt * ( velEcef + dVelEcef[2] );
        dAngBodyRates[3]    = dt * angularRatesDerivative( rotInertia, angRatesBody[ROLL] + dAngBodyRates[2][ROLL], angRatesBody[PITCH] + dAngBodyRates[2][PITCH], angRatesBody[YAW] + dAngBodyRates[2][YAW], netMomentBody );
        Kq[3]               = QuaterionRKrotationMatrix( 1.0 / 6.0, angRatesBody );


        // Update state
        velEcef         += ( dVelEcef[0]      + 2.0 * ( dVelEcef[1]      + dVelEcef[2]      ) + dVelEcef[3]      ) / 6.0;
        posEcef         += ( dPosEcef[0]      + 2.0 * ( dPosEcef[1]      + dPosEcef[2]      ) + dPosEcef[3]      ) / 6.0;
        angRatesBody    += ( dAngBodyRates[0] + 2.0 * ( dAngBodyRates[1] + dAngBodyRates[2] ) + dAngBodyRates[3] ) / 6.0;

        q_bodyFromEcef  = Kq[3] * Kq[2] * Kq[1] * Kq[0] * q_bodyFromEcef;
        q_bodyFromEcef.Normalize();

    }

    myMath::Vector3d EOMEcef::AccelerationEcef( const myMath::Vector3d& posEcef, const myMath::Vector3d& velEcef, const myMath::Vector3d& gravityEcef, const myMath::Vector3d& specificForceEcef )
    {
        const myMath::Vector3d omegaEcef{ 0.0, 0.0, myMath::Constants::EARTH_ROTATION_RATE };

        return specificForceEcef - 2.0 * myMath::Cross( omegaEcef, velEcef ) - myMath::Cross( omegaEcef, myMath::Cross( omegaEcef, posEcef ) ) + gravityEcef;
    }


    //////////////////////////////////////////////////////
    /// @note   Name: angularRatesDerivative
    /// @brief  Calculate the angular acceleration in
    ///         the body frame
    /// @param  Rotatational inertia matrix
    /// @param  Roll rate in body frame
    /// @param  Pitch rate in body frame
    /// @param  Yaw rate in body frame
    /// @param  EOM input data structure
    /// @return Acceleration in Z direction in body frame
    myMath::Vector3d EOMEcef::angularRatesDerivative( const myMath::Matrix3d& rotInertia, const double p, const double q, const double r, const myMath::Vector3d& netMomentBody )
    {
        myMath::Vector3d angularRatesDerivs;

        angularRatesDerivs[ROLL]  = -q * ( -p * rotInertia[X][Z] - q * rotInertia[Y][Z] + r * rotInertia[Z][Z] ) + r * ( -p * rotInertia[X][Y] + q * rotInertia[Y][Y] - r * rotInertia[Y][Z] ) + netMomentBody[ROLL];
        angularRatesDerivs[PITCH] =  p * ( -p * rotInertia[X][Z] - q * rotInertia[Y][Z] + r * rotInertia[Z][Z] ) - r * (  p * rotInertia[X][X] - q * rotInertia[X][Y] + r * rotInertia[X][Z] ) + netMomentBody[PITCH];
        angularRatesDerivs[YAW]   = -p * ( -p * rotInertia[X][Y] + q * rotInertia[Y][Y] - r * rotInertia[Y][Z] ) + q * (  p * rotInertia[X][X] - q * rotInertia[X][Y] + r * rotInertia[X][Z] ) + netMomentBody[YAW];

        return  rotInertia.Inverse() * angularRatesDerivs;
    }

    //////////////////////////////////////////////////////
    /// @note   Name: QuaterionRKrotationMatrix
    /// @brief  Calculate rotor derivative using
    ///         angular rates for Runge-Kutta
    /// @param  Integration scalar
    /// @param  Rotation rates
    /// @return Rotor
    //////////////////////////////////////////////////////
    myMath::Matrix4d EOMEcef::QuaterionRKrotationMatrix( const double scalar, const myMath::Vector3d& rotRates )
    {
        if ( myMath::isZero( rotRates.Magnitude() ) )
        {
            return myMath::Matrix4d::Identity();
        }

        myMath::Matrix4d omega;
        omega[0][0] = 0.0;
        omega[0][1] = -rotRates[2];
        omega[0][2] = rotRates[1];
        omega[0][3] = rotRates[0];

        omega[1][0] = rotRates[2];
        omega[1][1] = 0.0;
        omega[1][2] = -rotRates[0];
        omega[1][3] = rotRates[1];

        omega[2][0] = -rotRates[1];
        omega[2][1] = rotRates[0];
        omega[2][2] = 0.0;
        omega[2][3] = rotRates[2];

        omega[3][0] = -rotRates[0];
        omega[3][1] = -rotRates[1];
        omega[3][2] = -rotRates[2];
        omega[3][3] = 0.0;

        const double angInp = 0.5 * scalar * rotRates.Magnitude() / m_rate;

        return myMath::Matrix4d::Identity() * std::cos( angInp ) + omega * std::sin( angInp ) / rotRates.Magnitude();
    }
} // namespace SimLib