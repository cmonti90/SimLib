#ifndef E2731927_DDD7_4D9D_AF82_A57EB4795F51
#define E2731927_DDD7_4D9D_AF82_A57EB4795F51

#include "Model.h"

#include "Vector.h"

#include <vector>
#include <unordered_map>

namespace SimLib
{
    class ForceEffector : public Model
    {
      public:

        enum class ForceEffectorType : unsigned int
        {
            SINGLE,
            ZERO_ORDER_HOLD
        };

        ForceEffector() = delete;
        explicit ForceEffector( const ModelRate rate, const ModelLabel str = "ForceEffector" );
        virtual ~ForceEffector();

        // Getters
        myMath::Vector3d getForce();
        myMath::Vector3d getMoment();

        // Setters
        void addForce( const Model* model, const myMath::Vector3d force, const ForceEffectorType type = ForceEffectorType::ZERO_ORDER_HOLD );
        void addMoment( const Model* model, const myMath::Vector3d moment, const ForceEffectorType type = ForceEffectorType::ZERO_ORDER_HOLD );

      protected:

        virtual void initialize() override;
        virtual void update()     override;
        virtual void finalize()   override;

      private:
        typedef std::unordered_map< const Model*, myMath::Vector3d > ForceMap;

        ForceMap m_sustainedForceMap;
        ForceMap m_singleForceMap;
        ForceMap m_sustainedMomentMap;
        ForceMap m_singleMomentMap;

        ForceEffector( const ForceEffector& ) = delete;
        ForceEffector& operator=( const ForceEffector& ) = delete;
    };
} // namespace SimLib

#endif /* E2731927_DDD7_4D9D_AF82_A57EB4795F51 */
