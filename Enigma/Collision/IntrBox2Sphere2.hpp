/*********************************************************************
 * \file   IntrBox2Sphere2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_BOX2_SPHERE2_HPP
#define INTR_BOX2_SPHERE2_HPP
#include "Intersector.hpp"
#include "Math/Box2.hpp"
#include "Math/Sphere2.hpp"
namespace Collision
{
    class IntrBox2Sphere2 : public Intersector
    {
    public:
        IntrBox2Sphere2(const Math::Box2& box, const Math::Sphere2& sphere);

        [[nodiscard]] const Math::Box2& box() const;
        [[nodiscard]] const Math::Sphere2& sphere() const;

        bool test() override;

    private:
        Math::Box2 m_box;
        Math::Sphere2 m_sphere;
    };

}

#endif // INTR_BOX2_SPHERE2_HPP
