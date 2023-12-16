

#include "EOM.h"

namespace SimLib
{
    EOM::EOM( const ModelRate rate, const ModelLabel str )
        : Model( rate, str )
    {
    }

    void EOM::requestReferences( ReferenceRequest& refReq )
    {
        refReq.requestReference( reinterpret_cast< Model** >( &m_forceEffector ), "ForceEffector" );
    }

    EOM::~EOM()
    {
    }

    void EOM::initialize()
    {
    }

    void EOM::update()
    {
    }

    void EOM::finalize()
    {
    }

    void EOM::rungeKutta4thOrder( const myMath::Vector3d& pos_frameA, const myMath::Vector3d& vel_frameA, const myMath::Vector3d& omegaBody,
                                  const myMath::DCMd& bodyFromFrameA,
                                  const myMath::QuaternionD& frameAFromFrameB,
                                  myMath::Vector3d& intPos_frameA, myMath::Vector3d& intVel_frameA, myMath::Vector3d& acc_frameA,
                                  myMath::Vector3d& intOmegaBody, myMath::QuaternionD& intFrameAFromFrameB )
    {
    }

} // namespace SimLib