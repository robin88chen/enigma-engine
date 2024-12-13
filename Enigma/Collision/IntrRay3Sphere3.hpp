/*********************************************************************
 * \file   IntrRay3Sphere3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_RAY3_SPHERE3_HPP
#define INTR_RAY3_SPHERE3_HPP
#include "Intersector.hpp"
#include "Math/Ray3.hpp"
#include "Math/Sphere3.hpp"

namespace Collision
{
    class IntrRay3Sphere3 final : public Intersector
    {
    public:
        IntrRay3Sphere3(const Math::Ray3& ray, const Math::Sphere3& sphere);

        [[nodiscard]] const Math::Ray3& ray() const;
        [[nodiscard]] const Math::Sphere3& sphere() const;

        bool test() override;
        bool find() override;

        [[nodiscard]] unsigned getQuantity() const;
        [[nodiscard]] const Math::Point3& getPoint(unsigned i) const;
        [[nodiscard]] float getRayT(unsigned i) const;

    private:
        Math::Ray3 m_ray;
        Math::Sphere3 m_sphere;

        unsigned m_quantity;
        std::array<Math::Point3, 2> m_point;
        std::array<float, 2> m_tParam;
    };
}

#endif // INTR_RAY3_SPHERE3_HPP
