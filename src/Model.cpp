
#include "Model.h"

namespace SimLib
{
    Model::Model( const ModelRate rate, const ModelLabel str )
        : m_rate        ( rate )
        , label         ( str )
        , m_queue_mngr  ( nullptr )
    {
    }

    Model::Model( std::shared_ptr<PubSub::QueueMngr>& queue_mngr, const ModelRate m_rate, const ModelLabel str )
        : m_rate        ( m_rate )
        , label         ( str )
        , m_queue_mngr  ( queue_mngr )
    {
    }

    void Model::requestReferences()
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

} // namespace SimLib