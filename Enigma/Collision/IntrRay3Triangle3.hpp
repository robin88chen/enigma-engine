/*********************************************************************
 * \file   IntrRay3Triangle3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_RAY3_TRIANGLE3_HPP
#define INTR_RAY3_TRIANGLE3_HPP
#include "Intersector.hpp"
#include "Math/Ray3.hpp"
#include "Math/Triangle3.hpp"

namespace Collision
{
    class IntrRay3Triangle3 final : public Intersector
    {
    public:
        IntrRay3Triangle3(const Math::Ray3& ray, const Math::Triangle3& triangle);

        [[nodiscard]] const Math::Ray3& ray() const;
        [[nodiscard]] const Math::Triangle3& triangle() const;

        bool test() override;
        bool find() override;

        [[nodiscard]] unsigned getQuantity() const;
        [[nodiscard]] const Math::Vector3& getPoint() const;
        [[nodiscard]] float getRayT() const;

    private:
        Math::Ray3 m_ray;
        Math::Triangle3 m_triangle;

        unsigned m_quantity;
        Math::Vector3 m_point;
        float m_tParam;
    };
}

#endif // INTR_RAY3_TRIANGLE3_HPP
