/*********************************************************************
 * \file   IntrSphere3Sphere3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_SPHERE3_SPHERE3_HPP
#define INTR_SPHERE3_SPHERE3_HPP
#include "Intersector.hpp"
#include "Math/Sphere3.hpp"
namespace Collision
{
    class IntrSphere3Sphere3 final : public Intersector
    {
    public:
        IntrSphere3Sphere3(const Math::Sphere3& sphere0, const Math::Sphere3& sphere1);

        [[nodiscard]] const Math::Sphere3& sphere0() const;
        [[nodiscard]] const Math::Sphere3& sphere1() const;

        bool test() override;

    private:
        Math::Sphere3 m_sphere0;
        Math::Sphere3 m_sphere1;
    };
}

#endif // INTR_SPHERE3_SPHERE3_HPP
