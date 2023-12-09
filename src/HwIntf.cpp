
#include "HwIntf.h"

namespace SimLib
{
    HwIntf::HwIntf(  const double runRate, const ModelLabel str )
        : Model( runRate, str )
        , m_queueMngr( nullptr )
    {
    }

    HwIntf::~HwIntf()
    {
    }

    std::shared_ptr< PubSub::QueueMngr >& HwIntf::getQueueMngr()
    {
        return m_queueMngr;
    }

    void HwIntf::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
    {
        m_queueMngr = queueMngr;
    }

} // namespace SimLib