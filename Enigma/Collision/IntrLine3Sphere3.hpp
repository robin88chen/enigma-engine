/*********************************************************************
 * \file   IntrLine3Sphere3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_LINE3_SPHERE3_HPP
#define INTR_LINE3_SPHERE3_HPP
#include "Intersector.hpp"
#include "Math/Line3.hpp"
#include "Math/Sphere3.hpp"

namespace Collision
{
    class IntrLine3Sphere3 final : public Intersector
    {
    public:
        IntrLine3Sphere3(const Math::Line3& line, const Math::Sphere3& sphere);

        [[nodiscard]] const Math::Line3& line() const;
        [[nodiscard]] const Math::Sphere3& sphere() const;

        bool test() override;

        bool find() override;
        [[nodiscard]] unsigned getQuantity() const;
        [[nodiscard]] const Math::Vector3& getPoint(unsigned i) const;
        [[nodiscard]] float getLineT(unsigned i) const;

    private:
        Math::Line3 m_line;
        Math::Sphere3 m_sphere;

        unsigned m_quantity;
        std::array<Math::Vector3, 2> m_point;
        std::array<float, 2> m_lineT;
    };

}

#endif // INTR_LINE3_SPHERE3_HPP
