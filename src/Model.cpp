
#include "Model.h"

namespace SimLib
{
    ReferenceRequest::ReferenceRequest()
        : m_referenceRequests()
    {
    }

    ReferenceRequest::~ReferenceRequest()
    {
    }

    void ReferenceRequest::reset()
    {
        m_referenceRequests.clear();
    }

    void ReferenceRequest::requestReference( Model** model, ModelLabel label )
    {
        m_referenceRequests.push_back( std::pair< ModelLabel, Model** >( label, model ) );
    }

    Model::Model( const ModelRate rate, const ModelLabel str )
        : m_rate        ( rate )
        , label         ( str )
    {
    }

    Model::~Model()
    {
    }

    void Model::requestReferences( ReferenceRequest& refReq )
    {
        // Do nothing by default
    }

    ModelLabel Model::getModelLabel() const
    {
        return label;
    }

    ModelRate  Model::getModelRate() const
    {
        return m_rate;
    }

    void Model::receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
    {
        // Do nothing by default
    }

} // namespace SimLib