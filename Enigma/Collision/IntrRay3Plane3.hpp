/*********************************************************************
 * \file   IntrRay3Plane3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_RAY3_PLANE3_HPP
#define INTR_RAY3_PLANE3_HPP
#include "Intersector.hpp"
#include "Math/Ray3.hpp"
#include "Math/Plane3.hpp"

namespace Collision
{
    class IntrRay3Plane3 final : public Intersector
    {
    public:
        IntrRay3Plane3(const Math::Ray3& ray, const Math::Plane3& plane);

        [[nodiscard]] const Math::Ray3& ray() const;
        [[nodiscard]] const Math::Plane3& plane() const;

        bool test() override;
        bool find() override;

        [[nodiscard]] unsigned getQuantity() const;
        [[nodiscard]] const Math::Vector3& getPoint() const;
        [[nodiscard]] float getRayT() const;

    private:
        Math::Ray3 m_ray;
        Math::Plane3 m_plane;

        unsigned m_quantity;
        Math::Vector3 m_point;
        float m_tParam;
    };
}

#endif // INTR_RAY3_PLANE3_HPP
