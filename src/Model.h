#ifndef GUARD_SIMLIB_MODEL_H
#define GUARD_SIMLIB_MODEL_H

#include "QueueMngr.h"

#include <string>
#include <memory>
#include <list>

namespace SimLib
{
    class Model;
    typedef std::string             ModelLabel;
    typedef double                  ModelRate;
    typedef std::list< ModelLabel > ReferenceRequestList;
    typedef std::list< std::pair< ModelLabel, std::shared_ptr< Model > > > ReferenceList;

    class ReferenceRequest
    {
      public:
        friend class Model;

        ReferenceRequest();
        ~ReferenceRequest();

        void requestReference( ModelLabel label );
        Model* getReference( ModelLabel label );

      private:
      friend class Entity;

        ReferenceRequestList m_referenceRequests;
        ReferenceList        m_references;
    };

    class Model
    {
      public:

        Model() = delete;
        explicit Model( const ModelRate rate, const ModelLabel str );
        virtual ~Model();

        ModelLabel getModelLabel() const;
        ModelRate  getModelRate() const;

      protected:
        friend class World;
        friend class Entity;

        const ModelRate m_rate;

      private:

        const ModelLabel label;
        ReferenceRequest m_reference_request;

        virtual void initialize() = 0;
        virtual void update()     = 0;
        virtual void finalize()   = 0;
        virtual void getReferenceRequest( ReferenceRequest& refReq );
        
        virtual ReferenceRequest requestReferences() const;

        virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr );

        Model( const Model& ) = delete;
        Model& operator=( const Model& ) = delete;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_MODEL_H */
