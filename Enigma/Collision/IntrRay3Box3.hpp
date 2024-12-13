/*********************************************************************
 * \file   IntrRay3Box3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_RAY3_BOX3_HPP
#define INTR_RAY3_BOX3_HPP
#include "Intersector.hpp"
#include "Math/Ray3.hpp"
#include "Math/Box3.hpp"

namespace Collision
{
    class IntrRay3Box3 final : public Intersector
    {
    public:
        IntrRay3Box3(const Math::Ray3& ray, const Math::Box3& box);

        [[nodiscard]] const Math::Ray3& ray() const;
        [[nodiscard]] const Math::Box3& box() const;

        bool test() override;
        bool find() override;

        [[nodiscard]] unsigned getQuantity() const;
        [[nodiscard]] const Math::Point3& getPoint(unsigned i) const;
        [[nodiscard]] float getRayT(unsigned i) const;

    private:
        Math::Ray3 m_ray;
        Math::Box3 m_box;

        unsigned m_quantity;
        std::array<Math::Point3, 2> m_point;
        std::array<float, 2> m_tParam;
    };

}

#endif // INTR_RAY3_BOX3_HPP
