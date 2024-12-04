/*********************************************************************
 * \file   IntrBox3Sphere3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_BOX3_SPHERE3_HPP
#define INTR_BOX3_SPHERE3_HPP
#include "Intersector.hpp"
#include "Math/Box3.hpp"
#include "Math/Sphere3.hpp"

namespace Collision
{
    class IntrBox3Sphere3 final : public Intersector
    {
    public:
        IntrBox3Sphere3(const Math::Box3& box, const Math::Sphere3& sphere);

        [[nodiscard]] const Math::Box3& box() const;
        [[nodiscard]] const Math::Sphere3& sphere() const;

        bool test() override;

    private:
        Math::Box3 m_box;
        Math::Sphere3 m_sphere;
    };

}

#endif // INTR_BOX3_SPHERE3_HPP
