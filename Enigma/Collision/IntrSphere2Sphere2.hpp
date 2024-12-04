/*********************************************************************
 * \file   IntrSphere2Sphere2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_SPHERE2_SPHERE2_HPP
#define INTR_SPHERE2_SPHERE2_HPP
#include "Intersector.hpp"
#include "Math/Sphere2.hpp"

namespace Collision
{
    class IntrSphere2Sphere2 final : public Intersector
    {
    public:
        IntrSphere2Sphere2(const Math::Sphere2& sphere0, const Math::Sphere2& sphere1);

        [[nodiscard]] const Math::Sphere2& sphere0() const;
        [[nodiscard]] const Math::Sphere2& sphere1() const;

        bool test() override;

    private:
        Math::Sphere2 m_sphere0;
        Math::Sphere2 m_sphere1;
    };
}

#endif // INTR_SPHERE2_SPHERE2_HPP
