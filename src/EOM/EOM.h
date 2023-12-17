#ifndef E9AE2F1F_6E90_4B61_9966_1F376524BC82
#define E9AE2F1F_6E90_4B61_9966_1F376524BC82

#include "Model.h"
#include "ForceEffector.h"

namespace SimLib
{
    
    class EOM : public Model
    {
      public:
        explicit EOM( const ModelRate rate, const ModelLabel str );
        virtual ~EOM();

      protected:

        enum : unsigned int
        {
            X = 0u,
            Y,
            Z
        };

        enum : unsigned int
        {
            ROLL = 0u,
            PITCH,
            YAW
        };

        ForceEffector* m_forceEffector;

      private:

        virtual void requestReferences( ReferenceRequest& refReq ) override;
    };

} // namespace SimLib

#endif /* E9AE2F1F_6E90_4B61_9966_1F376524BC82 */
