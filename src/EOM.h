#ifndef C59815DA_39FC_4C7E_9D4B_7DCAEE2442F5
#define C59815DA_39FC_4C7E_9D4B_7DCAEE2442F5

#include "Model.h"
#include "ForceEffector.h"

#include "mathlib.h"

namespace SimLib
{
    class EOM : public Model
    {
      public:
        explicit EOM( const ModelRate rate, const ModelLabel str );
        virtual ~EOM();

      protected:

        virtual void initialize() override;
        virtual void update()     override;
        virtual void finalize()   override;

        ForceEffector* m_forceEffector;

      private:

        virtual void requestReferences( ReferenceRequest& refReq ) override;

        void rungeKutta4thOrder( const myMath::Vector3d& pos_frameA, const myMath::Vector3d& vel_frameA, const myMath::Vector3d& omegaBody,
                                 const myMath::DCMd& bodyFromFrameA,
                                 const myMath::QuaternionD& frameAFromFrameB,
                                 myMath::Vector3d& intPos_frameA, myMath::Vector3d& intVel_frameA, myMath::Vector3d& acc_frameA,
                                 myMath::Vector3d& intOmegaBody, myMath::QuaternionD& intFrameAFromFrameB );


    };
} // namespace SimLib

#endif /* C59815DA_39FC_4C7E_9D4B_7DCAEE2442F5 */
