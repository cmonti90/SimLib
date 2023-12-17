
#include "EOM.h"

namespace SimLib
{
    EOM::EOM( const ModelRate rate, const ModelLabel str )
        : Model( rate, str )
        , m_forceEffector( nullptr )
    {
    }

    EOM::~EOM()
    {
    }

    void EOM::requestReferences( ReferenceRequest& refReq )
    {
        refReq.requestReference( reinterpret_cast< Model** >( &m_forceEffector ), "ForceEffector" );
    }
    
} // namespace SimLib