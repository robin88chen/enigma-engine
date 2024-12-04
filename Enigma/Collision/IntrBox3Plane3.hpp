/*********************************************************************
 * \file   IntrBox3Plane3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_BOX3_PLANE3_HPP
#define INTR_BOX3_PLANE3_HPP
#include "Intersector.hpp"
#include "Math/Box3.hpp"
#include "Math/Plane3.hpp"

namespace Collision
{
    class IntrBox3Plane3 final : public Intersector
    {
    public:
        IntrBox3Plane3(const Math::Box3& box, const Math::Plane3& plane, bool is_aligned);

        [[nodiscard]] const Math::Box3& box() const;
        [[nodiscard]] const Math::Plane3& plane() const;

        bool test() override;

        [[nodiscard]] Math::Plane3::SideOfPlane testPlaneSide() const;

    private:
        Math::Box3 m_box;
        Math::Plane3 m_plane;
        bool m_isAligned;
    };
}

#endif // INTR_BOX3_PLANE3_HPP
