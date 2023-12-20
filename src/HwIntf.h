#ifndef B187FA68_4BBA_49D9_BF0E_B009930E2008
#define B187FA68_4BBA_49D9_BF0E_B009930E2008

#include "Model.h"
#include "QueueMngr.h"

#include <memory>

namespace SimLib
{
    class HwIntf : public Model
    {
      public:

        HwIntf() = delete;
        explicit HwIntf( const double runRate, const ModelLabel str );

        virtual ~HwIntf();

        std::shared_ptr< PubSub::QueueMngr >& getQueueMngr();

      protected:
      

      private:

        virtual void receiveQueueMngr( std::shared_ptr< PubSub::QueueMngr >& queueMngr ) override;

        std::shared_ptr< PubSub::QueueMngr > m_queueMngr;

        HwIntf( const HwIntf& ) = delete;
        HwIntf& operator=( const HwIntf& ) = delete;
    };
} // namespace SimLib

#endif /* B187FA68_4BBA_49D9_BF0E_B009930E2008 */
