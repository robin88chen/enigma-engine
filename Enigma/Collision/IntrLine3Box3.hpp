/*********************************************************************
 * \file   IntrLine3Box3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_LINE3_BOX3_HPP
#define INTR_LINE3_BOX3_HPP
#include "Intersector.hpp"
#include "Math/Line3.hpp"
#include "Math/Box3.hpp"
#include <array>

namespace Collision
{
    class IntrLine3Box3 final : public Intersector
    {
    public:
        IntrLine3Box3(const Math::Line3& line, const Math::Box3& box);

        [[nodiscard]] const Math::Line3& line() const;
        [[nodiscard]] const Math::Box3& box() const;

        bool test() override;

        bool find() override;
        [[nodiscard]] unsigned getQuantity() const;
        [[nodiscard]] const Math::Point3& getPoint(unsigned i) const;
        [[nodiscard]] float getLineT(unsigned i) const;

    private:
        static bool clip(float denom, float numer, float& t0, float& t1);

        //--- member variables
        Math::Line3 m_line;
        Math::Box3 m_box;

        unsigned m_quantity;
        std::array<Math::Point3, 2> m_point;
        std::array<float, 2> m_lineT;
    };
}

#endif // INTR_LINE3_BOX3_HPP
