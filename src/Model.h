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
    typedef std::list< std::pair< ModelLabel, Model** > > ReferenceRequestList;

    class ReferenceRequest
    {
      public:
        friend class Model;

        ReferenceRequest();
        ~ReferenceRequest();

        void requestReference( Model** model, ModelLabel label );

      private:
        friend class Entity;

        void reset();

        ReferenceRequestList m_referenceRequests;
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

        virtual void initialize() = 0;
        virtual void update()     = 0;
        virtual void finalize()   = 0;
        virtual void requestReferences( ReferenceRequest& refReq );

        const ModelRate m_rate;

      private:

        virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr );

        const ModelLabel label;

        Model( const Model& ) = delete;
        Model& operator=( const Model& ) = delete;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_MODEL_H */
