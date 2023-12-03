#ifndef GUARD_SIMLIB_MODEL_H
#define GUARD_SIMLIB_MODEL_H

#include "QueueMngr.h"

#include <string>
#include <memory>
#include <list>

namespace SimLib
{

    typedef std::string             ModelLabel;
    typedef double                  ModelRate;
    typedef std::list< ModelLabel > MessageSubscription;

    class Model
    {
      public:

        Model() = delete;
        Model( const ModelRate rate, const ModelLabel str );
        Model( std::shared_ptr<PubSub::QueueMngr>& queue_mngr, const ModelRate rate, const ModelLabel str );
        virtual ~Model() = default;

        virtual void requestReferences();
        virtual void initialize() = 0;
        virtual void update()     = 0;
        virtual void finalize()   = 0;

        ModelLabel getModelLabel() const;
        ModelRate  getModelRate() const;

      protected:

        const ModelRate m_rate;

      private:

        const ModelLabel label;

        std::shared_ptr< QueueMngr > m_queue_mngr;

        Model( const Model& ) = delete;
        Model& operator=( const Model& ) = delete;
    };
} // namespace SimLib

#endif /* GUARD_SIMLIB_MODEL_H */
