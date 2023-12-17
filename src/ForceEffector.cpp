

#include "ForceEffector.h"

namespace SimLib
{
    ForceEffector::ForceEffector( const ModelRate rate, const ModelLabel str )
        : Model( rate, str )
        , m_sustainedForceMap ()
        , m_singleForceMap    ()
        , m_sustainedMomentMap()
        , m_singleMomentMap   ()
    {
    }

    ForceEffector::~ForceEffector()
    {
    }

    void ForceEffector::requestReferences( ReferenceRequest& refReq )
    {
    }

    void ForceEffector::initialize()
    {
    }

    void ForceEffector::update()
    {
    }

    void ForceEffector::finalize()
    {
    }

    myMath::Vector3d ForceEffector::getForce()
    {
        myMath::Vector3d force( 0.0 );

        for( auto& it : m_sustainedForceMap )
        {
            force += it.second;
        }

        for( auto& it : m_singleForceMap )
        {
            force += it.second;

            m_singleForceMap.erase( it.first );
        }

        return force;
    }

    myMath::Vector3d ForceEffector::getMoment()
    {
        myMath::Vector3d moment( 0.0 );

        for( auto& it : m_sustainedMomentMap )
        {
            moment += it.second;
        }

        for( auto& it : m_singleMomentMap )
        {
            moment += it.second;

            m_singleForceMap.erase( it.first );
        }

        return moment;
    }

    void ForceEffector::addForce( const Model* model, const myMath::Vector3d force, const ForceEffectorType type )
    {
        switch( type )
        {
            case ForceEffectorType::SINGLE:

                m_singleForceMap[model] = force;

                break;

            case ForceEffectorType::ZERO_ORDER_HOLD:

                m_sustainedForceMap[model] = force;

                break;

            default:

                break;
        }
    }

    void ForceEffector::addMoment( const Model* model, const myMath::Vector3d moment, const ForceEffectorType type )
    {
        switch( type )
        {
            case ForceEffectorType::SINGLE:

                m_singleMomentMap[model] = moment;

                break;

            case ForceEffectorType::ZERO_ORDER_HOLD:

                m_sustainedMomentMap[model] = moment;

                break;

            default:

                break;
        }
    }

} // namespace SimLib