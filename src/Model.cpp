
#include "Model.h"

namespace SimLib
{
    ReferenceRequest::ReferenceRequest()
        : m_referenceRequests()
        , m_references       ()
    {
    }

    ReferenceRequest::~ReferenceRequest()
    {
    }

    void ReferenceRequest::requestReference( ModelLabel label )
    {
        m_referenceRequests.push_back( label );
    }

    Model* ReferenceRequest::getReference( ModelLabel label )
    {
        for ( auto& ref : m_referenceRequests )
        {
            if ( ref == label )
            {
                return nullptr;
            }
        }

        return nullptr;
    }

    Model::Model( const ModelRate rate, const ModelLabel str )
        : m_rate        ( rate )
        , label         ( str )
    {
    }

    Model::~Model()
    {
    }

    ReferenceRequest Model::requestReferences() const
    {
        // Do nothing by default
        ReferenceRequest request;

        return request;
    }

    void Model::getReferenceRequest( ReferenceRequest& refReq )
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